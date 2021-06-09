/* -*- mode: C -*-  */
/* 
   IGraph library.
   Copyright (C) 2003-2012  Gabor Csardi <csardi.gabor@gmail.com>
   334 Harvard street, Cambridge, MA 02139 USA
   
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 
   02110-1301 USA

*/

/* skiplist algo is documented on wikipedia with graphics
 * no recursive routines then no stack smashing
 * no casts needed as with gcc splay
 * union is used as opaque datatype instead of casting
 * multiple same-key values are possible
 * grouped in routines for int-as-key, string-as-key and pointer-as-key
 * replacement for gcc splay which has few issues.
 * only malloc/free and no realloc
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <stddef.h>
#include <time.h>
#include <limits.h>

#include "skiplist.h"

#define CALLOC calloc
#define FREE free

/* */
#define SKL_HEIGHT 10

/* */
static int skl_randlevel (void);

/* new tree pointer as key */
struct sklp *
sklp_new (void (*sklp_rm_key_fn) (void *key), void (*sklp_rm_value_fn) (union skl_value val))
{
  struct sklp *n = NULL;
  n = CALLOC (1, sizeof (struct sklp));
  if (n)
    {
      /* */
      n->start = (struct sklp_n **) CALLOC (1, SKL_HEIGHT * sizeof (struct sklp_n *));
      n->sklp_rm_key_fn = sklp_rm_key_fn;
      n->sklp_rm_value_fn = sklp_rm_value_fn;
    }
  return ((struct sklp *) n);
}

/* new tree string as key */
struct skls *
skls_new (void (*skls_rm_key_fn) (char *key), void (*skls_rm_value_fn) (union skl_value val))
{
  struct skls *n = NULL;
  n = CALLOC (1, sizeof (struct skls));
  if (n)
    {
      /* */
      n->start = (struct skls_n **) CALLOC (1, SKL_HEIGHT * sizeof (struct skls_n *));
      n->skls_rm_key_fn = skls_rm_key_fn;
      n->skls_rm_value_fn = skls_rm_value_fn;
    }
  return ((struct skls *) n);
}

/* new tree string as int */
struct skli *
skli_new (void (*skli_rm_key_fn) (int32_t key), void (*skli_rm_value_fn) (union skl_value val))
{
  struct skli *n = NULL;
  n = CALLOC (1, sizeof (struct skli));
  if (n)
    {
      /* */
      n->start = (struct skli_n **) CALLOC (1, SKL_HEIGHT * sizeof (struct skli_n *));
      n->skli_rm_key_fn = skli_rm_key_fn;
      n->skli_rm_value_fn = skli_rm_value_fn;
    }
  return ((struct skli *) n);
}

/* free whole tree pointer */
struct sklp *
sklp_rm (struct sklp *skl)
{
  struct sklp_n *item = (struct sklp_n *) 0;
  struct sklp_n *old = (struct sklp_n *) 0;
  /* */
  if ((struct sklp *) 0 == skl)
    {
      return ((struct sklp *) 0);
    }
  /* */
  item = skl->start[0];
  /* does not stack smash. */
  while (item)
    {
      /* */
      old = item;
      /* */
      item = item->next[0];
      /* delete data */
      if (skl->sklp_rm_value_fn)
	{
	  skl->sklp_rm_value_fn (old->value);
	}
      /* */
      old->value.p = NULL;
      /* delete key */
      if (skl->sklp_rm_key_fn)
	{
	  skl->sklp_rm_key_fn (old->key);
	}
      /* */
      old->key = NULL;
      /* */
      FREE (old->next);
      old->next = NULL;
      /* */
      FREE (old);
      old = NULL;
    }
  /* */
  FREE (skl->start);
  skl->start = NULL;
  /* The deallocate-key function.  NULL if no cleanup is necessary.  */
  skl->sklp_rm_key_fn = NULL;
  /* The deallocate-value function.  NULL if no cleanup is necessary.  */
  skl->sklp_rm_value_fn = NULL;
  /* */
  FREE (skl);
  /* */
  return ((struct sklp *) 0);
}

/* free whole tree string */
struct skls *
skls_rm (struct skls *skl)
{
  struct skls_n *item = (struct skls_n *) 0;
  struct skls_n *old = (struct skls_n *) 0;
  /* */
  if ((struct skls *) 0 == skl)
    {
      return ((struct skls *) 0);
    }
  /* */
  item = skl->start[0];
  /* */
  while (item)
    {
      /* */
      old = item;
      /* */
      item = item->next[0];
      /* delete data */
      if (skl->skls_rm_value_fn)
	{
	  skl->skls_rm_value_fn (old->value);
	}
      /* */
      old->value.p = NULL;
      /* delete key */
      if (skl->skls_rm_key_fn)
	{
	  skl->skls_rm_key_fn (old->key);
	}
      /* */
      old->key = NULL;
      /* */
      free (old->next);
      old->next = NULL;
      /* */
      FREE (old);
      old = NULL;
    }
  /* */
  FREE (skl->start);
  skl->start = NULL;
  /* The deallocate-key function.  NULL if no cleanup is necessary.  */
  skl->skls_rm_key_fn = NULL;
  /* The deallocate-value function.  NULL if no cleanup is necessary.  */
  skl->skls_rm_value_fn = NULL;
  /* */
  FREE (skl);
  /* */
  return ((struct skls *) 0);
}

/* free whole tree int */
struct skli *
skli_rm (struct skli *skl)
{
  struct skli_n *item = (struct skli_n *) 0;
  struct skli_n *old = (struct skli_n *) 0;
  /* */
  if ((struct skli *) 0 == skl)
    {
      return ((struct skli *) 0);
    }
  /* */
  item = skl->start[0];
  /* */
  while (item)
    {
      /* */
      old = item;
      /* */
      item = item->next[0];
      /* delete data */
      if (skl->skli_rm_value_fn)
	{
	  skl->skli_rm_value_fn (old->value);
	}
      /* */
      old->value.p = NULL;
      /* delete key */
      if (skl->skli_rm_key_fn)
	{
	  skl->skli_rm_key_fn (old->key);
	}
      /* */
      old->key = 0;
      /* */
      FREE (old->next);
      old->next = NULL;
      /* */
      free (old);
      old = NULL;
    }
  /* */
  FREE (skl->start);
  skl->start = NULL;
  /* The deallocate-key function.  NULL if no cleanup is necessary.  */
  skl->skli_rm_key_fn = NULL;
  /* The deallocate-value function.  NULL if no cleanup is necessary.  */
  skl->skli_rm_value_fn = NULL;
  /* */
  FREE (skl);
  /* this sets result to 0 */
  return ((struct skli *) 0);
}

/* add node in pointer tree */
struct sklp_n *
sklp_add (struct sklp *skl, void *ptr)
{
  struct sklp_n *n = NULL;
  struct sklp_n **cur = NULL;
  int h = 0;
  int hh = 0;
  /* allow 0 ptr in ptr */
  n = calloc (1, sizeof (struct sklp_n));
  hh = skl_randlevel () + 1;
  n->next = CALLOC (1, (sizeof (struct sklp_n *) * (hh)));
  n->key = ptr;
  cur = skl->start;
  h = (SKL_HEIGHT - 1);
  for (;;)
    {
      if (cur[h] && (ptrdiff_t) (cur[h]->key) < (ptrdiff_t) (ptr))
	{
	  cur = cur[h]->next;
	}
      else
	{
	  if (h < hh)
	    {
	      n->next[h] = cur[h];
	      cur[h] = n;
	    }
	  h = (h - 1);
	  if (h < 0)
	    {
	      break;
	    }
	}
    }
  return ((struct sklp_n *) n);
}

/* add node in string tree */
struct skls_n *
skls_add (struct skls *skl, char *str)
{
  struct skls_n *n = NULL;
  struct skls_n **cur = NULL;
  int h = 0;
  int hh = 0;
  if (str == (char *) 0)
    {
      return ((struct skls_n *) 0);
    }
  n = calloc (1, sizeof (struct skls_n));
 /* range 1...SKL_HEIGHT */
  hh = skl_randlevel () + 1;
  n->next = CALLOC (1, (sizeof (struct skls_n *) * (hh)));
  n->key = str;
  cur = skl->start;
  h = (SKL_HEIGHT - 1);
  for (;;)
    {
      /* */
      if (cur[h] && strcmp ((cur[h]->key), (str)) < 0)
	{
	  cur = cur[h]->next;
	}
      else
	{
	  if (h < hh)
	    {
	      n->next[h] = cur[h];
	      cur[h] = n;
	    }
	  h = (h - 1);
	  if (h < 0)
	    {
	      break;
	    }
	}
    }
  return ((struct skls_n *) n);
}

/* add node in int tree */
struct skli_n *
skli_add (struct skli *skl, int i)
{
  struct skli_n *n = NULL;
  struct skli_n **cur = NULL;
  int h = 0;
  int hh = 0;
  /* signed int 32bits in i */
  n = calloc (1, sizeof (struct skli_n));
  hh = skl_randlevel () + 1;
  n->next = CALLOC (1, (sizeof (struct skli_n *) * (hh)));
  n->key = i;
  cur = skl->start;
  h = (SKL_HEIGHT - 1);
  for (;;)
    {
      if (cur[h] && (int) (cur[h]->key) < (int) (i))
	{
	  cur = cur[h]->next;
	}
      else
	{
	  if (h < hh)
	    {
	      n->next[h] = cur[h];
	      cur[h] = n;
	    }
	  h = (h - 1);
	  if (h < 0)
	    {
	      break;
	    }
	}
    }
  return ((struct skli_n *) n);
}

/* find */
struct sklp_n *
sklp_find (struct sklp *skl, void *ptr)
{
  if (skl == (struct sklp *) 0)
    {
      return ((struct sklp_n *) 0);
    }
  if (ptr == (void *) 0)
    {
      return ((struct sklp_n *) 0);
    }

  return ((struct sklp_n *) 0);
}

/* find */
struct skls_n *
skls_find (struct skls *skl, char *str)
{
  struct skls_n **cur = NULL;
  int h = 0;
  if (skl == (struct skls *) 0)
    {
      return ((struct skls_n *) 0);
    }
  if (str == (char *) 0)
    {
      return ((struct skls_n *) 0);
    }
  h = (SKL_HEIGHT - 1);
  cur = skl->start;
  for (;;)
    {
      if (cur[h] && (strcmp ((cur[h]->key), str) < 0))
	{
	  cur = cur[h]->next;
	}
      else
	{
	  if (cur[h])
	    {
	      if (strcmp (cur[h]->key, str) == 0)
		{
		  return ((struct skls_n *) cur[h]);
		}
	    }
	  h = (h - 1);
	  if (h < 0)
	    {
	      break;
	    }
	}
    }
  /* */
  if (cur[0])
    {
      if (strcmp (cur[0]->key, str) == 0)
	{
	  return ((struct skls_n *) cur[0]);
	}
    }

  return ((struct skls_n *) 0);
}

/* find */
struct skli_n *
skli_find (struct skli *skl, int i)
{
  struct skli_n **cur = NULL;
  int h = 0;
  if (skl == (struct skli *) 0)
    {
      return ((struct skli_n *) 0);
    }
  h = (SKL_HEIGHT - 1);
  cur = skl->start;
  for (;;)
    {
      if (cur[h] && (int) (cur[h]->key) < (int) (i))
	{
	  cur = cur[h]->next;
	}
      else
	{
	  if (cur[h])
	    {
	      if (cur[h]->key == i)
		{
		  return ((struct skli_n *) cur[h]);
		}
	    }
	  h = (h - 1);
	  if (h < 0)
	    {
	      break;
	    }
	}
    }
  /* */
  if (cur[0])
    {
      if (cur[0]->key == i)
	{
	  return ((struct skli_n *) cur[0]);
	}
    }
  return ((struct skli_n *) 0);
}

/* print */
void
sklp_pr (struct sklp *skl)
{
  struct sklp_n **cur = NULL;
  struct sklp_n *nc = NULL;
  int h = 0;
  if (skl == (struct sklp *) 0)
    {
      return;
    }
  h = (SKL_HEIGHT - 1);
  cur = skl->start;
  for (h = (SKL_HEIGHT - 1); h >= 0; h = (h - 1))
    {
      if (cur[h] == NULL)
	{
	  printf ("level%d: empty\n", h);
	}
      else
	{
	  printf ("level%d: ", h);
	  nc = cur[h];
	  while (nc)
	    {
	      printf ("%p ", nc->key);
	      nc = nc->next[0];
	    }
	}
    }
  return;
}

/* print */
void
skls_pr (struct skls *skl)
{
  struct skls_n **cur = NULL;
  struct skls_n *nc = NULL;
  int h = 0;
  int nr = 0;
  if (skl == (struct skls *) 0)
    {
      return;
    }
  cur = skl->start;
  for (h = (SKL_HEIGHT - 1); h >= 0; h = (h - 1))
    {
      if (cur[h] == NULL)
	{
	  printf ("level%d: empty\n", h);
	}
      else
	{
	  nr = 0;
	  nc = cur[h];
	  while (nc)
	    {
	      nr = (nr + 1);
	      nc = nc->next[0];
	    }
	  printf ("level%d (%d entries): ", h, nr);
	  nc = cur[h];
	  while (nc)
	    {
	      printf ("\"%s\" ", nc->key);
	      nc = nc->next[0];
	    }
	  printf ("\n");
	}
    }
  return;
}

/* print */
void
skli_pr (struct skli *skl)
{
  struct skli_n **cur = NULL;
  struct skli_n *nc = NULL;
  int h = 0;
  if (skl == (struct skli *) 0)
    {
      return;
    }
  cur = skl->start;
  for (h = (SKL_HEIGHT - 1); h >= 0; h = (h - 1))
    {
      if (cur[h] == NULL)
	{
	  printf ("level%d: empty\n", h);
	}
      else
	{
	  printf ("level%d: ", h);
	  nc = cur[h];
	  while (nc)
	    {
	      printf ("%d ", nc->key);
	      nc = nc->next[0];
	    }
	  printf ("\n");
	}
    }
  return;
}

/* start element */
struct sklp_n *
sklp_min (struct sklp *skl)
{
  struct sklp_n *ret = (struct sklp_n *) 0;
  if (skl == (struct sklp *) 0)
    {
      return ((struct sklp_n *) 0);
    }
  if (skl->start)
    {
      if (skl->start[0])
	{
	  ret = skl->start[0];
	}
    }
  return ((struct sklp_n *) ret);
}

/* start element */
struct skls_n *
skls_min (struct skls *skl)
{
  struct skls_n *ret = (struct skls_n *) 0;
  if (skl == (struct skls *) 0)
    {
      return ((struct skls_n *) 0);
    }
  if (skl->start)
    {
      if (skl->start[0])
	{
	  ret = skl->start[0];
	}
    }
  return ((struct skls_n *) ret);
}

/* start element */
struct skli_n *
skli_min (struct skli *skl)
{
  struct skli_n *ret = (struct skli_n *) 0;
  if (skl == (struct skli *) 0)
    {
      return ((struct skli_n *) 0);
    }
  if (skl->start)
    {
      if (skl->start[0])
	{
	  ret = skl->start[0];
	}
    }
  return ((struct skli_n *) ret);
}

/* next entry */
struct sklp_n *
sklp_next (struct sklp *skl, struct sklp_n *n)
{
  if (skl == (struct sklp *) 0)
    {
      return ((struct sklp_n *) 0);
    }
  if (n == (struct sklp_n *) 0)
    {
      return ((struct sklp_n *) 0);
    }
  return (n->next[0]);
}

/* next entry */
struct skls_n *
skls_next (struct skls *skl, struct skls_n *n)
{
  if (skl == (struct skls *) 0)
    {
      return ((struct skls_n *) 0);
    }
  if (n == (struct skls_n *) 0)
    {
      return ((struct skls_n *) 0);
    }
  return (n->next[0]);
}

/* next entry */
struct skli_n *
skli_next (struct skli *skl, struct skli_n *n)
{
  if (skl == (struct skli *) 0)
    {
      return ((struct skli_n *) 0);
    }
  if (n == (struct skli_n *) 0)
    {
      return ((struct skli_n *) 0);
    }
  return (n->next[0]);
}

/* output range 0...(SKL_HEIGHT-1) */
static int
skl_randlevel (void)
{
  int level = 1;
  for (;;)
    {
      if (rand () < (RAND_MAX / 2))
	{
	  level = (level + 1);
	}
      else
	{
	  break;
	}
    }
  if (level >= SKL_HEIGHT)
    {
      level = (SKL_HEIGHT - 1);
    }
  return level;
}

/* end. */

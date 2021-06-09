/* -*- mode: C -*-  */
/* 
   IGraph library.
   Copyright (C) 2009-2012  Gabor Csardi <csardi.gabor@gmail.com>
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

#include "config.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "skiplist.h"

/* db */
static struct skls *gustring = NULL;

/* */
static void
uniqstring_free (char *s)
{
  if (s)
    {
      free ((void *) s);
    }
  return;
}

/* keep 1 copy of a string around */
char *
uniqstring (char *str)
{
  size_t len = 0;
  char *buf = NULL;
  struct skls_n *node = NULL;
  if (str == NULL)
    {
      return (NULL);
    }
  len = strlen (str);
  if (len == 0)
    {
      return ((char *) "");
    }
  if (gustring == NULL)
    {
      gustring = skls_new (uniqstring_free, NULL);
    }
  node = skls_find (gustring, str);
  if (node)
    {
      return (node->key);
    }
  buf = malloc (len + 1);
  memset (buf, 0, len + 1);
  memmove (buf, str, len);
  node = skls_add (gustring, buf);
  return (node->key);
}

/* clear db */
void
uniqstring_clear (void)
{
  gustring = skls_rm (gustring);
  return;
}

/* end. */

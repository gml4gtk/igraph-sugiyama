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

#ifndef SKIPLIST_H
#define SKIPLIST_H 1

/* value used with key */
union skl_value
{
  int   i; /* 32bit signed int */
  char *s;
  void *p;
};

/* node when pointer as key */
struct sklp_n
{
  /* pointer as a key */
  void *key;
  union skl_value value;
  struct sklp_n **next;
};

/* node when string as key */
struct skls_n
{
  /* string as a key */
  char *key;
  union skl_value value;
  struct skls_n **next;
};

/* node when int as key */
struct skli_n
{
  /* 32bit signed int int as a key */
  int key;
  union skl_value value;
  struct skli_n **next;
};

/* tree */
struct sklp
{
  /* root */
  struct sklp_n **start;

  /* The deallocate-key function.  NULL if no cleanup is necessary.  */
  void (*sklp_rm_key_fn) (void *key);

  /* The deallocate-value function.  NULL if no cleanup is necessary.  */
  void (*sklp_rm_value_fn) (union skl_value val);
};

/* tree string */
struct skls
{
  /* root */
  struct skls_n **start;

  /* The deallocate-key function.  NULL if no cleanup is necessary.  */
  void (*skls_rm_key_fn) (char *key);

  /* The deallocate-value function.  NULL if no cleanup is necessary.  */
  void (*skls_rm_value_fn) (union skl_value val);
};

/* tree int */
struct skli
{
  /* root */
  struct skli_n **start;

  /* The deallocate-key function.  NULL if no cleanup is necessary.  */
  void (*skli_rm_key_fn) (int key);

  /* The deallocate-value function.  NULL if no cleanup is necessary.  */
  void (*skli_rm_value_fn) (union skl_value val);
};

/* new tree pointer */
extern struct sklp *sklp_new (void (*sklp_rm_key_fn) (void *key),
			      void (*sklp_rm_value_fn) (union skl_value val));

/* new tree string */
extern struct skls *skls_new (void (*skls_rm_key_fn) (char *key),
			      void (*skls_rm_value_fn) (union skl_value val));

/* new tree int */
extern struct skli *skli_new (void (*skli_rm_key_fn) (int key),
			      void (*skli_rm_value_fn) (union skl_value val));

/* free tree pointer */
extern struct sklp *sklp_rm (struct sklp *skl);

/* free tree string */
extern struct skls *skls_rm (struct skls *skl);

/* free tree int */
extern struct skli *skli_rm (struct skli *skl);

/* add node in pointer tree */
extern struct sklp_n *sklp_add (struct sklp *skl, void *ptr);

/* add node in string tree */
extern struct skls_n *skls_add (struct skls *skl, char *str);

/* add node in int tree */
extern struct skli_n *skli_add (struct skli *skl, int i);

/* find data */
extern struct sklp_n *sklp_find (struct sklp *skl, void *ptr);

/* find data */
extern struct skls_n *skls_find (struct skls *skl, char *str);

/* find data */
extern struct skli_n *skli_find (struct skli *skl, int i);

/* print */
extern void sklp_pr (struct sklp *skl);

/* print */
extern void skls_pr (struct skls *skl);

/* print */
extern void skli_pr (struct skli *skl);

/* start element */
extern struct sklp_n *sklp_min (struct sklp *skl);

/* start element */
extern struct skls_n *skls_min (struct skls *skl);

/* start element */
extern struct skli_n *skli_min (struct skli *skl);

/* next entry */
extern struct sklp_n *sklp_next (struct sklp *skl, struct sklp_n *n);

/* next entry */
extern struct skls_n *skls_next (struct skls *skl, struct skls_n *n);

/* next entry */
extern struct skli_n *skli_next (struct skli *skl, struct skli_n *n);

#endif

/* end. */

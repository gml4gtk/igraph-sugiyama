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

#include "gui.h"
#include "skiplist.h"

/* db */
static struct skls *gunode = NULL;

/* */
struct unode *
uniqnode (char *str)
{
  size_t len = 0;
  struct skls_n *node = NULL;
  if (str == NULL)
    {
      return (NULL);
    }
  len = strlen (str);
  if (len == 0)
    {
      /* "" string */
      return (NULL);
    }
  if (gunode == NULL)
    {
      gunode = skls_new (NULL, NULL);
    }
  node = skls_find (gunode, str);
  if (node)
    {
      return ((struct unode *) node->value.p);
    }
  return (NULL);
}

/* */
void
uniqnode_clear (void)
{
  gunode = skls_rm (gunode);
  return;
}

/* */
void
uniqnode_add (char *str, struct unode *un)
{
  size_t len = 0;
  struct skls_n *node = NULL;
  if (str == NULL)
    {
      return;
    }
  len = strlen (str);
  if (len == 0)
    {
      return;
    }
  if (gunode == NULL)
    {
      gunode = skls_new (NULL, NULL);
    }
  /* multiple same key entries possible */
  node = skls_add (gunode, str);
  if (node)
    {
      node->value.p = (void *) un;
    }
  return;
}

/* end. */


/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <string.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif


#include "splay-tree.h"
/* #include "mem.h" */


/* forward decl. */
static struct splay_tree_node_n *splay (splay_tree sp, splay_tree_key key);

/* delete whole sp tree */
splay_tree
splay_tree_delete (splay_tree sp)
{
  splay_tree_node spn = (splay_tree_node) 0;
  splay_tree_node spn2 = (splay_tree_node) 0;

  if (sp == (splay_tree) 0)
    {
      return ((splay_tree) 0);
    }

  /* if there is data */
  if (sp->root)
    {
      /* for every node, this does not cause stack smashing */
      spn = splay_tree_min (sp);
      while (spn)
	{
	  spn2 = splay_tree_successor (sp, spn->key);
	  splay_tree_remove (sp, spn->key);
	  spn = spn2;
	}
    }

  /* wipe the pointers in the struct to make valgrind happy */
  sp->root = (splay_tree_node) 0;

  /* The comparision function.  */
  sp->comp = (splay_tree_compare_fn) 0;

  /* The deallocate-key function.  NULL if no cleanup is necessary.  */
  sp->delete_key = (splay_tree_delete_key_fn) 0;

  /* The deallocate-value function.  NULL if no cleanup is necessary.  */
  sp->delete_value = (splay_tree_delete_value_fn) 0;

  /* myfree ((void *) sp, __FUNCTION__, __LINE__); */ free((void *)sp);

  return ((splay_tree) 0);
}

/* Allocate a new splay tree, using COMPARE_FN to compare nodes,
   DELETE_KEY_FN to deallocate keys, and DELETE_VALUE_FN to deallocate
   values.  */

splay_tree
splay_tree_new (splay_tree_compare_fn compare_fn, splay_tree_delete_key_fn delete_key_fn, splay_tree_delete_value_fn delete_value_fn)
{
  splay_tree sp = (splay_tree) 0;

  /* there must be a compare function, the free() functions are optional */
  if (compare_fn == (splay_tree_compare_fn) 0)
    {
      return ((splay_tree) 0);
    }

  sp = (splay_tree) /* mymalloc (sizeof (struct splay_tree_t), __FUNCTION__, __LINE__); */ calloc (1,sizeof(struct splay_tree_t));

  if (sp == (splay_tree) 0)
    {
      return ((splay_tree) 0);
    }

  /* set root node to use and the functions */
  sp->root = (splay_tree_node) 0;
  sp->comp = compare_fn;
  sp->delete_key = delete_key_fn;
  sp->delete_value = delete_value_fn;

  return ((splay_tree) sp);
}


/* Insert a new node (associating KEY with DATA) into SP.  If a
   previous node with the indicated KEY exists, its data is not replaced
   with the new value.  */

void
splay_tree_insert (splay_tree sp, splay_tree_key key, splay_tree_value value)
{
  splay_tree_node spn = (splay_tree_node) 0;
  int comparison = 0;

  if (sp == (splay_tree) 0)
    {
      /* no tree */
      return;
    }

  spn = splay_tree_lookup (sp, key);

  if (spn != (splay_tree_node) 0)
    {
      /* did already exist */
      return;
    }

  /* Create a new node, and insert it at the root.  */
  spn = (splay_tree_node) /* mymalloc (sizeof (struct splay_tree_node_n), __FUNCTION__, __LINE__); */ calloc (1,sizeof (struct splay_tree_node_n));

  if (spn == (splay_tree_node) 0)
    {
      /* shouldnothappen */
      return;
    }

  /* set node data */
  spn->key = key;
  spn->value = value;

  if (sp->root == (splay_tree_node) 0)
    {
      /* first entry */
      sp->root = spn;
      return;
    }

  /* add in tree */
  comparison = (*sp->comp) (sp->root->key, key);

  if (comparison < 0)
    {
      spn->left = sp->root;
      spn->right = spn->left->right;
      spn->left->right = (splay_tree_node) 0;
    }
  else
    {
      /* > or == */
      spn->right = sp->root;
      spn->left = spn->right->left;
      spn->right->left = (splay_tree_node) 0;
    }

  sp->root = spn;

  return;
}

/* insert and allow duplicates of key */
void
splay_tree_insert_duplicates (splay_tree sp, splay_tree_key key, splay_tree_value value)
{

  if (sp == (splay_tree) 0)
    {
      /* no tree */
      return;
    }

  splay_tree_insert (sp, key, value);

  return;
}

/* Remove KEY from SP.  It is not an error if it did not exist.  */
void
splay_tree_remove (splay_tree sp, splay_tree_key key)
{
  splay_tree_node spn = (splay_tree_node) 0;
  splay_tree_node node = (splay_tree_node) 0;
  splay_tree_node left = (splay_tree_node) 0;
  splay_tree_node right = (splay_tree_node) 0;

  if (sp == (splay_tree) 0)
    {
      /* no tree */
      return;
    }

  if (sp->root == (splay_tree_node) 0)
    {
      /* no data */
      return;
    }

  spn = splay_tree_lookup (sp, key);

  if (spn == (splay_tree_node) 0)
    {
      /* printf ("%s(): key %p not found\n", __FUNCTION__, (void *) key); */
      return;
    }

  /* found entry to delete now in spn */
  node = sp->root;
  left = sp->root->left;
  right = sp->root->right;

  /* One of the children is now the root.  Doesn't matter much
     which, so long as we preserve the properties of the tree.  */
  if (left)
    {
      sp->root = left;
      /* If there was a right child as well, hang it off the
         right-most leaf of the left child.  */
      if (right)
	{
	  while (left->right)
	    {
	      left = left->right;
	    }
	  left->right = right;
	}
    }
  else
    {
      sp->root = right;
    }

  /* free() key if needed */
  if (sp->delete_key)
    {
      /* avoid free(0) */
      if (node->key)
	{
	  (*sp->delete_key) (node->key);
	}
      node->key = (splay_tree_key) 0;
    }

  /* free() value if needed */
  if (sp->delete_value)
    {
      /* avoid free(0) */
      if (node->value)
	{
	  (*sp->delete_value) (node->value);
	}
      node->value = (splay_tree_value) 0;
    }

  /* free() node itself and wipe the pointers */
  node->left = (splay_tree_node) 0;
  node->right = (splay_tree_node) 0;

  /* myfree ((void *) node, __FUNCTION__, __LINE__); */ free ((void *)node);

  return;
}

/* Lookup KEY in SP, returning VALUE if present, and NULL
   otherwise.  */
splay_tree_node
splay_tree_lookup (splay_tree sp, splay_tree_key key)
{
  splay_tree_node spn = (splay_tree_node) 0;

  if (sp == (splay_tree) 0)
    {
      /* no tree */
      return ((splay_tree_node) 0);
    }

  if (sp->root == (splay_tree_node) 0)
    {
      /* no data */
      return ((splay_tree_node) 0);
    }

  if ((*sp->comp) (sp->root->key, key) == 0)
    {
      /* found */
      return ((splay_tree_node) sp->root);
    }

  spn = splay (sp, key);

  if (spn)
    {

      if ((*sp->comp) (sp->root->key, key) == 0)
	{
	  /* found */
	  return ((splay_tree_node) sp->root);
	}
    }

  /* not found */
  return ((splay_tree_node) 0);
}

/* Call FN, passing it the DATA, for every node in SP, following an
   in-order traversal.  If FN every returns a non-zero value, the
   iteration ceases immediately, and the value is returned.
   Otherwise, this function returns 0.
*/

int
splay_tree_foreach (splay_tree sp, splay_tree_foreach_fn fn, void *data)
{
  splay_tree_node spn = (splay_tree_node) 0;
  splay_tree_key spnkey = (splay_tree_key) 0;
  int status = 0;

  /* <nil> splaytree */
  if (sp == (splay_tree) 0)
    {
      return (0);
    }

  /* no data */
  if (sp->root == (splay_tree_node) 0)
    {
      return (0);
    }

  /* no routine() to run */
  if (fn == (splay_tree_foreach_fn) 0)
    {
      return (0);
    }

  /* */
  status = 0;

  spn = splay_tree_min (sp);

  while (spn)
    {
      /* save key if spn disappears */
      spnkey = spn->key;
      status = (*fn) (spn, data);
      if (status)
	{
	  break;
	}
      spn = splay_tree_successor (sp, spnkey);
    }

  /* set if callback() routine set it otherwise 0 */
  return (status);
}


/* Return the node in SP with the smallest key.  */
splay_tree_node
splay_tree_min (splay_tree sp)
{
  splay_tree_node n = (splay_tree_node) 0;

  /* <nil> splaytree */
  if (sp == (splay_tree) 0)
    {
      return ((splay_tree_node) 0);
    }

  /* no data */
  if (sp->root == (splay_tree_node) 0)
    {
      return ((splay_tree_node) 0);
    }

  n = sp->root;

  /* scan l */
  while (n->left)
    {
      n = n->left;
    }

  return ((splay_tree_node) n);
}

/* return 1 if splay tree has data, otherwise 0 */
int
splay_tree_has_data (splay_tree sp)
{
  if (sp == (splay_tree) 0)
    {
      return (0);
    }
  if (sp->root)
    {
      return (1);
    }
  else
    {
      return (0);
    }
}

/* Return the immediate successor KEY, or NULL if there is no
   successor.  KEY need not be present in the tree.  */

splay_tree_node
splay_tree_successor (splay_tree sp, splay_tree_key key)
{
  int comparison = 0;
  splay_tree_node node = (splay_tree_node) 0;

  if (sp == (splay_tree) 0)
    {
      /* no tree */
      return ((splay_tree_node) 0);
    }

  /* If the tree is empty, there is certainly no successor.  */
  if (sp->root == (splay_tree_node) 0)
    {
      return ((splay_tree_node) 0);
    }

  /* Splay the tree around KEY.  That will leave either the KEY
     itself, its predecessor, or its successor at the root.  */
  node = splay (sp, key);

  if (node == (splay_tree_node) 0)
    {
      return ((splay_tree_node) 0);
    }

  /* */
  comparison = (*sp->comp) (sp->root->key, key);

  /* If the successor is at the root, just return it.  */
  if (comparison > 0)
    {
      return ((splay_tree_node) sp->root);
    }

  /* Otherwise, find the leftmost element of the right subtree.  */
  node = sp->root->right;

  if (node)
    {
      while (node->left)
	{
	  node = node->left;
	}
    }

  return ((splay_tree_node) node);
}

/* free() wrappers to free key/value */
void
splay_tree_free_value (splay_tree_value value)
{
  if (value)
    {
      /* myfree ((void *) value, __FUNCTION__, __LINE__); */ free ((void *)value);
    }
  return;
}

void
splay_tree_free_key (splay_tree_key key)
{
  if (key)
    {
      /* myfree ((void *) key, __FUNCTION__, __LINE__); */ free ((void *)key);
    }
  return;
}

/* Splay-tree comparison function, treating the keys as ints.  */

int
splay_tree_compare_ints (splay_tree_key k1, splay_tree_key k2)
{
  if ((int) k1 < (int) k2)
    {
      return ((int) -1);
    }
  else if ((int) k1 > (int) k2)
    {
      return (1);
    }
  else
    {
      return (0);
    }
}

/* Splay-tree comparison function, treating the keys as pointers.
   Note this is possibly not portable on all systems according to standards
   and may have undefined results. there seems no good solution for this.
   (a char datatype does not have to be a single byte in c for example)
*/

int
splay_tree_compare_pointers (splay_tree_key k1, splay_tree_key k2)
{
  /* 0==0 */
  if ((k1 == (splay_tree_key) 0) && (k2 == (splay_tree_key) 0))
    {
      return (0);
    }
  /* possible undefined results at this, says the c standard. has to be understood as (signed char *) */
  if ((char *) k1 < (char *) k2)
    {
      return ((int) -1);
    }
  else if ((char *) k1 > (char *) k2)
    {
      return (1);
    }
  else
    {
      return (0);
    }
}

/* Comparison function for a splay tree in which the keys are strings.
   K1 and K2 have the dynamic type "const char *".  Returns <0, 0, or
   >0 to indicate whether K1 is less than, equal to, or greater than
   K2, respectively.
   similar issues here when as compare pointers and c portable src.
*/

int
splay_tree_compare_strings (splay_tree_key k1, splay_tree_key k2)
{
  const char *s1 = (const char *) k1;
  const char *s2 = (const char *) k2;
  int ret = 0;

  if ((k1 == (splay_tree_key) 0) && (k2 == (splay_tree_key) 0))
    {
      return (0);
    }

  if (s1 == (const char *) 0)
    {
      /* to avoid crashes only */
      return (0);
    }

  if (s2 == (const char *) 0)
    {
      /* to avoid crashes only */
      return (0);
    }

  /* check if same pointer. possible not portable c. */
  if (s1 == s2)
    {
      return (0);
    }

  ret = strcmp (s1, s2);

  return ((int) ret);
}

/* */
static struct splay_tree_node_n *
splay (splay_tree sp, splay_tree_key key)
{
  struct splay_tree_node_n *t = (struct splay_tree_node_n *) 0;
  struct splay_tree_node_n *l = (struct splay_tree_node_n *) 0;
  struct splay_tree_node_n *r = (struct splay_tree_node_n *) 0;
  struct splay_tree_node_n *y = (struct splay_tree_node_n *) 0;
  int comparevalue = 0;
  int comparevalue2 = 0;
  struct splay_tree_node_n tmp = {
    /* The key.  */
    (splay_tree_key) 0,
    /* The value.  */
    (splay_tree_value) 0,
    /* The left and right children, respectively.  */
    (struct splay_tree_node_n *) 0,	/* left */
    (struct splay_tree_node_n *) 0	/* right */
  };

  /* no tree */
  if (sp == (splay_tree) 0)
    {
      return ((struct splay_tree_node_n *) 0);
    }

  /* no data in root. return 0 */
  if (sp->root == (struct splay_tree_node_n *) 0)
    {
      return ((struct splay_tree_node_n *) 0);
    }

  /* current root */
  t = sp->root;

  tmp.left = (struct splay_tree_node_n *) 0;
  tmp.right = (struct splay_tree_node_n *) 0;

  l = &tmp;
  r = &tmp;

labelstart:

  /* */
  comparevalue = (*sp->comp) (key, t->key);

  if (comparevalue < 0)
    {

      if (t->left == (struct splay_tree_node_n *) 0)
	{
	  goto labelend;
	}

      /* */
      comparevalue2 = (*sp->comp) (key, t->left->key);

      if (comparevalue2 < 0)
	{

	  y = t->left;
	  t->left = y->right;
	  y->right = t;
	  t = y;

	  if (t->left == (struct splay_tree_node_n *) 0)
	    {
	      goto labelend;
	    }
	}

      /* */
      r->left = t;
      r = t;
      t = t->left;

    }
  else if (comparevalue > 0)
    {

      if (t->right == (struct splay_tree_node_n *) 0)
	{
	  goto labelend;
	}

      /* */
      comparevalue2 = (*sp->comp) (key, t->right->key);

      if (comparevalue2 > 0)
	{

	  /* */
	  y = t->right;
	  t->right = y->left;
	  y->left = t;
	  t = y;

	  if (t->right == (struct splay_tree_node_n *) 0)
	    {
	      goto labelend;
	    }
	}

      /* */
      l->right = t;
      l = t;
      t = t->right;
    }
  else
    {
      /* here if (comparevalue == 0) */
      goto labelend;
    }

  goto labelstart;

labelend:

  l->right = t->left;
  r->left = t->right;
  t->left = tmp.right;
  t->right = tmp.left;

  sp->root = t;

  return ((struct splay_tree_node_n *) t);
}

/* end */

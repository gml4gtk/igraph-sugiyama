
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


#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H 1

#include <stdint.h>

/* how many bytes can a splay key to index on have max. */
/* typedef unsigned long long int splay_tree_key; */
typedef uintptr_t splay_tree_key;

/* how many bytes can a splay value have max. */
/* typedef unsigned long long int splay_tree_value; */
typedef uintptr_t splay_tree_value;

/* Forward declaration for a tree.  */
typedef struct splay_tree_t *splay_tree;


/* The nodes in the splay tree.  */
struct splay_tree_node_n
{
  /* The key.  */
  splay_tree_key key;

  /* The value.  */
  splay_tree_value value;

  /* The left and right children, respectively.  */
  struct splay_tree_node_n *left;
  struct splay_tree_node_n *right;
};


/* Forward declaration for a node in the tree.  */
typedef struct splay_tree_node_n *splay_tree_node;

/* The type of a function which compares two splay-tree keys.  The
   function should return values as for qsort.  */
typedef int (*splay_tree_compare_fn) (splay_tree_key, splay_tree_key);

/* The type of a function used to deallocate any resources associated
   with the key.  */
typedef void (*splay_tree_delete_key_fn) (splay_tree_key);

/* The type of a function used to deallocate any resources associated
   with the value.  */
typedef void (*splay_tree_delete_value_fn) (splay_tree_value);

/* The type of a function used to iterate over the tree.  */
typedef int (*splay_tree_foreach_fn) (splay_tree_node, void *);

/* The splay tree itself.  */
struct splay_tree_t
{
  /* The root of the tree.  */
  struct splay_tree_node_n *root;

  /* The comparision function.  */
  splay_tree_compare_fn comp;

  /* The deallocate-key function.  NULL if no cleanup is necessary.  */
  splay_tree_delete_key_fn delete_key;

  /* The deallocate-value function.  NULL if no cleanup is necessary.  */
  splay_tree_delete_value_fn delete_value;
};

/* splay routines */
extern splay_tree splay_tree_new (splay_tree_compare_fn fnc, splay_tree_delete_key_fn fndk, splay_tree_delete_value_fn fndv);
extern splay_tree splay_tree_delete (splay_tree sp);
extern void splay_tree_insert (splay_tree sp, splay_tree_key k, splay_tree_value v);
extern void splay_tree_insert_duplicates (splay_tree sp, splay_tree_key k, splay_tree_value v);
extern void splay_tree_remove (splay_tree sp, splay_tree_key key);
extern splay_tree_node splay_tree_lookup (splay_tree sp, splay_tree_key k);
extern int splay_tree_foreach (splay_tree sp, splay_tree_foreach_fn f, void *data);
extern splay_tree_node splay_tree_min (splay_tree sp);

/* Return the immediate successor KEY, or NULL if there is no
   successor.  KEY need not be present in the tree.  */
extern splay_tree_node splay_tree_successor (splay_tree sp, splay_tree_key key);

/* return 1 if splay tree has data, otherwise 0 */
extern int splay_tree_has_data (splay_tree sp);

/* copy splay tree data */
extern void xsplay_tree_copy (splay_tree from_sp, splay_tree to_sp);

/* free() wrappers to free key/value */
extern void splay_tree_free_value (splay_tree_value value);
extern void splay_tree_free_key (splay_tree_key key);

extern int splay_tree_compare_ints (splay_tree_key k1, splay_tree_key k2);
extern int splay_tree_compare_pointers (splay_tree_key k1, splay_tree_key k2);
extern int splay_tree_compare_strings (splay_tree_key k1, splay_tree_key k2);

#endif /* _SPLAY_TREE_H */

/* end */

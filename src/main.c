/* -*- mode: C -*-  */
/* 
   IGraph library.
   Copyright (C) 2006-2012  Gabor Csardi <csardi.gabor@gmail.com>
   334 Harvard st, Cambridge MA, 02139 USA
   
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
   Foundation, Inc.,  51 Franklin Street, Fifth Floor, Boston, MA 
   02110-1301 USA

*/

#include <igraph.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "gui.h"
#include "color.h"
#include "uniqstring.h"
#include "uniqnode.h"

/* test from libigraph result should match test data file */
static void
maintest (void)
{
  igraph_t g, extd_g;
  igraph_matrix_t coords;
  igraph_vector_t edgelist, extd_edgelist, extd_to_orig_eids;
  igraph_vector_t layers;

  igraph_matrix_init (&coords, 0, 0);
  igraph_vector_init (&extd_to_orig_eids, 0);

  /* Layout on simple graph with predefined layers */
  igraph_vector_init_int_end (&layers, -1, 0, 1, 1, 2, 3, 3, 4, 4, 5, -1);
  igraph_vector_init_int_end (&edgelist, -1, 0, 1, 0, 2, 0, 3, 1, 2, 2, 2, 1, 4, 2, 5, 4, 6, 5, 7, 6, 8, 7, 8, 3, 8, 8, 1, 8, 2, -1);
  igraph_create (&g, &edgelist, 0, 1);

  igraph_layout_sugiyama (&g, &coords, 0, 0, &layers,
			  /* hgap = */ 1,
			  /* vgap = */ 1,
			  /* maxiter = */ 100,
			  /* weights = */ 0);
  igraph_matrix_print (&coords);
  printf ("===\n");

  /* Same, but this time also return the extended graph */
  igraph_layout_sugiyama (&g, &coords, &extd_g, &extd_to_orig_eids, &layers,
			  /* hgap = */ 1,
			  /* vgap = */ 1,
			  /* maxiter = */ 100,
			  /* weights = */ 0);
  igraph_matrix_print (&coords);
  printf ("===\n");
  igraph_vector_init (&extd_edgelist, 0);
  igraph_get_edgelist (&extd_g, &extd_edgelist, 0);
  igraph_vector_print (&extd_edgelist);
  igraph_vector_destroy (&extd_edgelist);
  igraph_destroy (&extd_g);
  printf ("===\n");
  igraph_vector_print (&extd_to_orig_eids);
  printf ("===\n");

  igraph_vector_destroy (&layers);

  /* Same, but with automatic layering */
  igraph_layout_sugiyama (&g, &coords, 0, 0, 0,
			  /* hgap = */ 1,
			  /* vgap = */ 1,
			  /* maxiter = */ 100,
			  /* weights = */ 0);
  igraph_matrix_print (&coords);
  printf ("===\n");

  /* Layering with gaps in it */
  igraph_vector_init_int_end (&layers, -1, 0, 2, 2, 4, 6, 6, 12, 12, 15, -1);
  igraph_layout_sugiyama (&g, &coords, 0, 0, &layers,
			  /* hgap = */ 1,
			  /* vgap = */ 1,
			  /* maxiter = */ 100,
			  /* weights = */ 0);
  igraph_matrix_print (&coords);
  igraph_vector_destroy (&layers);
  printf ("===\n");

  igraph_vector_destroy (&edgelist);
  igraph_matrix_destroy (&coords);
  igraph_vector_destroy (&extd_to_orig_eids);
  igraph_destroy (&g);

  return;
}


static void
matrixprint2 (const igraph_matrix_t * m)
{
  long int nr = igraph_matrix_nrow (m);
  long int nc = igraph_matrix_ncol (m);
  long int i, j;
  int nn = 0;
  int maxl = 0;
  for (i = 0; i < nr; i++)
    {
      printf ("node %d\t", nn);
      nn++;
      for (j = 0; j < nc; j++)
	{
	  if (j != 0)
	    {
	      putchar (' ');
	    }
	  if (j == 0)
	    {
	      printf ("xpos: %G\t\t", MATRIX (*m, i, j));
	    }
	  if (j == 1)
	    {
	      printf ("level: %G\t", MATRIX (*m, i, j));
	      if ((int) MATRIX (*m, i, j) > maxl)
		{
		  maxl = (int) MATRIX (*m, i, j);
		}
	    }
	}
      printf ("\n");
    }
  printf ("there are %d levels range [0...%d]\n", maxl + 1, maxl);
}

int
main (int argc, char *argv[])
{
  int status = 0;
  int test = 0;
  igraph_t g;
  igraph_t extd_g;
  igraph_matrix_t coords;
  igraph_vector_t edgelist;
  igraph_vector_t extd_edgelist;
  igraph_vector_t extd_to_orig_eids;
  long int n = 0;
  long int i = 0;

  /* rand() init for skiplist.c */
  srand ((unsigned int) time (NULL));

  /* set to 1 to run igraph lib testcode */
  test = 0;
  if (test)
    {
      maintest ();
      return (0);
    }

  igraph_matrix_init (&coords, 0, 0);
  igraph_vector_init (&extd_to_orig_eids, 0);

  if (0)
    {
      igraph_vector_init_int_end (&edgelist, -1,
				  /* */ 0, 1,
				  /* */ 0, 2,
				  /* */ 0, 3,
				  /* */ -1);
      /* VECTOR(edgelist)[0]=1; other way */

    }

  if (1)
    {
      /* sample fixed input graph as edge list */
      igraph_vector_init_int_end (&edgelist, -1,
				  /* edge from node 0 to node 1 */ 0, 1,
				  /* edge from 0 to 2 */ 0, 2,
				  /* edge */ 0, 3,
				  /* */ 1, 2,
				  /* */ 2, 2,
				  /* */ 1, 4,
				  /* */ 2, 5,
				  /* */ 4, 6,
				  /* */ 5, 7,
				  /* */ 6, 8,
				  /* */ 7, 8,
				  /* */ 3, 8,
				  /* */ 8, 1,
				  /* */ 8, 2,
				  /* end marker */ -1);
    }

  igraph_create (&g, &edgelist, 0, 1);

  /* automatic layering with extended graph */
  status = igraph_layout_sugiyama ((const igraph_t *) &g /* graph */ , (igraph_matrix_t *) & coords /* res */ ,
				   (igraph_t *) & extd_g, (igraph_vector_t *) & extd_to_orig_eids,
				   (const igraph_vector_t *) 0 /* layers */ , (igraph_real_t) 1.0 /* hgap */ ,
				   (igraph_real_t) 1.0 /* vgap */ , (long int) 100 /* maxiter */ , (const igraph_vector_t *) 0 /* weights */ );

  printf ("igraph_layout_sugiyama() status=%d\nnode coords:\n", status);
  igraph_matrix_print (&coords);
  matrixprint2 (&coords);

  printf ("input edge list:\n");
  igraph_vector_print (&edgelist);
  n = igraph_vector_size (&edgelist);
  printf ("input edge list has %li elements for %li edges\n", n, n / 2);


  /* edge list with created dummy nodes and edges to it included */
  printf ("ext. edgelist:\n");
  igraph_vector_init (&extd_edgelist, 0);
  igraph_get_edgelist (&extd_g, &extd_edgelist, 0);
  igraph_vector_print (&extd_edgelist);
  n = igraph_vector_size (&extd_edgelist);
  printf ("output edge list has %li elements for %li edges\n", n, n / 2);
  for (i = 0; i < n; i = i + 2)
    {
      printf ("edge %li is from node %d to node %d\n", i / 2, (int) VECTOR (extd_edgelist)[i], (int) VECTOR (extd_edgelist)[i + 1]);
    }
  igraph_vector_destroy (&extd_edgelist);
  igraph_destroy (&extd_g);

  printf ("ext. to orig eid\n");
  igraph_vector_print (&extd_to_orig_eids);

  igraph_vector_destroy (&edgelist);
  igraph_matrix_destroy (&coords);
  igraph_vector_destroy (&extd_to_orig_eids);
  igraph_destroy (&g);

  if (0)
    {
      printf ("colorcode 0x%0x for %s\n", colorcode ("yellow1"), "yellow1");
      printf ("colorcode 0x%0x for %s\n", colorcode ("DarkOrange"), "DarkOrange");
      colorcode_clear ();
    }

  if (0)
    {
      printf ("abc is %p\n", (void *) uniqstring ("abc"));
      printf ("abc is %p\n", (void *) uniqstring ("abc"));
      printf ("Abc is %p\n", (void *) uniqstring ("Abc"));
      printf ("Abc is %s\n", uniqstring ("Abc"));
      uniqstring_clear ();
    }

  if (0)
    {
      uniqnode_add (uniqstring ("abc"), (struct unode *) 0x123);
      printf ("abc = %p\n", (void *) uniqnode ("abc"));
      uniqstring_clear ();
      uniqnode_clear ();
    }

  /* gtk */
  if (1)
    {
      gui (argc, argv);
    }

  return (0);
}

/* end. */

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


#include "config.h"

#include <stdio.h>
#include <string.h>

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <cairo.h>

#include "gui.h"
#include "gui2.h"

static void doredraw_subgrapharea (cairo_t * crp);
static void doredraw_nodes (cairo_t * crp);
static void doredraw_edges (cairo_t * crp);

/* redraw whole drawing on screen area */
void
doredraw (cairo_t * crp)
{
  int i = 0;
  int ld = 0;
  int hd = 0;
  int ntodo = 0;

  /* mark which layers to draw */
  for (i = 0; i < dli_nlevels; i++)
    {
      ld = dlip[i]->y0 - vymin;
      hd = dlip[i]->y0 + dlip[i]->ht - vymin;
      if (((int) (ld * zfactor) >= 0 && (int) (hd * zfactor) < drawing_area_ysize)
	  || ((int) (ld * zfactor) <= 0 && (int) (hd * zfactor) >= 0) || ((int) (ld * zfactor) < drawing_area_ysize
									  && (int) (hd * zfactor) >= drawing_area_ysize))
	{
	  ntodo = (ntodo + 1);
	  dlip[i]->draw = 1;
	}
      else
	{
	  dlip[i]->draw = 0;
	}
    }

  /* check */
  if (ntodo == 0)
    {
      /* white fill drawing area */
      cairo_set_source_rgb (crp, 1.0, 1.0, 1.0);
      cairo_fill (crp);
      cairo_stroke (crp);
      return;
    }

  /* select whole screen to fill with background color */
  cairo_set_source_rgb (crp, bgcr / 255.0, bgcg / 255.0, bgcb / 255.0);
  cairo_rectangle (crp, 0, 0, drawing_area_xsize, drawing_area_ysize);
  cairo_fill (crp);
  cairo_stroke (crp);

  /* use zoom slider drawing scale */
  cairo_scale (crp, zfactor, zfactor);

  /* draw outline of subgraphs */
  doredraw_subgrapharea (crp);

  /* draw nodes */
  doredraw_nodes (crp);

  /* draw edge lines */
  doredraw_edges (crp);

  return;
}

/* area of subgraphs with green box lines */
static void
doredraw_subgrapharea (cairo_t * crp)
{
  return;
}

static void
doredraw_nodes (cairo_t * crp)
{
  return;
}

static void
doredraw_edges (cairo_t * crp)
{
  return;
}

/* end. */

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

#ifndef GUI_H
#define GUI_H 1

#ifndef SPLAY_TREE_H
#include "splay-tree.h"
#endif

/* parsed node */
struct unode
{
  splay_tree sp_poe;		/* node is part of edge */
  splay_tree sp_tc;		/* connection points at top of node */
  splay_tree sp_bc;		/* connection points at bottom of node */
  int number;			/* uniq node number for regular and dummy nodes */
  char *name;			/* uniq name of node */
  char *utf8name;		/* utf-8 uniq name of node */
  char *label;			/* display name of node */
  char *utf8label;		/* utf-8 display name of node */
  char *url;			/* url like "http://www.example.org" to link with node for image map data */
  int color;			/* argb of node background color */
  struct usubg *rootedon;	/* node is part of subgraph or NULL if in rootgraph */
  int level;			/* relative depth level of node */
  int pos;			/* relative horizontal position of node */
  int nse;			/* number of selfedges at node */
  int indegree;			/* number of incoming edges to node */
  int outdegree;		/* number of outgoing edges from node */
  int textcolor;		/* color of label text */
  char *fontsize;		/* size of font for label text range 1..100 and 0 is gtk default */
  char *fontname;		/* name of font to use default "serif" used if NULL */
  int tx;			/* textarea x-size */
  int ty;			/* textarea y-size */
  int bbx;			/* node area size with text x-size */
  int bby;			/* node area size with text y-size */
  int objectnr;			/* node number used in dia output */

  /* gcc unsigned int is 32bits */
  struct
  {
    /* 0-9 */
    unsigned int sumnode:1;	/* set if node is a subgraph summary node */
    unsigned int dummynode:1;	/* set if node is a dummy node without label */
    unsigned int singlenode:1;	/* set if node has zero in+out degree but may have selfedges in nse */
    unsigned int edgelabel:1;	/* node is edgelabel to draw different */
    unsigned int parseerror:1;	/* set if node is a parse error message */
    unsigned int defbynode:1;	/* set if node is defined by node statement */
    unsigned int defbyedge:1;	/* set if node is defined by edge statement */
    unsigned int textitalic:1;	/* label text is in slant italic */
    unsigned int textoblique:1;	/* label text is in slant oblique */
    unsigned int textbold:1;	/* label text is in weight bold */
    /* 10-19 */
    unsigned int reloc:1;	/* if set node is relocated by subgraph during parse */
    unsigned int done:1;	/* set if node is processed */
    unsigned int visible:1;	/* set if node is in output drawing */
    unsigned int longedge:1;	/* set if node is part of a long edge */
    unsigned int horedge:1;	/* set if node is part of horizontal edge */
    unsigned int txy:1;		/* set if textarea (x,y) is calculated */
    unsigned int shape:5;	/* node shape, box ellips etc. */
    unsigned int altcolor:1;	/* draw in alt color grey if set */
    unsigned int textshadow:1;	/* label text is shadowed draw (for summary nodes) */
    /* 20-29 */
    unsigned int deletenode:1;	/* virtual node in parsed list to delete at re-layout */
    unsigned int skip:1;	/* skip node from input if set */
    unsigned int bit21:1;
    unsigned int bit22:1;
    unsigned int bit23:1;
    unsigned int bit24:1;
    unsigned int bit25:1;
    unsigned int bit26:1;
    unsigned int bit27:1;
    unsigned int bit28:1;
    unsigned int bit29:1;
    /* 30-31 */
    unsigned int bit30:1;
    unsigned int bit31:1;
  } bitflags;

  int x0;			/* x0 where node drawing area starts */
  int x1;			/* x1 center of node */
  int y1;			/* y1 top of node */
  int y2;			/* y2 bottom of node */

};

/* parsed edge */
struct uedge
{
  int number;			/* uniq number */
  struct unode *fn;		/* from node */
  struct unode *tn;		/* to node */
  struct usubg *rootedon;	/* edge is defined in subgraph but may be located in other subgraph */
  int color;			/* color of edge line a/r/g/b */
  char *label;			/* edgelabel or null */
  char *utf8label;		/* utf-8 edgelabel or null */
  int textcolor;		/* color of label text */
  char *fontsize;		/* size of font for label text range 1..100 and 0 is gtk default */
  char *fontname;		/* name of font to use default "serif" used if NULL */
  int tx;			/* textarea x-size */
  int ty;			/* textarea y-size */
  int bbx;			/* total area size with text x-size */
  int bby;			/* total area size with text y-size */
  int repeated;			/* edge is n times repeated in input graph */

  struct
  {
    unsigned int selfedge:1;	/* set if edge is a selfedge */
    unsigned int textbold:1;	/* label text is in weight bold */
    unsigned int textitalic:1;	/* label text is in slant italic */
    unsigned int textoblique:1;	/* label text is in slant oblique */
    unsigned int done:1;	/* set if edge is processed */
    unsigned int visible:1;	/* set if edge is in output drawing */
    unsigned int reversed:1;	/* if set edge is direction reversed */
    unsigned int repeated:1;	/* set if edge is repeated in input graph */
    unsigned int longedge:1;	/* set if edge is part of a long edge */
    unsigned int horedge:1;	/* set if edge is part of horizontal edge */
    /* 10 */
    unsigned int thickness:3;	/* edge line thickness range 0...7 default is 0 */
    unsigned int arrows:1;	/* if set draw arrows at edge */
    unsigned int botharrows:1;	/* if set draw arrows at both sides of edge */
    unsigned int multarrows:1;	/* if set draw multiple arrows at long edge */
    unsigned int style:3;	/* solid, dotted, dashed or invisible style of edge line */
    unsigned int altcolor:1;	/* if set draw in alt color grey */
    /* 20 */
    unsigned int txy:1;		/* set if textarea (x,y) is calculated */
    unsigned int insidegraph:1;	/* set if from/to node is in same root or subgraph */
    unsigned int skip:1;	/* skip edge from input if set */
    /* max. 32 bits */
  } bitflags;

};

/* parsed subgraph */
struct usubg
{
  int number;			/* uniq number */
  char *name;			/* uniq name of subgraph */
  char *utf8name;		/* utf-8 uniq name of subgraph */
  char *label;			/* display name of subgraph */
  struct usubg *rootsubgraph;	/* subgraph in root graph where subsubgraphs start from */
  struct usubg *rootedon;	/* subgraph in other subgraph or root graph if NULL */
  struct unode *summaryn;	/* folded summary node */
  splay_tree sp_nl;		/* nodes in this subgraph */
  splay_tree sp_el;		/* edges connecting to this subgraph */
  splay_tree sp_sg;		/* subgraphs rooted in this subgraph from input parsed data */
  splay_tree sp_wsg;		/* subgraphs rooted in this subgraph working on */
  int aminx;			/* subgraph area min. x point */
  int aminy;			/* subgraph area min. y point */
  int amaxx;			/* subgraph area max. x point */
  int amaxy;			/* subgraph area max. y point */

  struct
  {
    unsigned int folded:1;	/* if set subgraph is folded in summary node un */
    unsigned int summary:1;	/* if set summary node is visible */
    unsigned int done:1;	/* set if subgraph is processed */
    unsigned int visible:1;	/* set if subgraph is in output drawing */
    unsigned int adone:1;	/* set if subgraph area drawing is done */
    unsigned int txy:1;		/* set if textarea (x,y) is calculated */
    unsigned int skip:1;	/* skip subgraph from input if set */
    /* max. 32 bits */
  } bitflags;

};

/* list with nodes */
struct dln
{
  struct dln *next;
  struct unode *un;
};

/* list with nodes to draw */
struct drawn
{
  struct unode *un;		/* node data */
  struct drawn *next;
};

/* list with edges to draw */
struct drawe
{
  struct uedge *ue;		/* edge data */
  struct drawe *next;
};

/* draw nodes linkage */
struct ddn
{
  struct drawn *dn;
  struct ddn *next;
};

/* draw edges linkage */
struct dde
{
  struct drawe *de;
  struct dde *next;
};

/*
 * in draw layer info and node info are these (x,y) points:
 *
 * node coordinates are:
 *
 * dlip[layer]->x0
 * dlip[layer]->y0         un->x0 un->x1
 *             +--------------+----+---------------------+
 *             |                   |
 *             |              +---------+ un->y1
 *      dlip[layer]->hn       | node un |
 *             |              +---------+ un->y2
 *             |                   |
 *             +-------------------+----------------------+ dlip->layer[i]->wn x-size
 *             | y=(dlip[layer]->y0+dlip[layer]->hn)
 *             |
 *     dlip[layer]->he   edges area / \ or | lines
 *             |
 *             |
 *             +------------------------------------------+
 *             y=(dlip[layer]->y0+dlip[layer]ht)
 *
 * node x size is un->bbx
 * node y size is un->bby
 */
struct dli
{
  unsigned int nnodes;		/* number of nodes in level */
  unsigned int nedges;		/* number of edges in level including invisible edges */
  unsigned int ncross;		/* number of crossing edges in layer */
  struct ddn *nl;		/* nodes list */
  struct ddn *nl_end;		/* nodes list end */
  struct dde *el;		/* edges list */
  struct dde *el_end;		/* edges list end */
  int wn;			/* total x size of layer nodes with x spacing */
  int hn;			/* total y size of layer nodes */
  int he;			/* edge area y size */
  int ht;			/* total height of layer is node+edge height */
  int x0;			/* x where layer starts */
  int y0;			/* y where layer starts */
  unsigned int draw;		/* if set draw layer nodes and edges */

};


/* run gtk+ gui until stopped with quit */
extern void gui (int argc, char *argv[]);

extern int drawing_area_xsize;
extern int drawing_area_ysize;
extern int vxmin;
extern int vymin;
extern double zfactor;
extern int dli_nlevels;
extern struct dli **dlip;
extern int bgcr;
extern int bgcg;
extern int bgcb;

#endif

/* end. */

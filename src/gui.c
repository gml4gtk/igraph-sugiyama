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

/* This can be configured here: the starting (x,y) size of the main window */
#define TOP_LEVEL_WINDOW_XSIZE 500
#define TOP_LEVEL_WINDOW_YSIZE 430

/* */
#define PACKPADDING 0

#include "config.h"

#include <stdio.h>
#include <string.h>

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <cairo.h>

#include "gui.h"
#include "gui2.h"
#include "nes.h"

/* top level window */
static GtkWidget *mainwindow1 = (GtkWidget *) 0;

/* where to draw */
static GtkWidget *drawingarea1 = (GtkWidget *) 0;

/* sliders */
#if GTK_HAVE_API_VERSION_2
static GtkObject *adjvscale1 = NULL;
static GtkObject *adjvscale2 = NULL;
static GtkObject *adjhscale1 = NULL;
#endif

#if GTK_HAVE_API_VERSION_3
static GtkAdjustment *adjvscale1 = NULL;
static GtkAdjustment *adjvscale2 = NULL;
static GtkAdjustment *adjhscale1 = NULL;
#endif

/* last file open dir */
static char *lastdir = (char *) 0;

/* if set thee is valid data to draw */
static int drawdata = 0;

/* screen drawing area in pixels */
int drawing_area_xsize = 0;
int drawing_area_ysize = 0;

/* (x,y) offset changed by sliders */
int vxmin = 0;
int vymin = 0;

/* drawing zoom factor */
double zfactor = 1.0;

/* draw levels */
int dli_nlevels = 0;
struct dli **dlip = NULL;

/* rgb background color */
int bgcr = 0xff;
int bgcg = 0xff;
int bgcb = 0xff;

/* finally stop the gui */
static void top_level_window_main_quit (void);
static void on_top_level_window_quit1_activate (GtkMenuItem * menuitem, gpointer user_data);
static void on_top_level_window_open1_activate (GtkMenuItem * menuitem, gpointer user_data);

#if GTK_HAVE_API_VERSION_2
/* redraw drawing area */
static gboolean on_top_level_window_drawingarea1_expose_event (GtkWidget * widget, GdkEventExpose * event, gpointer user_data);
#endif
#if GTK_HAVE_API_VERSION_3
/* redraw drawing area */
static gboolean on_top_level_window_drawingarea1_draw_event (GtkWidget * widget, cairo_t * crdraw, gpointer user_data);
#endif
/* slider zoom factor */
static void on_vscale1_changed (GtkAdjustment * adj);
/* slider y pos */
static void on_vscale2_changed (GtkAdjustment * adj);
/* slider x pos */
static void on_hscale1_changed (GtkAdjustment * adj);

/* run gtk+ gui until stopped with quit */
void
gui (int argc, char *argv[])
{
  int status = 0;
  GtkWidget *vbox1;
  /* - */
  GtkWidget *menubar1;
  GtkWidget *menuitem1;
  GtkWidget *menuitem1_menu;
  GtkWidget *open1;
  GtkWidget *quit1;
  /* - */
  GtkWidget *hbox1;
  GtkWidget *vscale1;
  GtkWidget *vscale2;
  GtkWidget *hscale1;
  /* - */

#if !GLIB_CHECK_VERSION (2, 36, 0)
  /* for GDBus */
  g_type_init ();
#endif

  /*
   *    gtk_init (&argc, &argv);
   *
   * calls the function gtk_init(gint *argc, gchar ***argv) which will be called in all GTK applications. 
   * This sets up a few things for us such as the default visual and color map and then proceeds to call 
   * gdk_init(gint *argc, gchar ***argv). This function initializes the library for use, sets up default 
   * signal handlers, and checks the arguments passed to your application on the command line, 
   * looking for one of the following:
   *
   *    * --gtk-module
   *    * --g-fatal-warnings
   *    * --gtk-debug
   *    * --gtk-no-debug
   *    * --gdk-debug
   *    * --gdk-no-debug
   *    * --display
   *    * --sync
   *    * --no-xshm
   *    * --name
   *    * --class
   *
   * It removes these from the argument list, leaving anything it does not recognize for your application 
   * to parse or ignore. This creates a set of standard arguments accepted by all GTK applications.
   *
   */

  /* do gtk init, gtk will grab the gtk specific options on command line */
  status = gtk_init_check (&argc, &argv);

  if (status == FALSE)
    {
      printf ("%s is in console mode and need in graphical mode to run\n", argv[0]);
      fflush (stdout);
      return;
    }

  /* top level outer window */
  mainwindow1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);

  /* make sure to exit oke. */
  g_signal_connect (G_OBJECT (mainwindow1), "destroy", G_CALLBACK (top_level_window_main_quit), NULL);

  /* needed for the cairo drawing */
  gtk_widget_set_app_paintable (mainwindow1, TRUE);

  /* use package string program name as set by configure in config.h */
  gtk_window_set_title (GTK_WINDOW (mainwindow1), PACKAGE_STRING);

  /* pre-set some size */
  gtk_window_set_default_size (GTK_WINDOW (mainwindow1), TOP_LEVEL_WINDOW_XSIZE, TOP_LEVEL_WINDOW_YSIZE);

  /* --- */

  /* vbox1 is a menu bar */
#if GTK_HAVE_API_VERSION_2
  vbox1 = gtk_vbox_new ( /* homogeneous */ FALSE, /* spacing */ 0);
  gtk_container_add (GTK_CONTAINER (mainwindow1), vbox1);
  gtk_widget_show (vbox1);
#endif

#if GTK_HAVE_API_VERSION_3
  vbox1 = gtk_box_new (GTK_ORIENTATION_VERTICAL, /* spacing */ 0);
  gtk_container_add (GTK_CONTAINER (mainwindow1), vbox1);
  gtk_widget_show (vbox1);
#endif

  /* menu bar in vbox1 */
  menubar1 = gtk_menu_bar_new ();
  gtk_box_pack_start ( /* box */ GTK_BOX (vbox1), /* child */ menubar1,
		      /* expand */ FALSE, /* fill */ FALSE,	/* padding */
		      PACKPADDING);
  gtk_widget_show (menubar1);

  /* --- */

  /* menu items in menu bar in vbox1 */
  menuitem1 = gtk_menu_item_new_with_mnemonic ("File");
  gtk_container_add (GTK_CONTAINER (menubar1), menuitem1);
  gtk_widget_show (menuitem1);

  /* --- */

  /* 'file' sub menu in menu items in menu bar in vbox1 */
  menuitem1_menu = gtk_menu_new ();
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitem1), menuitem1_menu);

  /* --- */

  /* 'open' in 'file' sub menu in menu items in menu bar in vbox1 */
  open1 = gtk_menu_item_new_with_mnemonic ("Open");
  gtk_container_add (GTK_CONTAINER (menuitem1_menu), open1);
  gtk_widget_show (open1);

  /* run this routine when selected 'open' in 'file' menu */
  g_signal_connect (G_OBJECT (open1), "activate", G_CALLBACK (on_top_level_window_open1_activate), NULL);

  /* 'quit' in 'file' sub menu in menu items in menu bar in vbox1 */
  quit1 = gtk_menu_item_new_with_mnemonic ("Quit");
  gtk_container_add (GTK_CONTAINER (menuitem1_menu), quit1);
  gtk_widget_show (quit1);

  /* run this routine when selected 'quit' in 'file' menu */
  g_signal_connect (G_OBJECT (quit1), "activate", G_CALLBACK (on_top_level_window_quit1_activate), NULL);

  /* --- */

  /* add next area to the vbox1 */
#if GTK_HAVE_API_VERSION_2
  hbox1 = gtk_hbox_new ( /* homogeneous */ FALSE, /* spacing */ 0);
  gtk_box_pack_start ( /* box */ GTK_BOX (vbox1), /* child */ hbox1,
		      /* expand */ TRUE, /* fill */ TRUE,	/* padding */
		      PACKPADDING);
  gtk_widget_show (hbox1);
#endif

#if GTK_HAVE_API_VERSION_3
  hbox1 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, /* spacing */ 0);
  gtk_box_pack_start ( /* box */ GTK_BOX (vbox1), /* child */ hbox1,
		      /* expand */ TRUE, /* fill */ TRUE,	/* padding */
		      PACKPADDING);
  gtk_widget_show (hbox1);
#endif

  /* where to draw in hbox1 */
  drawingarea1 = gtk_drawing_area_new ();
  gtk_box_pack_start ( /* box */ GTK_BOX (hbox1), /* child */ drawingarea1,
		      /* expand */ TRUE, /* fill */ TRUE,	/* padding */
		      PACKPADDING);
  gtk_widget_show (drawingarea1);

#if GTK_HAVE_API_VERSION_2
  g_signal_connect (G_OBJECT (drawingarea1), "expose_event", G_CALLBACK (on_top_level_window_drawingarea1_expose_event), NULL);
#endif

#if GTK_HAVE_API_VERSION_3
  g_signal_connect (G_OBJECT (drawingarea1), "draw", G_CALLBACK (on_top_level_window_drawingarea1_draw_event), NULL);
#endif

  /* vertical slider in hbox1 for the y position range 0...100% of full image size */
  adjvscale2 = gtk_adjustment_new (0, 0, 100, 0, 0, 0);

#if GTK_HAVE_API_VERSION_2
  vscale2 = gtk_vscale_new (GTK_ADJUSTMENT (adjvscale2));
  g_signal_connect (G_OBJECT (adjvscale2), "value_changed", GTK_SIGNAL_FUNC (on_vscale2_changed), NULL);
  gtk_box_pack_start ( /* box */ GTK_BOX (hbox1), /* child */ vscale2,
		      /* expand */ FALSE, /* fill */ TRUE,	/* padding */
		      PACKPADDING);
  gtk_scale_set_draw_value (GTK_SCALE (vscale2), FALSE);
  gtk_widget_show (vscale2);
#endif

#if GTK_HAVE_API_VERSION_3
  vscale2 = gtk_scale_new (GTK_ORIENTATION_VERTICAL, GTK_ADJUSTMENT (adjvscale2));
  g_signal_connect (G_OBJECT (adjvscale2), "value_changed", G_CALLBACK (on_vscale2_changed), NULL);
  gtk_box_pack_start ( /* box */ GTK_BOX (hbox1), /* child */ vscale2,
		      /* expand */ FALSE, /* fill */ TRUE,	/* padding */
		      PACKPADDING);
  gtk_scale_set_draw_value (GTK_SCALE (vscale2), FALSE);
  gtk_widget_show (vscale2);
#endif

  /* vertical slider in hbox1 for the zoom factor 50% is 1:1 */
  adjvscale1 = gtk_adjustment_new (50, 0, 100, 0, 0, 0);

#if GTK_HAVE_API_VERSION_2
  vscale1 = gtk_vscale_new (GTK_ADJUSTMENT (adjvscale1));
  g_signal_connect (G_OBJECT (adjvscale1), "value_changed", GTK_SIGNAL_FUNC (on_vscale1_changed), NULL);
  gtk_box_pack_start ( /* box */ GTK_BOX (hbox1), /* child */ vscale1,
		      /* expand */ FALSE, /* fill */ TRUE,	/* padding */
		      PACKPADDING);
  gtk_scale_set_draw_value (GTK_SCALE (vscale1), FALSE);
  gtk_widget_show (vscale1);
#endif

#if GTK_HAVE_API_VERSION_3
  vscale1 = gtk_scale_new (GTK_ORIENTATION_VERTICAL, GTK_ADJUSTMENT (adjvscale1));
  g_signal_connect (G_OBJECT (adjvscale1), "value_changed", G_CALLBACK (on_vscale1_changed), NULL);
  gtk_box_pack_start ( /* box */ GTK_BOX (hbox1), /* child */ vscale1,
		      /* expand */ FALSE, /* fill */ TRUE,	/* padding */
		      PACKPADDING);
  gtk_scale_set_draw_value (GTK_SCALE (vscale1), FALSE);
  gtk_widget_show (vscale1);
#endif

  /* horizontal scroller 0..100% of drawing size */
  adjhscale1 = gtk_adjustment_new (0, 0, 100, 0, 0, 0);

#if GTK_HAVE_API_VERSION_2
  hscale1 = gtk_hscale_new (GTK_ADJUSTMENT (adjhscale1));
  g_signal_connect (G_OBJECT (adjhscale1), "value_changed", GTK_SIGNAL_FUNC (on_hscale1_changed), NULL);
  gtk_box_pack_start ( /* box */ GTK_BOX (vbox1), /* child */ hscale1,
		      /* expand */ FALSE, /* fill */ TRUE,	/* padding */
		      PACKPADDING);
  gtk_scale_set_draw_value (GTK_SCALE (hscale1), FALSE);
  gtk_widget_show (hscale1);
#endif

#if GTK_HAVE_API_VERSION_3
  hscale1 = gtk_scale_new (GTK_ORIENTATION_HORIZONTAL, GTK_ADJUSTMENT (adjhscale1));
  g_signal_connect (G_OBJECT (adjhscale1), "value_changed", G_CALLBACK (on_hscale1_changed), NULL);
  gtk_box_pack_start ( /* box */ GTK_BOX (vbox1), /* child */ hscale1,
		      /* expand */ FALSE, /* fill */ TRUE,	/* padding */
		      PACKPADDING);
  gtk_scale_set_draw_value (GTK_SCALE (hscale1), FALSE);
  gtk_widget_show (hscale1);
#endif

  /* --- */

  /* --- */

  /* put on screen */
  gtk_widget_show (mainwindow1);

  /* interact the gui elements */
  gtk_main ();

  /* back to main() */
  return;
}

/* finally stop the gui */
static void
top_level_window_main_quit (void)
{

  /* stdup'ed copy of last used dir at file->open */
  if (lastdir)
    {
      g_free (lastdir);
      lastdir = (char *) 0;
    }

  /* run the gtk internal routine to stop gtk_main() which is a for(){} loop */
  gtk_main_quit ();

  return;
}

/* 'quit' in 'file' menu activated - sub menu in menu items in menu bar in vbox1 */
static void
on_top_level_window_quit1_activate (GtkMenuItem * menuitem, gpointer user_data)
{
  if (menuitem)
    {
    }
  if (user_data)
    {
    }
  top_level_window_main_quit ();
  return;
}

/* open in menu */
static void
on_top_level_window_open1_activate (GtkMenuItem * menuitem, gpointer user_data)
{
  GtkWidget *dialog = (GtkWidget *) 0;
  char *file_chooser_filename = (char *) 0;
  char *file_chooser_dir = (char *) 0;
  GtkFileChooser *chooser = NULL;
  char *inputfilename = (char *) 0;

  if (menuitem)
    {
    }

  if (user_data)
    {
    }

#if GTK_HAVE_API_VERSION_2

  /* see gimp source code howto */
  dialog = gtk_file_chooser_dialog_new ("Choose dot, gc or graph File", 0,	/* parent_window */
					GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);

#endif

#if GTK_HAVE_API_VERSION_3

  /* see gimp source code howto */
  dialog = gtk_file_chooser_dialog_new ("Choose dot, gv or graph File", GTK_WINDOW (mainwindow1) /* parent_window */ ,
					GTK_FILE_CHOOSER_ACTION_OPEN, "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, NULL);

#endif

  chooser = GTK_FILE_CHOOSER (dialog);

  /* use same dir if opened in earlier dir */
  if (lastdir)
    {
      gtk_file_chooser_set_current_folder (chooser, lastdir);
    }

  /* run the window to select a input file */
  if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
    {
      /* open button */
      file_chooser_filename = (char *) gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
      file_chooser_dir = (char *) gtk_file_chooser_get_current_folder (chooser);
    }
  else
    {
      /* cancel button */
      (void) gtk_widget_destroy (dialog);
      return;
    }

  /* */
  (void) gtk_widget_destroy (dialog);

  /* update last-used-dir */
  if (file_chooser_dir)
    {
      if (lastdir)
	{
	  (void) g_free (lastdir);
	}
      lastdir = g_strdup (file_chooser_dir);
      (void) g_free (file_chooser_dir);
    }

  /* copy the input filename from gtk */
  if (file_chooser_filename)
    {
      inputfilename = g_strdup (file_chooser_filename);
      (void) g_free (file_chooser_filename);
    }
  else
    {
      return;
    }

  /* no valid data to draw */
  drawdata = 0;

  /* parse input file */

  /* clear all data just before parsing new data or random data */
  prepare4newdata ();

  /* valid data to draw */
  drawdata = 1;

  /* input filename is not saved */
  (void) g_free (inputfilename);

  return;
}


/* slider zoom factor */
static void
on_vscale1_changed (GtkAdjustment * adj)
{
  return;
}

/* slider y pos */
static void
on_vscale2_changed (GtkAdjustment * adj)
{
  return;
}

/* slider x pos */
static void
on_hscale1_changed (GtkAdjustment * adj)
{
  return;
}

#if GTK_HAVE_API_VERSION_2
/* redraw drawing area */
static gboolean
on_top_level_window_drawingarea1_expose_event (GtkWidget * widget, GdkEventExpose * event, gpointer user_data)
{
  cairo_t *crdraw = NULL;
  gint w = 0;			/* xsize of drawing area */
  gint h = 0;			/* ysize of drawing area */

  if (widget)
    {
    }

  if (event)
    {
    }

  if (user_data)
    {
    }

  /* get cairo drawing context */
  crdraw = gdk_cairo_create (event->window);

  /* how large drawing area is */
  (void) gdk_drawable_get_size (event->window, &w, &h);

  /* save a copy of current size */
  drawing_area_xsize = w;
  drawing_area_ysize = h;

  /* check if there is node data to draw */
  if ((drawdata == 0) || (dli_nlevels == 0) || (dlip == NULL))
    {
      /* white fill drawing area */
      cairo_set_source_rgb (crdraw, 1.0, 1.0, 1.0);
      cairo_rectangle (crdraw, 0, 0, w, h);
      cairo_fill (crdraw);
      cairo_stroke (crdraw);
      cairo_destroy (crdraw);
      /* no data */
      return (FALSE);
    }

  /* redraw drawing gui2.c */
  doredraw (crdraw);

  cairo_destroy (crdraw);

  return (FALSE);
}
#endif

#if GTK_HAVE_API_VERSION_3
/* redraw drawing area */
static gboolean
on_top_level_window_drawingarea1_draw_event (GtkWidget * widget, cairo_t * crdraw, gpointer user_data)
{
  gint w = 0;
  gint h = 0;
  cairo_t *crp = NULL;

  /* this is a workaround for issue in cairo-lib 1.14.0 with gtk3,
   * cairo.c cairo_destroy() line 305 assert(), (with gtk2 no problem) */
  crp = cairo_reference (crdraw);

  /* how large drawing area is */
  w = gtk_widget_get_allocated_width (drawingarea1);
  h = gtk_widget_get_allocated_height (drawingarea1);

  /* save a copy of current size */
  drawing_area_xsize = w;
  drawing_area_ysize = h;

  /* check if there is node data to draw */
  if ((drawdata == 0) || (dli_nlevels == 0) || (dlip == NULL))
    {
      /* white fill drawing area */
      cairo_set_source_rgb (crdraw, 1.0, 1.0, 1.0);
      cairo_rectangle (crdraw, 0, 0, w, h);
      cairo_fill (crdraw);
      cairo_stroke (crdraw);
      cairo_destroy (crp);
      /* no data */
      return (FALSE);
    }

  /* redraw drawing gui2.c */
  doredraw (crdraw);

  cairo_destroy (crp);

  return (FALSE);
}
#endif

/* end. */

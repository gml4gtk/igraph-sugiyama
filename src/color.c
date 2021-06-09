/* -*- mode: C -*-  */
/* vim:set ts=2 sts=2 sw=2 et: */
/* 
   IGraph library.
   Copyright (C) 2007-2012  Gabor Csardi <csardi.gabor@gmail.com>
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

/*
 *
 * Usable color info wikipedia: RGB_color_model, HSL_and_HSV, X11_color_names
 * color data based on data in x11 server src oscolor.c
 * april 2016
 * https://cgit.freedesktop.org/xorg/xserver/tree/os/oscolor.c
 * blob: 017aab1f2c1ced555230c9899867c0edc5876ba7
 */

#include "config.h"

#include <stdio.h>
#include <string.h>

#include "color.h"
#include "skiplist.h"

/* color names database */
static struct skls *gucolor = NULL;

/* add color data */
static void colordata (void);

/* add 1 color to database */
static void coloradd (const char *name, int code);

/* wipe color database */
void
colorcode_clear (void)
{
  /* color names database */
  if (1) {
    skls_pr (gucolor);
  }
  gucolor = skls_rm (gucolor);
  return;
}

/* create color database */
static void
color_init (void)
{

  /* indexed on (char *) */
  gucolor = skls_new (NULL, NULL);

  /* add color data indexed by name */
  colordata ();

  return;
}

/* add color data */
static void
colordata (void)
{

  /* 782 colors */
  coloradd ("alice blue", 0x00f0f8ff);	/* color 0 r/g/b decimal 240 248 255 */
  coloradd ("AliceBlue", 0x00f0f8ff);	/* color 1 r/g/b decimal 240 248 255 */
  coloradd ("antique white", 0x00faebd7);	/* color 2 r/g/b decimal 250 235 215 */
  coloradd ("AntiqueWhite", 0x00faebd7);	/* color 3 r/g/b decimal 250 235 215 */
  coloradd ("AntiqueWhite1", 0x00ffefdb);	/* color 4 r/g/b decimal 255 239 219 */
  coloradd ("AntiqueWhite2", 0x00eedfcc);	/* color 5 r/g/b decimal 238 223 204 */
  coloradd ("AntiqueWhite3", 0x00cdc0b0);	/* color 6 r/g/b decimal 205 192 176 */
  coloradd ("AntiqueWhite4", 0x008b8378);	/* color 7 r/g/b decimal 139 131 120 */
  coloradd ("aqua", 0x0000ffff);	/* color 8 r/g/b decimal 0 255 255 */
  coloradd ("aquamarine", 0x007fffd4);	/* color 9 r/g/b decimal 127 255 212 */
  coloradd ("aquamarine1", 0x007fffd4);	/* color 10 r/g/b decimal 127 255 212 */
  coloradd ("aquamarine2", 0x0076eec6);	/* color 11 r/g/b decimal 118 238 198 */
  coloradd ("aquamarine3", 0x0066cdaa);	/* color 12 r/g/b decimal 102 205 170 */
  coloradd ("aquamarine4", 0x00458b74);	/* color 13 r/g/b decimal 69 139 116 */
  coloradd ("azure", 0x00f0ffff);	/* color 14 r/g/b decimal 240 255 255 */
  coloradd ("azure1", 0x00f0ffff);	/* color 15 r/g/b decimal 240 255 255 */
  coloradd ("azure2", 0x00e0eeee);	/* color 16 r/g/b decimal 224 238 238 */
  coloradd ("azure3", 0x00c1cdcd);	/* color 17 r/g/b decimal 193 205 205 */
  coloradd ("azure4", 0x00838b8b);	/* color 18 r/g/b decimal 131 139 139 */
  coloradd ("beige", 0x00f5f5dc);	/* color 19 r/g/b decimal 245 245 220 */
  coloradd ("bisque", 0x00ffe4c4);	/* color 20 r/g/b decimal 255 228 196 */
  coloradd ("bisque1", 0x00ffe4c4);	/* color 21 r/g/b decimal 255 228 196 */
  coloradd ("bisque2", 0x00eed5b7);	/* color 22 r/g/b decimal 238 213 183 */
  coloradd ("bisque3", 0x00cdb79e);	/* color 23 r/g/b decimal 205 183 158 */
  coloradd ("bisque4", 0x008b7d6b);	/* color 24 r/g/b decimal 139 125 107 */
  coloradd ("black", 0x00000000);	/* color 25 r/g/b decimal 0 0 0 */
  coloradd ("blanched almond", 0x00ffebcd);	/* color 26 r/g/b decimal 255 235 205 */
  coloradd ("BlanchedAlmond", 0x00ffebcd);	/* color 27 r/g/b decimal 255 235 205 */
  coloradd ("blue", 0x000000ff);	/* color 28 r/g/b decimal 0 0 255 */
  coloradd ("blue violet", 0x008a2be2);	/* color 29 r/g/b decimal 138 43 226 */
  coloradd ("blue1", 0x000000ff);	/* color 30 r/g/b decimal 0 0 255 */
  coloradd ("blue2", 0x000000ee);	/* color 31 r/g/b decimal 0 0 238 */
  coloradd ("blue3", 0x000000cd);	/* color 32 r/g/b decimal 0 0 205 */
  coloradd ("blue4", 0x0000008b);	/* color 33 r/g/b decimal 0 0 139 */
  coloradd ("BlueViolet", 0x008a2be2);	/* color 34 r/g/b decimal 138 43 226 */
  coloradd ("brown", 0x00a52a2a);	/* color 35 r/g/b decimal 165 42 42 */
  coloradd ("brown1", 0x00ff4040);	/* color 36 r/g/b decimal 255 64 64 */
  coloradd ("brown2", 0x00ee3b3b);	/* color 37 r/g/b decimal 238 59 59 */
  coloradd ("brown3", 0x00cd3333);	/* color 38 r/g/b decimal 205 51 51 */
  coloradd ("brown4", 0x008b2323);	/* color 39 r/g/b decimal 139 35 35 */
  coloradd ("burlywood", 0x00deb887);	/* color 40 r/g/b decimal 222 184 135 */
  coloradd ("burlywood1", 0x00ffd39b);	/* color 41 r/g/b decimal 255 211 155 */
  coloradd ("burlywood2", 0x00eec591);	/* color 42 r/g/b decimal 238 197 145 */
  coloradd ("burlywood3", 0x00cdaa7d);	/* color 43 r/g/b decimal 205 170 125 */
  coloradd ("burlywood4", 0x008b7355);	/* color 44 r/g/b decimal 139 115 85 */
  coloradd ("cadet blue", 0x005f9ea0);	/* color 45 r/g/b decimal 95 158 160 */
  coloradd ("CadetBlue", 0x005f9ea0);	/* color 46 r/g/b decimal 95 158 160 */
  coloradd ("CadetBlue1", 0x0098f5ff);	/* color 47 r/g/b decimal 152 245 255 */
  coloradd ("CadetBlue2", 0x008ee5ee);	/* color 48 r/g/b decimal 142 229 238 */
  coloradd ("CadetBlue3", 0x007ac5cd);	/* color 49 r/g/b decimal 122 197 205 */
  coloradd ("CadetBlue4", 0x0053868b);	/* color 50 r/g/b decimal 83 134 139 */
  coloradd ("chartreuse", 0x007fff00);	/* color 51 r/g/b decimal 127 255 0 */
  coloradd ("chartreuse1", 0x007fff00);	/* color 52 r/g/b decimal 127 255 0 */
  coloradd ("chartreuse2", 0x0076ee00);	/* color 53 r/g/b decimal 118 238 0 */
  coloradd ("chartreuse3", 0x0066cd00);	/* color 54 r/g/b decimal 102 205 0 */
  coloradd ("chartreuse4", 0x00458b00);	/* color 55 r/g/b decimal 69 139 0 */
  coloradd ("chocolate", 0x00d2691e);	/* color 56 r/g/b decimal 210 105 30 */
  coloradd ("chocolate1", 0x00ff7f24);	/* color 57 r/g/b decimal 255 127 36 */
  coloradd ("chocolate2", 0x00ee7621);	/* color 58 r/g/b decimal 238 118 33 */
  coloradd ("chocolate3", 0x00cd661d);	/* color 59 r/g/b decimal 205 102 29 */
  coloradd ("chocolate4", 0x008b4513);	/* color 60 r/g/b decimal 139 69 19 */
  coloradd ("coral", 0x00ff7f50);	/* color 61 r/g/b decimal 255 127 80 */
  coloradd ("coral1", 0x00ff7256);	/* color 62 r/g/b decimal 255 114 86 */
  coloradd ("coral2", 0x00ee6a50);	/* color 63 r/g/b decimal 238 106 80 */
  coloradd ("coral3", 0x00cd5b45);	/* color 64 r/g/b decimal 205 91 69 */
  coloradd ("coral4", 0x008b3e2f);	/* color 65 r/g/b decimal 139 62 47 */
  coloradd ("cornflower blue", 0x006495ed);	/* color 66 r/g/b decimal 100 149 237 */
  coloradd ("CornflowerBlue", 0x006495ed);	/* color 67 r/g/b decimal 100 149 237 */
  coloradd ("cornsilk", 0x00fff8dc);	/* color 68 r/g/b decimal 255 248 220 */
  coloradd ("cornsilk1", 0x00fff8dc);	/* color 69 r/g/b decimal 255 248 220 */
  coloradd ("cornsilk2", 0x00eee8cd);	/* color 70 r/g/b decimal 238 232 205 */
  coloradd ("cornsilk3", 0x00cdc8b1);	/* color 71 r/g/b decimal 205 200 177 */
  coloradd ("cornsilk4", 0x008b8878);	/* color 72 r/g/b decimal 139 136 120 */
  coloradd ("crimson", 0x00dc143c);	/* color 73 r/g/b decimal 220 20 60 */
  coloradd ("cyan", 0x0000ffff);	/* color 74 r/g/b decimal 0 255 255 */
  coloradd ("cyan1", 0x0000ffff);	/* color 75 r/g/b decimal 0 255 255 */
  coloradd ("cyan2", 0x0000eeee);	/* color 76 r/g/b decimal 0 238 238 */
  coloradd ("cyan3", 0x0000cdcd);	/* color 77 r/g/b decimal 0 205 205 */
  coloradd ("cyan4", 0x00008b8b);	/* color 78 r/g/b decimal 0 139 139 */
  coloradd ("dark blue", 0x0000008b);	/* color 79 r/g/b decimal 0 0 139 */
  coloradd ("dark cyan", 0x00008b8b);	/* color 80 r/g/b decimal 0 139 139 */
  coloradd ("dark goldenrod", 0x00b8860b);	/* color 81 r/g/b decimal 184 134 11 */
  coloradd ("dark gray", 0x00a9a9a9);	/* color 82 r/g/b decimal 169 169 169 */
  coloradd ("dark green", 0x00006400);	/* color 83 r/g/b decimal 0 100 0 */
  coloradd ("dark grey", 0x00a9a9a9);	/* color 84 r/g/b decimal 169 169 169 */
  coloradd ("dark khaki", 0x00bdb76b);	/* color 85 r/g/b decimal 189 183 107 */
  coloradd ("dark magenta", 0x008b008b);	/* color 86 r/g/b decimal 139 0 139 */
  coloradd ("dark olive green", 0x00556b2f);	/* color 87 r/g/b decimal 85 107 47 */
  coloradd ("dark orange", 0x00ff8c00);	/* color 88 r/g/b decimal 255 140 0 */
  coloradd ("dark orchid", 0x009932cc);	/* color 89 r/g/b decimal 153 50 204 */
  coloradd ("dark red", 0x008b0000);	/* color 90 r/g/b decimal 139 0 0 */
  coloradd ("dark salmon", 0x00e9967a);	/* color 91 r/g/b decimal 233 150 122 */
  coloradd ("dark sea green", 0x008fbc8f);	/* color 92 r/g/b decimal 143 188 143 */
  coloradd ("dark slate blue", 0x00483d8b);	/* color 93 r/g/b decimal 72 61 139 */
  coloradd ("dark slate gray", 0x002f4f4f);	/* color 94 r/g/b decimal 47 79 79 */
  coloradd ("dark slate grey", 0x002f4f4f);	/* color 95 r/g/b decimal 47 79 79 */
  coloradd ("dark turquoise", 0x0000ced1);	/* color 96 r/g/b decimal 0 206 209 */
  coloradd ("dark violet", 0x009400d3);	/* color 97 r/g/b decimal 148 0 211 */
  coloradd ("DarkBlue", 0x0000008b);	/* color 98 r/g/b decimal 0 0 139 */
  coloradd ("DarkCyan", 0x00008b8b);	/* color 99 r/g/b decimal 0 139 139 */
  coloradd ("DarkGoldenrod", 0x00b8860b);	/* color 100 r/g/b decimal 184 134 11 */
  coloradd ("DarkGoldenrod1", 0x00ffb90f);	/* color 101 r/g/b decimal 255 185 15 */
  coloradd ("DarkGoldenrod2", 0x00eead0e);	/* color 102 r/g/b decimal 238 173 14 */
  coloradd ("DarkGoldenrod3", 0x00cd950c);	/* color 103 r/g/b decimal 205 149 12 */
  coloradd ("DarkGoldenrod4", 0x008b6508);	/* color 104 r/g/b decimal 139 101 8 */
  coloradd ("DarkGray", 0x00a9a9a9);	/* color 105 r/g/b decimal 169 169 169 */
  coloradd ("DarkGreen", 0x00006400);	/* color 106 r/g/b decimal 0 100 0 */
  coloradd ("DarkGrey", 0x00a9a9a9);	/* color 107 r/g/b decimal 169 169 169 */
  coloradd ("DarkKhaki", 0x00bdb76b);	/* color 108 r/g/b decimal 189 183 107 */
  coloradd ("DarkMagenta", 0x008b008b);	/* color 109 r/g/b decimal 139 0 139 */
  coloradd ("DarkOliveGreen", 0x00556b2f);	/* color 110 r/g/b decimal 85 107 47 */
  coloradd ("DarkOliveGreen1", 0x00caff70);	/* color 111 r/g/b decimal 202 255 112 */
  coloradd ("DarkOliveGreen2", 0x00bcee68);	/* color 112 r/g/b decimal 188 238 104 */
  coloradd ("DarkOliveGreen3", 0x00a2cd5a);	/* color 113 r/g/b decimal 162 205 90 */
  coloradd ("DarkOliveGreen4", 0x006e8b3d);	/* color 114 r/g/b decimal 110 139 61 */
  coloradd ("DarkOrange", 0x00ff8c00);	/* color 115 r/g/b decimal 255 140 0 */
  coloradd ("DarkOrange1", 0x00ff7f00);	/* color 116 r/g/b decimal 255 127 0 */
  coloradd ("DarkOrange2", 0x00ee7600);	/* color 117 r/g/b decimal 238 118 0 */
  coloradd ("DarkOrange3", 0x00cd6600);	/* color 118 r/g/b decimal 205 102 0 */
  coloradd ("DarkOrange4", 0x008b4500);	/* color 119 r/g/b decimal 139 69 0 */
  coloradd ("DarkOrchid", 0x009932cc);	/* color 120 r/g/b decimal 153 50 204 */
  coloradd ("DarkOrchid1", 0x00bf3eff);	/* color 121 r/g/b decimal 191 62 255 */
  coloradd ("DarkOrchid2", 0x00b23aee);	/* color 122 r/g/b decimal 178 58 238 */
  coloradd ("DarkOrchid3", 0x009a32cd);	/* color 123 r/g/b decimal 154 50 205 */
  coloradd ("DarkOrchid4", 0x0068228b);	/* color 124 r/g/b decimal 104 34 139 */
  coloradd ("DarkRed", 0x008b0000);	/* color 125 r/g/b decimal 139 0 0 */
  coloradd ("DarkSalmon", 0x00e9967a);	/* color 126 r/g/b decimal 233 150 122 */
  coloradd ("DarkSeaGreen", 0x008fbc8f);	/* color 127 r/g/b decimal 143 188 143 */
  coloradd ("DarkSeaGreen1", 0x00c1ffc1);	/* color 128 r/g/b decimal 193 255 193 */
  coloradd ("DarkSeaGreen2", 0x00b4eeb4);	/* color 129 r/g/b decimal 180 238 180 */
  coloradd ("DarkSeaGreen3", 0x009bcd9b);	/* color 130 r/g/b decimal 155 205 155 */
  coloradd ("DarkSeaGreen4", 0x00698b69);	/* color 131 r/g/b decimal 105 139 105 */
  coloradd ("DarkSlateBlue", 0x00483d8b);	/* color 132 r/g/b decimal 72 61 139 */
  coloradd ("DarkSlateGray", 0x002f4f4f);	/* color 133 r/g/b decimal 47 79 79 */
  coloradd ("DarkSlateGray1", 0x0097ffff);	/* color 134 r/g/b decimal 151 255 255 */
  coloradd ("DarkSlateGray2", 0x008deeee);	/* color 135 r/g/b decimal 141 238 238 */
  coloradd ("DarkSlateGray3", 0x0079cdcd);	/* color 136 r/g/b decimal 121 205 205 */
  coloradd ("DarkSlateGray4", 0x00528b8b);	/* color 137 r/g/b decimal 82 139 139 */
  coloradd ("DarkSlateGrey", 0x002f4f4f);	/* color 138 r/g/b decimal 47 79 79 */
  coloradd ("DarkTurquoise", 0x0000ced1);	/* color 139 r/g/b decimal 0 206 209 */
  coloradd ("DarkViolet", 0x009400d3);	/* color 140 r/g/b decimal 148 0 211 */
  coloradd ("deep pink", 0x00ff1493);	/* color 141 r/g/b decimal 255 20 147 */
  coloradd ("deep sky blue", 0x0000bfff);	/* color 142 r/g/b decimal 0 191 255 */
  coloradd ("DeepPink", 0x00ff1493);	/* color 143 r/g/b decimal 255 20 147 */
  coloradd ("DeepPink1", 0x00ff1493);	/* color 144 r/g/b decimal 255 20 147 */
  coloradd ("DeepPink2", 0x00ee1289);	/* color 145 r/g/b decimal 238 18 137 */
  coloradd ("DeepPink3", 0x00cd1076);	/* color 146 r/g/b decimal 205 16 118 */
  coloradd ("DeepPink4", 0x008b0a50);	/* color 147 r/g/b decimal 139 10 80 */
  coloradd ("DeepSkyBlue", 0x0000bfff);	/* color 148 r/g/b decimal 0 191 255 */
  coloradd ("DeepSkyBlue1", 0x0000bfff);	/* color 149 r/g/b decimal 0 191 255 */
  coloradd ("DeepSkyBlue2", 0x0000b2ee);	/* color 150 r/g/b decimal 0 178 238 */
  coloradd ("DeepSkyBlue3", 0x00009acd);	/* color 151 r/g/b decimal 0 154 205 */
  coloradd ("DeepSkyBlue4", 0x0000688b);	/* color 152 r/g/b decimal 0 104 139 */
  coloradd ("dim gray", 0x00696969);	/* color 153 r/g/b decimal 105 105 105 */
  coloradd ("dim grey", 0x00696969);	/* color 154 r/g/b decimal 105 105 105 */
  coloradd ("DimGray", 0x00696969);	/* color 155 r/g/b decimal 105 105 105 */
  coloradd ("DimGrey", 0x00696969);	/* color 156 r/g/b decimal 105 105 105 */
  coloradd ("dodger blue", 0x001e90ff);	/* color 157 r/g/b decimal 30 144 255 */
  coloradd ("DodgerBlue", 0x001e90ff);	/* color 158 r/g/b decimal 30 144 255 */
  coloradd ("DodgerBlue1", 0x001e90ff);	/* color 159 r/g/b decimal 30 144 255 */
  coloradd ("DodgerBlue2", 0x001c86ee);	/* color 160 r/g/b decimal 28 134 238 */
  coloradd ("DodgerBlue3", 0x001874cd);	/* color 161 r/g/b decimal 24 116 205 */
  coloradd ("DodgerBlue4", 0x00104e8b);	/* color 162 r/g/b decimal 16 78 139 */
  coloradd ("firebrick", 0x00b22222);	/* color 163 r/g/b decimal 178 34 34 */
  coloradd ("firebrick1", 0x00ff3030);	/* color 164 r/g/b decimal 255 48 48 */
  coloradd ("firebrick2", 0x00ee2c2c);	/* color 165 r/g/b decimal 238 44 44 */
  coloradd ("firebrick3", 0x00cd2626);	/* color 166 r/g/b decimal 205 38 38 */
  coloradd ("firebrick4", 0x008b1a1a);	/* color 167 r/g/b decimal 139 26 26 */
  coloradd ("floral white", 0x00fffaf0);	/* color 168 r/g/b decimal 255 250 240 */
  coloradd ("FloralWhite", 0x00fffaf0);	/* color 169 r/g/b decimal 255 250 240 */
  coloradd ("forest green", 0x00228b22);	/* color 170 r/g/b decimal 34 139 34 */
  coloradd ("ForestGreen", 0x00228b22);	/* color 171 r/g/b decimal 34 139 34 */
  coloradd ("fuchsia", 0x00ff00ff);	/* color 172 r/g/b decimal 255 0 255 */
  coloradd ("gainsboro", 0x00dcdcdc);	/* color 173 r/g/b decimal 220 220 220 */
  coloradd ("ghost white", 0x00f8f8ff);	/* color 174 r/g/b decimal 248 248 255 */
  coloradd ("GhostWhite", 0x00f8f8ff);	/* color 175 r/g/b decimal 248 248 255 */
  coloradd ("gold", 0x00ffd700);	/* color 176 r/g/b decimal 255 215 0 */
  coloradd ("gold1", 0x00ffd700);	/* color 177 r/g/b decimal 255 215 0 */
  coloradd ("gold2", 0x00eec900);	/* color 178 r/g/b decimal 238 201 0 */
  coloradd ("gold3", 0x00cdad00);	/* color 179 r/g/b decimal 205 173 0 */
  coloradd ("gold4", 0x008b7500);	/* color 180 r/g/b decimal 139 117 0 */
  coloradd ("goldenrod", 0x00daa520);	/* color 181 r/g/b decimal 218 165 32 */
  coloradd ("goldenrod1", 0x00ffc125);	/* color 182 r/g/b decimal 255 193 37 */
  coloradd ("goldenrod2", 0x00eeb422);	/* color 183 r/g/b decimal 238 180 34 */
  coloradd ("goldenrod3", 0x00cd9b1d);	/* color 184 r/g/b decimal 205 155 29 */
  coloradd ("goldenrod4", 0x008b6914);	/* color 185 r/g/b decimal 139 105 20 */
  coloradd ("gray", 0x00bebebe);	/* color 186 r/g/b decimal 190 190 190 */
  coloradd ("gray0", 0x00000000);	/* color 187 r/g/b decimal 0 0 0 */
  coloradd ("gray1", 0x00030303);	/* color 188 r/g/b decimal 3 3 3 */
  coloradd ("gray10", 0x001a1a1a);	/* color 189 r/g/b decimal 26 26 26 */
  coloradd ("gray100", 0x00ffffff);	/* color 190 r/g/b decimal 255 255 255 */
  coloradd ("gray11", 0x001c1c1c);	/* color 191 r/g/b decimal 28 28 28 */
  coloradd ("gray12", 0x001f1f1f);	/* color 192 r/g/b decimal 31 31 31 */
  coloradd ("gray13", 0x00212121);	/* color 193 r/g/b decimal 33 33 33 */
  coloradd ("gray14", 0x00242424);	/* color 194 r/g/b decimal 36 36 36 */
  coloradd ("gray15", 0x00262626);	/* color 195 r/g/b decimal 38 38 38 */
  coloradd ("gray16", 0x00292929);	/* color 196 r/g/b decimal 41 41 41 */
  coloradd ("gray17", 0x002b2b2b);	/* color 197 r/g/b decimal 43 43 43 */
  coloradd ("gray18", 0x002e2e2e);	/* color 198 r/g/b decimal 46 46 46 */
  coloradd ("gray19", 0x00303030);	/* color 199 r/g/b decimal 48 48 48 */
  coloradd ("gray2", 0x00050505);	/* color 200 r/g/b decimal 5 5 5 */
  coloradd ("gray20", 0x00333333);	/* color 201 r/g/b decimal 51 51 51 */
  coloradd ("gray21", 0x00363636);	/* color 202 r/g/b decimal 54 54 54 */
  coloradd ("gray22", 0x00383838);	/* color 203 r/g/b decimal 56 56 56 */
  coloradd ("gray23", 0x003b3b3b);	/* color 204 r/g/b decimal 59 59 59 */
  coloradd ("gray24", 0x003d3d3d);	/* color 205 r/g/b decimal 61 61 61 */
  coloradd ("gray25", 0x00404040);	/* color 206 r/g/b decimal 64 64 64 */
  coloradd ("gray26", 0x00424242);	/* color 207 r/g/b decimal 66 66 66 */
  coloradd ("gray27", 0x00454545);	/* color 208 r/g/b decimal 69 69 69 */
  coloradd ("gray28", 0x00474747);	/* color 209 r/g/b decimal 71 71 71 */
  coloradd ("gray29", 0x004a4a4a);	/* color 210 r/g/b decimal 74 74 74 */
  coloradd ("gray3", 0x00080808);	/* color 211 r/g/b decimal 8 8 8 */
  coloradd ("gray30", 0x004d4d4d);	/* color 212 r/g/b decimal 77 77 77 */
  coloradd ("gray31", 0x004f4f4f);	/* color 213 r/g/b decimal 79 79 79 */
  coloradd ("gray32", 0x00525252);	/* color 214 r/g/b decimal 82 82 82 */
  coloradd ("gray33", 0x00545454);	/* color 215 r/g/b decimal 84 84 84 */
  coloradd ("gray34", 0x00575757);	/* color 216 r/g/b decimal 87 87 87 */
  coloradd ("gray35", 0x00595959);	/* color 217 r/g/b decimal 89 89 89 */
  coloradd ("gray36", 0x005c5c5c);	/* color 218 r/g/b decimal 92 92 92 */
  coloradd ("gray37", 0x005e5e5e);	/* color 219 r/g/b decimal 94 94 94 */
  coloradd ("gray38", 0x00616161);	/* color 220 r/g/b decimal 97 97 97 */
  coloradd ("gray39", 0x00636363);	/* color 221 r/g/b decimal 99 99 99 */
  coloradd ("gray4", 0x000a0a0a);	/* color 222 r/g/b decimal 10 10 10 */
  coloradd ("gray40", 0x00666666);	/* color 223 r/g/b decimal 102 102 102 */
  coloradd ("gray41", 0x00696969);	/* color 224 r/g/b decimal 105 105 105 */
  coloradd ("gray42", 0x006b6b6b);	/* color 225 r/g/b decimal 107 107 107 */
  coloradd ("gray43", 0x006e6e6e);	/* color 226 r/g/b decimal 110 110 110 */
  coloradd ("gray44", 0x00707070);	/* color 227 r/g/b decimal 112 112 112 */
  coloradd ("gray45", 0x00737373);	/* color 228 r/g/b decimal 115 115 115 */
  coloradd ("gray46", 0x00757575);	/* color 229 r/g/b decimal 117 117 117 */
  coloradd ("gray47", 0x00787878);	/* color 230 r/g/b decimal 120 120 120 */
  coloradd ("gray48", 0x007a7a7a);	/* color 231 r/g/b decimal 122 122 122 */
  coloradd ("gray49", 0x007d7d7d);	/* color 232 r/g/b decimal 125 125 125 */
  coloradd ("gray5", 0x000d0d0d);	/* color 233 r/g/b decimal 13 13 13 */
  coloradd ("gray50", 0x007f7f7f);	/* color 234 r/g/b decimal 127 127 127 */
  coloradd ("gray51", 0x00828282);	/* color 235 r/g/b decimal 130 130 130 */
  coloradd ("gray52", 0x00858585);	/* color 236 r/g/b decimal 133 133 133 */
  coloradd ("gray53", 0x00878787);	/* color 237 r/g/b decimal 135 135 135 */
  coloradd ("gray54", 0x008a8a8a);	/* color 238 r/g/b decimal 138 138 138 */
  coloradd ("gray55", 0x008c8c8c);	/* color 239 r/g/b decimal 140 140 140 */
  coloradd ("gray56", 0x008f8f8f);	/* color 240 r/g/b decimal 143 143 143 */
  coloradd ("gray57", 0x00919191);	/* color 241 r/g/b decimal 145 145 145 */
  coloradd ("gray58", 0x00949494);	/* color 242 r/g/b decimal 148 148 148 */
  coloradd ("gray59", 0x00969696);	/* color 243 r/g/b decimal 150 150 150 */
  coloradd ("gray6", 0x000f0f0f);	/* color 244 r/g/b decimal 15 15 15 */
  coloradd ("gray60", 0x00999999);	/* color 245 r/g/b decimal 153 153 153 */
  coloradd ("gray61", 0x009c9c9c);	/* color 246 r/g/b decimal 156 156 156 */
  coloradd ("gray62", 0x009e9e9e);	/* color 247 r/g/b decimal 158 158 158 */
  coloradd ("gray63", 0x00a1a1a1);	/* color 248 r/g/b decimal 161 161 161 */
  coloradd ("gray64", 0x00a3a3a3);	/* color 249 r/g/b decimal 163 163 163 */
  coloradd ("gray65", 0x00a6a6a6);	/* color 250 r/g/b decimal 166 166 166 */
  coloradd ("gray66", 0x00a8a8a8);	/* color 251 r/g/b decimal 168 168 168 */
  coloradd ("gray67", 0x00ababab);	/* color 252 r/g/b decimal 171 171 171 */
  coloradd ("gray68", 0x00adadad);	/* color 253 r/g/b decimal 173 173 173 */
  coloradd ("gray69", 0x00b0b0b0);	/* color 254 r/g/b decimal 176 176 176 */
  coloradd ("gray7", 0x00121212);	/* color 255 r/g/b decimal 18 18 18 */
  coloradd ("gray70", 0x00b3b3b3);	/* color 256 r/g/b decimal 179 179 179 */
  coloradd ("gray71", 0x00b5b5b5);	/* color 257 r/g/b decimal 181 181 181 */
  coloradd ("gray72", 0x00b8b8b8);	/* color 258 r/g/b decimal 184 184 184 */
  coloradd ("gray73", 0x00bababa);	/* color 259 r/g/b decimal 186 186 186 */
  coloradd ("gray74", 0x00bdbdbd);	/* color 260 r/g/b decimal 189 189 189 */
  coloradd ("gray75", 0x00bfbfbf);	/* color 261 r/g/b decimal 191 191 191 */
  coloradd ("gray76", 0x00c2c2c2);	/* color 262 r/g/b decimal 194 194 194 */
  coloradd ("gray77", 0x00c4c4c4);	/* color 263 r/g/b decimal 196 196 196 */
  coloradd ("gray78", 0x00c7c7c7);	/* color 264 r/g/b decimal 199 199 199 */
  coloradd ("gray79", 0x00c9c9c9);	/* color 265 r/g/b decimal 201 201 201 */
  coloradd ("gray8", 0x00141414);	/* color 266 r/g/b decimal 20 20 20 */
  coloradd ("gray80", 0x00cccccc);	/* color 267 r/g/b decimal 204 204 204 */
  coloradd ("gray81", 0x00cfcfcf);	/* color 268 r/g/b decimal 207 207 207 */
  coloradd ("gray82", 0x00d1d1d1);	/* color 269 r/g/b decimal 209 209 209 */
  coloradd ("gray83", 0x00d4d4d4);	/* color 270 r/g/b decimal 212 212 212 */
  coloradd ("gray84", 0x00d6d6d6);	/* color 271 r/g/b decimal 214 214 214 */
  coloradd ("gray85", 0x00d9d9d9);	/* color 272 r/g/b decimal 217 217 217 */
  coloradd ("gray86", 0x00dbdbdb);	/* color 273 r/g/b decimal 219 219 219 */
  coloradd ("gray87", 0x00dedede);	/* color 274 r/g/b decimal 222 222 222 */
  coloradd ("gray88", 0x00e0e0e0);	/* color 275 r/g/b decimal 224 224 224 */
  coloradd ("gray89", 0x00e3e3e3);	/* color 276 r/g/b decimal 227 227 227 */
  coloradd ("gray9", 0x00171717);	/* color 277 r/g/b decimal 23 23 23 */
  coloradd ("gray90", 0x00e5e5e5);	/* color 278 r/g/b decimal 229 229 229 */
  coloradd ("gray91", 0x00e8e8e8);	/* color 279 r/g/b decimal 232 232 232 */
  coloradd ("gray92", 0x00ebebeb);	/* color 280 r/g/b decimal 235 235 235 */
  coloradd ("gray93", 0x00ededed);	/* color 281 r/g/b decimal 237 237 237 */
  coloradd ("gray94", 0x00f0f0f0);	/* color 282 r/g/b decimal 240 240 240 */
  coloradd ("gray95", 0x00f2f2f2);	/* color 283 r/g/b decimal 242 242 242 */
  coloradd ("gray96", 0x00f5f5f5);	/* color 284 r/g/b decimal 245 245 245 */
  coloradd ("gray97", 0x00f7f7f7);	/* color 285 r/g/b decimal 247 247 247 */
  coloradd ("gray98", 0x00fafafa);	/* color 286 r/g/b decimal 250 250 250 */
  coloradd ("gray99", 0x00fcfcfc);	/* color 287 r/g/b decimal 252 252 252 */
  coloradd ("green", 0x0000ff00);	/* color 288 r/g/b decimal 0 255 0 */
  coloradd ("green yellow", 0x00adff2f);	/* color 289 r/g/b decimal 173 255 47 */
  coloradd ("green1", 0x0000ff00);	/* color 290 r/g/b decimal 0 255 0 */
  coloradd ("green2", 0x0000ee00);	/* color 291 r/g/b decimal 0 238 0 */
  coloradd ("green3", 0x0000cd00);	/* color 292 r/g/b decimal 0 205 0 */
  coloradd ("green4", 0x00008b00);	/* color 293 r/g/b decimal 0 139 0 */
  coloradd ("GreenYellow", 0x00adff2f);	/* color 294 r/g/b decimal 173 255 47 */
  coloradd ("grey", 0x00bebebe);	/* color 295 r/g/b decimal 190 190 190 */
  coloradd ("grey0", 0x00000000);	/* color 296 r/g/b decimal 0 0 0 */
  coloradd ("grey1", 0x00030303);	/* color 297 r/g/b decimal 3 3 3 */
  coloradd ("grey10", 0x001a1a1a);	/* color 298 r/g/b decimal 26 26 26 */
  coloradd ("grey100", 0x00ffffff);	/* color 299 r/g/b decimal 255 255 255 */
  coloradd ("grey11", 0x001c1c1c);	/* color 300 r/g/b decimal 28 28 28 */
  coloradd ("grey12", 0x001f1f1f);	/* color 301 r/g/b decimal 31 31 31 */
  coloradd ("grey13", 0x00212121);	/* color 302 r/g/b decimal 33 33 33 */
  coloradd ("grey14", 0x00242424);	/* color 303 r/g/b decimal 36 36 36 */
  coloradd ("grey15", 0x00262626);	/* color 304 r/g/b decimal 38 38 38 */
  coloradd ("grey16", 0x00292929);	/* color 305 r/g/b decimal 41 41 41 */
  coloradd ("grey17", 0x002b2b2b);	/* color 306 r/g/b decimal 43 43 43 */
  coloradd ("grey18", 0x002e2e2e);	/* color 307 r/g/b decimal 46 46 46 */
  coloradd ("grey19", 0x00303030);	/* color 308 r/g/b decimal 48 48 48 */
  coloradd ("grey2", 0x00050505);	/* color 309 r/g/b decimal 5 5 5 */
  coloradd ("grey20", 0x00333333);	/* color 310 r/g/b decimal 51 51 51 */
  coloradd ("grey21", 0x00363636);	/* color 311 r/g/b decimal 54 54 54 */
  coloradd ("grey22", 0x00383838);	/* color 312 r/g/b decimal 56 56 56 */
  coloradd ("grey23", 0x003b3b3b);	/* color 313 r/g/b decimal 59 59 59 */
  coloradd ("grey24", 0x003d3d3d);	/* color 314 r/g/b decimal 61 61 61 */
  coloradd ("grey25", 0x00404040);	/* color 315 r/g/b decimal 64 64 64 */
  coloradd ("grey26", 0x00424242);	/* color 316 r/g/b decimal 66 66 66 */
  coloradd ("grey27", 0x00454545);	/* color 317 r/g/b decimal 69 69 69 */
  coloradd ("grey28", 0x00474747);	/* color 318 r/g/b decimal 71 71 71 */
  coloradd ("grey29", 0x004a4a4a);	/* color 319 r/g/b decimal 74 74 74 */
  coloradd ("grey3", 0x00080808);	/* color 320 r/g/b decimal 8 8 8 */
  coloradd ("grey30", 0x004d4d4d);	/* color 321 r/g/b decimal 77 77 77 */
  coloradd ("grey31", 0x004f4f4f);	/* color 322 r/g/b decimal 79 79 79 */
  coloradd ("grey32", 0x00525252);	/* color 323 r/g/b decimal 82 82 82 */
  coloradd ("grey33", 0x00545454);	/* color 324 r/g/b decimal 84 84 84 */
  coloradd ("grey34", 0x00575757);	/* color 325 r/g/b decimal 87 87 87 */
  coloradd ("grey35", 0x00595959);	/* color 326 r/g/b decimal 89 89 89 */
  coloradd ("grey36", 0x005c5c5c);	/* color 327 r/g/b decimal 92 92 92 */
  coloradd ("grey37", 0x005e5e5e);	/* color 328 r/g/b decimal 94 94 94 */
  coloradd ("grey38", 0x00616161);	/* color 329 r/g/b decimal 97 97 97 */
  coloradd ("grey39", 0x00636363);	/* color 330 r/g/b decimal 99 99 99 */
  coloradd ("grey4", 0x000a0a0a);	/* color 331 r/g/b decimal 10 10 10 */
  coloradd ("grey40", 0x00666666);	/* color 332 r/g/b decimal 102 102 102 */
  coloradd ("grey41", 0x00696969);	/* color 333 r/g/b decimal 105 105 105 */
  coloradd ("grey42", 0x006b6b6b);	/* color 334 r/g/b decimal 107 107 107 */
  coloradd ("grey43", 0x006e6e6e);	/* color 335 r/g/b decimal 110 110 110 */
  coloradd ("grey44", 0x00707070);	/* color 336 r/g/b decimal 112 112 112 */
  coloradd ("grey45", 0x00737373);	/* color 337 r/g/b decimal 115 115 115 */
  coloradd ("grey46", 0x00757575);	/* color 338 r/g/b decimal 117 117 117 */
  coloradd ("grey47", 0x00787878);	/* color 339 r/g/b decimal 120 120 120 */
  coloradd ("grey48", 0x007a7a7a);	/* color 340 r/g/b decimal 122 122 122 */
  coloradd ("grey49", 0x007d7d7d);	/* color 341 r/g/b decimal 125 125 125 */
  coloradd ("grey5", 0x000d0d0d);	/* color 342 r/g/b decimal 13 13 13 */
  coloradd ("grey50", 0x007f7f7f);	/* color 343 r/g/b decimal 127 127 127 */
  coloradd ("grey51", 0x00828282);	/* color 344 r/g/b decimal 130 130 130 */
  coloradd ("grey52", 0x00858585);	/* color 345 r/g/b decimal 133 133 133 */
  coloradd ("grey53", 0x00878787);	/* color 346 r/g/b decimal 135 135 135 */
  coloradd ("grey54", 0x008a8a8a);	/* color 347 r/g/b decimal 138 138 138 */
  coloradd ("grey55", 0x008c8c8c);	/* color 348 r/g/b decimal 140 140 140 */
  coloradd ("grey56", 0x008f8f8f);	/* color 349 r/g/b decimal 143 143 143 */
  coloradd ("grey57", 0x00919191);	/* color 350 r/g/b decimal 145 145 145 */
  coloradd ("grey58", 0x00949494);	/* color 351 r/g/b decimal 148 148 148 */
  coloradd ("grey59", 0x00969696);	/* color 352 r/g/b decimal 150 150 150 */
  coloradd ("grey6", 0x000f0f0f);	/* color 353 r/g/b decimal 15 15 15 */
  coloradd ("grey60", 0x00999999);	/* color 354 r/g/b decimal 153 153 153 */
  coloradd ("grey61", 0x009c9c9c);	/* color 355 r/g/b decimal 156 156 156 */
  coloradd ("grey62", 0x009e9e9e);	/* color 356 r/g/b decimal 158 158 158 */
  coloradd ("grey63", 0x00a1a1a1);	/* color 357 r/g/b decimal 161 161 161 */
  coloradd ("grey64", 0x00a3a3a3);	/* color 358 r/g/b decimal 163 163 163 */
  coloradd ("grey65", 0x00a6a6a6);	/* color 359 r/g/b decimal 166 166 166 */
  coloradd ("grey66", 0x00a8a8a8);	/* color 360 r/g/b decimal 168 168 168 */
  coloradd ("grey67", 0x00ababab);	/* color 361 r/g/b decimal 171 171 171 */
  coloradd ("grey68", 0x00adadad);	/* color 362 r/g/b decimal 173 173 173 */
  coloradd ("grey69", 0x00b0b0b0);	/* color 363 r/g/b decimal 176 176 176 */
  coloradd ("grey7", 0x00121212);	/* color 364 r/g/b decimal 18 18 18 */
  coloradd ("grey70", 0x00b3b3b3);	/* color 365 r/g/b decimal 179 179 179 */
  coloradd ("grey71", 0x00b5b5b5);	/* color 366 r/g/b decimal 181 181 181 */
  coloradd ("grey72", 0x00b8b8b8);	/* color 367 r/g/b decimal 184 184 184 */
  coloradd ("grey73", 0x00bababa);	/* color 368 r/g/b decimal 186 186 186 */
  coloradd ("grey74", 0x00bdbdbd);	/* color 369 r/g/b decimal 189 189 189 */
  coloradd ("grey75", 0x00bfbfbf);	/* color 370 r/g/b decimal 191 191 191 */
  coloradd ("grey76", 0x00c2c2c2);	/* color 371 r/g/b decimal 194 194 194 */
  coloradd ("grey77", 0x00c4c4c4);	/* color 372 r/g/b decimal 196 196 196 */
  coloradd ("grey78", 0x00c7c7c7);	/* color 373 r/g/b decimal 199 199 199 */
  coloradd ("grey79", 0x00c9c9c9);	/* color 374 r/g/b decimal 201 201 201 */
  coloradd ("grey8", 0x00141414);	/* color 375 r/g/b decimal 20 20 20 */
  coloradd ("grey80", 0x00cccccc);	/* color 376 r/g/b decimal 204 204 204 */
  coloradd ("grey81", 0x00cfcfcf);	/* color 377 r/g/b decimal 207 207 207 */
  coloradd ("grey82", 0x00d1d1d1);	/* color 378 r/g/b decimal 209 209 209 */
  coloradd ("grey83", 0x00d4d4d4);	/* color 379 r/g/b decimal 212 212 212 */
  coloradd ("grey84", 0x00d6d6d6);	/* color 380 r/g/b decimal 214 214 214 */
  coloradd ("grey85", 0x00d9d9d9);	/* color 381 r/g/b decimal 217 217 217 */
  coloradd ("grey86", 0x00dbdbdb);	/* color 382 r/g/b decimal 219 219 219 */
  coloradd ("grey87", 0x00dedede);	/* color 383 r/g/b decimal 222 222 222 */
  coloradd ("grey88", 0x00e0e0e0);	/* color 384 r/g/b decimal 224 224 224 */
  coloradd ("grey89", 0x00e3e3e3);	/* color 385 r/g/b decimal 227 227 227 */
  coloradd ("grey9", 0x00171717);	/* color 386 r/g/b decimal 23 23 23 */
  coloradd ("grey90", 0x00e5e5e5);	/* color 387 r/g/b decimal 229 229 229 */
  coloradd ("grey91", 0x00e8e8e8);	/* color 388 r/g/b decimal 232 232 232 */
  coloradd ("grey92", 0x00ebebeb);	/* color 389 r/g/b decimal 235 235 235 */
  coloradd ("grey93", 0x00ededed);	/* color 390 r/g/b decimal 237 237 237 */
  coloradd ("grey94", 0x00f0f0f0);	/* color 391 r/g/b decimal 240 240 240 */
  coloradd ("grey95", 0x00f2f2f2);	/* color 392 r/g/b decimal 242 242 242 */
  coloradd ("grey96", 0x00f5f5f5);	/* color 393 r/g/b decimal 245 245 245 */
  coloradd ("grey97", 0x00f7f7f7);	/* color 394 r/g/b decimal 247 247 247 */
  coloradd ("grey98", 0x00fafafa);	/* color 395 r/g/b decimal 250 250 250 */
  coloradd ("grey99", 0x00fcfcfc);	/* color 396 r/g/b decimal 252 252 252 */
  coloradd ("honeydew", 0x00f0fff0);	/* color 397 r/g/b decimal 240 255 240 */
  coloradd ("honeydew1", 0x00f0fff0);	/* color 398 r/g/b decimal 240 255 240 */
  coloradd ("honeydew2", 0x00e0eee0);	/* color 399 r/g/b decimal 224 238 224 */
  coloradd ("honeydew3", 0x00c1cdc1);	/* color 400 r/g/b decimal 193 205 193 */
  coloradd ("honeydew4", 0x00838b83);	/* color 401 r/g/b decimal 131 139 131 */
  coloradd ("hot pink", 0x00ff69b4);	/* color 402 r/g/b decimal 255 105 180 */
  coloradd ("HotPink", 0x00ff69b4);	/* color 403 r/g/b decimal 255 105 180 */
  coloradd ("HotPink1", 0x00ff6eb4);	/* color 404 r/g/b decimal 255 110 180 */
  coloradd ("HotPink2", 0x00ee6aa7);	/* color 405 r/g/b decimal 238 106 167 */
  coloradd ("HotPink3", 0x00cd6090);	/* color 406 r/g/b decimal 205 96 144 */
  coloradd ("HotPink4", 0x008b3a62);	/* color 407 r/g/b decimal 139 58 98 */
  coloradd ("indian red", 0x00cd5c5c);	/* color 408 r/g/b decimal 205 92 92 */
  coloradd ("IndianRed", 0x00cd5c5c);	/* color 409 r/g/b decimal 205 92 92 */
  coloradd ("IndianRed1", 0x00ff6a6a);	/* color 410 r/g/b decimal 255 106 106 */
  coloradd ("IndianRed2", 0x00ee6363);	/* color 411 r/g/b decimal 238 99 99 */
  coloradd ("IndianRed3", 0x00cd5555);	/* color 412 r/g/b decimal 205 85 85 */
  coloradd ("IndianRed4", 0x008b3a3a);	/* color 413 r/g/b decimal 139 58 58 */
  coloradd ("indigo", 0x004b0082);	/* color 414 r/g/b decimal 75 0 130 */
  coloradd ("ivory", 0x00fffff0);	/* color 415 r/g/b decimal 255 255 240 */
  coloradd ("ivory1", 0x00fffff0);	/* color 416 r/g/b decimal 255 255 240 */
  coloradd ("ivory2", 0x00eeeee0);	/* color 417 r/g/b decimal 238 238 224 */
  coloradd ("ivory3", 0x00cdcdc1);	/* color 418 r/g/b decimal 205 205 193 */
  coloradd ("ivory4", 0x008b8b83);	/* color 419 r/g/b decimal 139 139 131 */
  coloradd ("khaki", 0x00f0e68c);	/* color 420 r/g/b decimal 240 230 140 */
  coloradd ("khaki1", 0x00fff68f);	/* color 421 r/g/b decimal 255 246 143 */
  coloradd ("khaki2", 0x00eee685);	/* color 422 r/g/b decimal 238 230 133 */
  coloradd ("khaki3", 0x00cdc673);	/* color 423 r/g/b decimal 205 198 115 */
  coloradd ("khaki4", 0x008b864e);	/* color 424 r/g/b decimal 139 134 78 */
  coloradd ("lavender", 0x00e6e6fa);	/* color 425 r/g/b decimal 230 230 250 */
  coloradd ("lavender blush", 0x00fff0f5);	/* color 426 r/g/b decimal 255 240 245 */
  coloradd ("LavenderBlush", 0x00fff0f5);	/* color 427 r/g/b decimal 255 240 245 */
  coloradd ("LavenderBlush1", 0x00fff0f5);	/* color 428 r/g/b decimal 255 240 245 */
  coloradd ("LavenderBlush2", 0x00eee0e5);	/* color 429 r/g/b decimal 238 224 229 */
  coloradd ("LavenderBlush3", 0x00cdc1c5);	/* color 430 r/g/b decimal 205 193 197 */
  coloradd ("LavenderBlush4", 0x008b8386);	/* color 431 r/g/b decimal 139 131 134 */
  coloradd ("lawn green", 0x007cfc00);	/* color 432 r/g/b decimal 124 252 0 */
  coloradd ("LawnGreen", 0x007cfc00);	/* color 433 r/g/b decimal 124 252 0 */
  coloradd ("lemon chiffon", 0x00fffacd);	/* color 434 r/g/b decimal 255 250 205 */
  coloradd ("LemonChiffon", 0x00fffacd);	/* color 435 r/g/b decimal 255 250 205 */
  coloradd ("LemonChiffon1", 0x00fffacd);	/* color 436 r/g/b decimal 255 250 205 */
  coloradd ("LemonChiffon2", 0x00eee9bf);	/* color 437 r/g/b decimal 238 233 191 */
  coloradd ("LemonChiffon3", 0x00cdc9a5);	/* color 438 r/g/b decimal 205 201 165 */
  coloradd ("LemonChiffon4", 0x008b8970);	/* color 439 r/g/b decimal 139 137 112 */
  coloradd ("light blue", 0x00add8e6);	/* color 440 r/g/b decimal 173 216 230 */
  coloradd ("light coral", 0x00f08080);	/* color 441 r/g/b decimal 240 128 128 */
  coloradd ("light cyan", 0x00e0ffff);	/* color 442 r/g/b decimal 224 255 255 */
  coloradd ("light goldenrod", 0x00eedd82);	/* color 443 r/g/b decimal 238 221 130 */
  coloradd ("light goldenrod yellow", 0x00fafad2);	/* color 444 r/g/b decimal 250 250 210 */
  coloradd ("light gray", 0x00d3d3d3);	/* color 445 r/g/b decimal 211 211 211 */
  coloradd ("light green", 0x0090ee90);	/* color 446 r/g/b decimal 144 238 144 */
  coloradd ("light grey", 0x00d3d3d3);	/* color 447 r/g/b decimal 211 211 211 */
  coloradd ("light pink", 0x00ffb6c1);	/* color 448 r/g/b decimal 255 182 193 */
  coloradd ("light salmon", 0x00ffa07a);	/* color 449 r/g/b decimal 255 160 122 */
  coloradd ("light sea green", 0x0020b2aa);	/* color 450 r/g/b decimal 32 178 170 */
  coloradd ("light sky blue", 0x0087cefa);	/* color 451 r/g/b decimal 135 206 250 */
  coloradd ("light slate blue", 0x008470ff);	/* color 452 r/g/b decimal 132 112 255 */
  coloradd ("light slate gray", 0x00778899);	/* color 453 r/g/b decimal 119 136 153 */
  coloradd ("light slate grey", 0x00778899);	/* color 454 r/g/b decimal 119 136 153 */
  coloradd ("light steel blue", 0x00b0c4de);	/* color 455 r/g/b decimal 176 196 222 */
  coloradd ("light yellow", 0x00ffffe0);	/* color 456 r/g/b decimal 255 255 224 */
  coloradd ("LightBlue", 0x00add8e6);	/* color 457 r/g/b decimal 173 216 230 */
  coloradd ("LightBlue1", 0x00bfefff);	/* color 458 r/g/b decimal 191 239 255 */
  coloradd ("LightBlue2", 0x00b2dfee);	/* color 459 r/g/b decimal 178 223 238 */
  coloradd ("LightBlue3", 0x009ac0cd);	/* color 460 r/g/b decimal 154 192 205 */
  coloradd ("LightBlue4", 0x0068838b);	/* color 461 r/g/b decimal 104 131 139 */
  coloradd ("LightCoral", 0x00f08080);	/* color 462 r/g/b decimal 240 128 128 */
  coloradd ("LightCyan", 0x00e0ffff);	/* color 463 r/g/b decimal 224 255 255 */
  coloradd ("LightCyan1", 0x00e0ffff);	/* color 464 r/g/b decimal 224 255 255 */
  coloradd ("LightCyan2", 0x00d1eeee);	/* color 465 r/g/b decimal 209 238 238 */
  coloradd ("LightCyan3", 0x00b4cdcd);	/* color 466 r/g/b decimal 180 205 205 */
  coloradd ("LightCyan4", 0x007a8b8b);	/* color 467 r/g/b decimal 122 139 139 */
  coloradd ("LightGoldenrod", 0x00eedd82);	/* color 468 r/g/b decimal 238 221 130 */
  coloradd ("LightGoldenrod1", 0x00ffec8b);	/* color 469 r/g/b decimal 255 236 139 */
  coloradd ("LightGoldenrod2", 0x00eedc82);	/* color 470 r/g/b decimal 238 220 130 */
  coloradd ("LightGoldenrod3", 0x00cdbe70);	/* color 471 r/g/b decimal 205 190 112 */
  coloradd ("LightGoldenrod4", 0x008b814c);	/* color 472 r/g/b decimal 139 129 76 */
  coloradd ("LightGoldenrodYellow", 0x00fafad2);	/* color 473 r/g/b decimal 250 250 210 */
  coloradd ("LightGray", 0x00d3d3d3);	/* color 474 r/g/b decimal 211 211 211 */
  coloradd ("LightGreen", 0x0090ee90);	/* color 475 r/g/b decimal 144 238 144 */
  coloradd ("LightGrey", 0x00d3d3d3);	/* color 476 r/g/b decimal 211 211 211 */
  coloradd ("LightPink", 0x00ffb6c1);	/* color 477 r/g/b decimal 255 182 193 */
  coloradd ("LightPink1", 0x00ffaeb9);	/* color 478 r/g/b decimal 255 174 185 */
  coloradd ("LightPink2", 0x00eea2ad);	/* color 479 r/g/b decimal 238 162 173 */
  coloradd ("LightPink3", 0x00cd8c95);	/* color 480 r/g/b decimal 205 140 149 */
  coloradd ("LightPink4", 0x008b5f65);	/* color 481 r/g/b decimal 139 95 101 */
  coloradd ("LightSalmon", 0x00ffa07a);	/* color 482 r/g/b decimal 255 160 122 */
  coloradd ("LightSalmon1", 0x00ffa07a);	/* color 483 r/g/b decimal 255 160 122 */
  coloradd ("LightSalmon2", 0x00ee9572);	/* color 484 r/g/b decimal 238 149 114 */
  coloradd ("LightSalmon3", 0x00cd8162);	/* color 485 r/g/b decimal 205 129 98 */
  coloradd ("LightSalmon4", 0x008b5742);	/* color 486 r/g/b decimal 139 87 66 */
  coloradd ("LightSeaGreen", 0x0020b2aa);	/* color 487 r/g/b decimal 32 178 170 */
  coloradd ("LightSkyBlue", 0x0087cefa);	/* color 488 r/g/b decimal 135 206 250 */
  coloradd ("LightSkyBlue1", 0x00b0e2ff);	/* color 489 r/g/b decimal 176 226 255 */
  coloradd ("LightSkyBlue2", 0x00a4d3ee);	/* color 490 r/g/b decimal 164 211 238 */
  coloradd ("LightSkyBlue3", 0x008db6cd);	/* color 491 r/g/b decimal 141 182 205 */
  coloradd ("LightSkyBlue4", 0x00607b8b);	/* color 492 r/g/b decimal 96 123 139 */
  coloradd ("LightSlateBlue", 0x008470ff);	/* color 493 r/g/b decimal 132 112 255 */
  coloradd ("LightSlateGray", 0x00778899);	/* color 494 r/g/b decimal 119 136 153 */
  coloradd ("LightSlateGrey", 0x00778899);	/* color 495 r/g/b decimal 119 136 153 */
  coloradd ("LightSteelBlue", 0x00b0c4de);	/* color 496 r/g/b decimal 176 196 222 */
  coloradd ("LightSteelBlue1", 0x00cae1ff);	/* color 497 r/g/b decimal 202 225 255 */
  coloradd ("LightSteelBlue2", 0x00bcd2ee);	/* color 498 r/g/b decimal 188 210 238 */
  coloradd ("LightSteelBlue3", 0x00a2b5cd);	/* color 499 r/g/b decimal 162 181 205 */
  coloradd ("LightSteelBlue4", 0x006e7b8b);	/* color 500 r/g/b decimal 110 123 139 */
  coloradd ("LightYellow", 0x00ffffe0);	/* color 501 r/g/b decimal 255 255 224 */
  coloradd ("LightYellow1", 0x00ffffe0);	/* color 502 r/g/b decimal 255 255 224 */
  coloradd ("LightYellow2", 0x00eeeed1);	/* color 503 r/g/b decimal 238 238 209 */
  coloradd ("LightYellow3", 0x00cdcdb4);	/* color 504 r/g/b decimal 205 205 180 */
  coloradd ("LightYellow4", 0x008b8b7a);	/* color 505 r/g/b decimal 139 139 122 */
  coloradd ("lime", 0x0000ff00);	/* color 506 r/g/b decimal 0 255 0 */
  coloradd ("lime green", 0x0032cd32);	/* color 507 r/g/b decimal 50 205 50 */
  coloradd ("LimeGreen", 0x0032cd32);	/* color 508 r/g/b decimal 50 205 50 */
  coloradd ("linen", 0x00faf0e6);	/* color 509 r/g/b decimal 250 240 230 */
  coloradd ("magenta", 0x00ff00ff);	/* color 510 r/g/b decimal 255 0 255 */
  coloradd ("magenta1", 0x00ff00ff);	/* color 511 r/g/b decimal 255 0 255 */
  coloradd ("magenta2", 0x00ee00ee);	/* color 512 r/g/b decimal 238 0 238 */
  coloradd ("magenta3", 0x00cd00cd);	/* color 513 r/g/b decimal 205 0 205 */
  coloradd ("magenta4", 0x008b008b);	/* color 514 r/g/b decimal 139 0 139 */
  coloradd ("maroon", 0x00b03060);	/* color 515 r/g/b decimal 176 48 96 */
  coloradd ("maroon1", 0x00ff34b3);	/* color 516 r/g/b decimal 255 52 179 */
  coloradd ("maroon2", 0x00ee30a7);	/* color 517 r/g/b decimal 238 48 167 */
  coloradd ("maroon3", 0x00cd2990);	/* color 518 r/g/b decimal 205 41 144 */
  coloradd ("maroon4", 0x008b1c62);	/* color 519 r/g/b decimal 139 28 98 */
  coloradd ("medium aquamarine", 0x0066cdaa);	/* color 520 r/g/b decimal 102 205 170 */
  coloradd ("medium blue", 0x000000cd);	/* color 521 r/g/b decimal 0 0 205 */
  coloradd ("medium orchid", 0x00ba55d3);	/* color 522 r/g/b decimal 186 85 211 */
  coloradd ("medium purple", 0x009370db);	/* color 523 r/g/b decimal 147 112 219 */
  coloradd ("medium sea green", 0x003cb371);	/* color 524 r/g/b decimal 60 179 113 */
  coloradd ("medium slate blue", 0x007b68ee);	/* color 525 r/g/b decimal 123 104 238 */
  coloradd ("medium spring green", 0x0000fa9a);	/* color 526 r/g/b decimal 0 250 154 */
  coloradd ("medium turquoise", 0x0048d1cc);	/* color 527 r/g/b decimal 72 209 204 */
  coloradd ("medium violet red", 0x00c71585);	/* color 528 r/g/b decimal 199 21 133 */
  coloradd ("MediumAquamarine", 0x0066cdaa);	/* color 529 r/g/b decimal 102 205 170 */
  coloradd ("MediumBlue", 0x000000cd);	/* color 530 r/g/b decimal 0 0 205 */
  coloradd ("MediumOrchid", 0x00ba55d3);	/* color 531 r/g/b decimal 186 85 211 */
  coloradd ("MediumOrchid1", 0x00e066ff);	/* color 532 r/g/b decimal 224 102 255 */
  coloradd ("MediumOrchid2", 0x00d15fee);	/* color 533 r/g/b decimal 209 95 238 */
  coloradd ("MediumOrchid3", 0x00b452cd);	/* color 534 r/g/b decimal 180 82 205 */
  coloradd ("MediumOrchid4", 0x007a378b);	/* color 535 r/g/b decimal 122 55 139 */
  coloradd ("MediumPurple", 0x009370db);	/* color 536 r/g/b decimal 147 112 219 */
  coloradd ("MediumPurple1", 0x00ab82ff);	/* color 537 r/g/b decimal 171 130 255 */
  coloradd ("MediumPurple2", 0x009f79ee);	/* color 538 r/g/b decimal 159 121 238 */
  coloradd ("MediumPurple3", 0x008968cd);	/* color 539 r/g/b decimal 137 104 205 */
  coloradd ("MediumPurple4", 0x005d478b);	/* color 540 r/g/b decimal 93 71 139 */
  coloradd ("MediumSeaGreen", 0x003cb371);	/* color 541 r/g/b decimal 60 179 113 */
  coloradd ("MediumSlateBlue", 0x007b68ee);	/* color 542 r/g/b decimal 123 104 238 */
  coloradd ("MediumSpringGreen", 0x0000fa9a);	/* color 543 r/g/b decimal 0 250 154 */
  coloradd ("MediumTurquoise", 0x0048d1cc);	/* color 544 r/g/b decimal 72 209 204 */
  coloradd ("MediumVioletRed", 0x00c71585);	/* color 545 r/g/b decimal 199 21 133 */
  coloradd ("midnight blue", 0x00191970);	/* color 546 r/g/b decimal 25 25 112 */
  coloradd ("MidnightBlue", 0x00191970);	/* color 547 r/g/b decimal 25 25 112 */
  coloradd ("mint cream", 0x00f5fffa);	/* color 548 r/g/b decimal 245 255 250 */
  coloradd ("MintCream", 0x00f5fffa);	/* color 549 r/g/b decimal 245 255 250 */
  coloradd ("misty rose", 0x00ffe4e1);	/* color 550 r/g/b decimal 255 228 225 */
  coloradd ("MistyRose", 0x00ffe4e1);	/* color 551 r/g/b decimal 255 228 225 */
  coloradd ("MistyRose1", 0x00ffe4e1);	/* color 552 r/g/b decimal 255 228 225 */
  coloradd ("MistyRose2", 0x00eed5d2);	/* color 553 r/g/b decimal 238 213 210 */
  coloradd ("MistyRose3", 0x00cdb7b5);	/* color 554 r/g/b decimal 205 183 181 */
  coloradd ("MistyRose4", 0x008b7d7b);	/* color 555 r/g/b decimal 139 125 123 */
  coloradd ("moccasin", 0x00ffe4b5);	/* color 556 r/g/b decimal 255 228 181 */
  coloradd ("navajo white", 0x00ffdead);	/* color 557 r/g/b decimal 255 222 173 */
  coloradd ("NavajoWhite", 0x00ffdead);	/* color 558 r/g/b decimal 255 222 173 */
  coloradd ("NavajoWhite1", 0x00ffdead);	/* color 559 r/g/b decimal 255 222 173 */
  coloradd ("NavajoWhite2", 0x00eecfa1);	/* color 560 r/g/b decimal 238 207 161 */
  coloradd ("NavajoWhite3", 0x00cdb38b);	/* color 561 r/g/b decimal 205 179 139 */
  coloradd ("NavajoWhite4", 0x008b795e);	/* color 562 r/g/b decimal 139 121 94 */
  coloradd ("navy", 0x00000080);	/* color 563 r/g/b decimal 0 0 128 */
  coloradd ("navy blue", 0x00000080);	/* color 564 r/g/b decimal 0 0 128 */
  coloradd ("NavyBlue", 0x00000080);	/* color 565 r/g/b decimal 0 0 128 */
  coloradd ("old lace", 0x00fdf5e6);	/* color 566 r/g/b decimal 253 245 230 */
  coloradd ("OldLace", 0x00fdf5e6);	/* color 567 r/g/b decimal 253 245 230 */
  coloradd ("olive", 0x00808000);	/* color 568 r/g/b decimal 128 128 0 */
  coloradd ("olive drab", 0x006b8e23);	/* color 569 r/g/b decimal 107 142 35 */
  coloradd ("OliveDrab", 0x006b8e23);	/* color 570 r/g/b decimal 107 142 35 */
  coloradd ("OliveDrab1", 0x00c0ff3e);	/* color 571 r/g/b decimal 192 255 62 */
  coloradd ("OliveDrab2", 0x00b3ee3a);	/* color 572 r/g/b decimal 179 238 58 */
  coloradd ("OliveDrab3", 0x009acd32);	/* color 573 r/g/b decimal 154 205 50 */
  coloradd ("OliveDrab4", 0x00698b22);	/* color 574 r/g/b decimal 105 139 34 */
  coloradd ("orange", 0x00ffa500);	/* color 575 r/g/b decimal 255 165 0 */
  coloradd ("orange red", 0x00ff4500);	/* color 576 r/g/b decimal 255 69 0 */
  coloradd ("orange1", 0x00ffa500);	/* color 577 r/g/b decimal 255 165 0 */
  coloradd ("orange2", 0x00ee9a00);	/* color 578 r/g/b decimal 238 154 0 */
  coloradd ("orange3", 0x00cd8500);	/* color 579 r/g/b decimal 205 133 0 */
  coloradd ("orange4", 0x008b5a00);	/* color 580 r/g/b decimal 139 90 0 */
  coloradd ("OrangeRed", 0x00ff4500);	/* color 581 r/g/b decimal 255 69 0 */
  coloradd ("OrangeRed1", 0x00ff4500);	/* color 582 r/g/b decimal 255 69 0 */
  coloradd ("OrangeRed2", 0x00ee4000);	/* color 583 r/g/b decimal 238 64 0 */
  coloradd ("OrangeRed3", 0x00cd3700);	/* color 584 r/g/b decimal 205 55 0 */
  coloradd ("OrangeRed4", 0x008b2500);	/* color 585 r/g/b decimal 139 37 0 */
  coloradd ("orchid", 0x00da70d6);	/* color 586 r/g/b decimal 218 112 214 */
  coloradd ("orchid1", 0x00ff83fa);	/* color 587 r/g/b decimal 255 131 250 */
  coloradd ("orchid2", 0x00ee7ae9);	/* color 588 r/g/b decimal 238 122 233 */
  coloradd ("orchid3", 0x00cd69c9);	/* color 589 r/g/b decimal 205 105 201 */
  coloradd ("orchid4", 0x008b4789);	/* color 590 r/g/b decimal 139 71 137 */
  coloradd ("pale goldenrod", 0x00eee8aa);	/* color 591 r/g/b decimal 238 232 170 */
  coloradd ("pale green", 0x0098fb98);	/* color 592 r/g/b decimal 152 251 152 */
  coloradd ("pale turquoise", 0x00afeeee);	/* color 593 r/g/b decimal 175 238 238 */
  coloradd ("pale violet red", 0x00db7093);	/* color 594 r/g/b decimal 219 112 147 */
  coloradd ("PaleGoldenrod", 0x00eee8aa);	/* color 595 r/g/b decimal 238 232 170 */
  coloradd ("PaleGreen", 0x0098fb98);	/* color 596 r/g/b decimal 152 251 152 */
  coloradd ("PaleGreen1", 0x009aff9a);	/* color 597 r/g/b decimal 154 255 154 */
  coloradd ("PaleGreen2", 0x0090ee90);	/* color 598 r/g/b decimal 144 238 144 */
  coloradd ("PaleGreen3", 0x007ccd7c);	/* color 599 r/g/b decimal 124 205 124 */
  coloradd ("PaleGreen4", 0x00548b54);	/* color 600 r/g/b decimal 84 139 84 */
  coloradd ("PaleTurquoise", 0x00afeeee);	/* color 601 r/g/b decimal 175 238 238 */
  coloradd ("PaleTurquoise1", 0x00bbffff);	/* color 602 r/g/b decimal 187 255 255 */
  coloradd ("PaleTurquoise2", 0x00aeeeee);	/* color 603 r/g/b decimal 174 238 238 */
  coloradd ("PaleTurquoise3", 0x0096cdcd);	/* color 604 r/g/b decimal 150 205 205 */
  coloradd ("PaleTurquoise4", 0x00668b8b);	/* color 605 r/g/b decimal 102 139 139 */
  coloradd ("PaleVioletRed", 0x00db7093);	/* color 606 r/g/b decimal 219 112 147 */
  coloradd ("PaleVioletRed1", 0x00ff82ab);	/* color 607 r/g/b decimal 255 130 171 */
  coloradd ("PaleVioletRed2", 0x00ee799f);	/* color 608 r/g/b decimal 238 121 159 */
  coloradd ("PaleVioletRed3", 0x00cd6889);	/* color 609 r/g/b decimal 205 104 137 */
  coloradd ("PaleVioletRed4", 0x008b475d);	/* color 610 r/g/b decimal 139 71 93 */
  coloradd ("papaya whip", 0x00ffefd5);	/* color 611 r/g/b decimal 255 239 213 */
  coloradd ("PapayaWhip", 0x00ffefd5);	/* color 612 r/g/b decimal 255 239 213 */
  coloradd ("peach puff", 0x00ffdab9);	/* color 613 r/g/b decimal 255 218 185 */
  coloradd ("PeachPuff", 0x00ffdab9);	/* color 614 r/g/b decimal 255 218 185 */
  coloradd ("PeachPuff1", 0x00ffdab9);	/* color 615 r/g/b decimal 255 218 185 */
  coloradd ("PeachPuff2", 0x00eecbad);	/* color 616 r/g/b decimal 238 203 173 */
  coloradd ("PeachPuff3", 0x00cdaf95);	/* color 617 r/g/b decimal 205 175 149 */
  coloradd ("PeachPuff4", 0x008b7765);	/* color 618 r/g/b decimal 139 119 101 */
  coloradd ("peru", 0x00cd853f);	/* color 619 r/g/b decimal 205 133 63 */
  coloradd ("pink", 0x00ffc0cb);	/* color 620 r/g/b decimal 255 192 203 */
  coloradd ("pink1", 0x00ffb5c5);	/* color 621 r/g/b decimal 255 181 197 */
  coloradd ("pink2", 0x00eea9b8);	/* color 622 r/g/b decimal 238 169 184 */
  coloradd ("pink3", 0x00cd919e);	/* color 623 r/g/b decimal 205 145 158 */
  coloradd ("pink4", 0x008b636c);	/* color 624 r/g/b decimal 139 99 108 */
  coloradd ("plum", 0x00dda0dd);	/* color 625 r/g/b decimal 221 160 221 */
  coloradd ("plum1", 0x00ffbbff);	/* color 626 r/g/b decimal 255 187 255 */
  coloradd ("plum2", 0x00eeaeee);	/* color 627 r/g/b decimal 238 174 238 */
  coloradd ("plum3", 0x00cd96cd);	/* color 628 r/g/b decimal 205 150 205 */
  coloradd ("plum4", 0x008b668b);	/* color 629 r/g/b decimal 139 102 139 */
  coloradd ("powder blue", 0x00b0e0e6);	/* color 630 r/g/b decimal 176 224 230 */
  coloradd ("PowderBlue", 0x00b0e0e6);	/* color 631 r/g/b decimal 176 224 230 */
  coloradd ("purple", 0x00a020f0);	/* color 632 r/g/b decimal 160 32 240 */
  coloradd ("purple1", 0x009b30ff);	/* color 633 r/g/b decimal 155 48 255 */
  coloradd ("purple2", 0x00912cee);	/* color 634 r/g/b decimal 145 44 238 */
  coloradd ("purple3", 0x007d26cd);	/* color 635 r/g/b decimal 125 38 205 */
  coloradd ("purple4", 0x00551a8b);	/* color 636 r/g/b decimal 85 26 139 */
  coloradd ("rebecca purple", 0x00663399);	/* color 637 r/g/b decimal 102 51 153 */
  coloradd ("RebeccaPurple", 0x00663399);	/* color 638 r/g/b decimal 102 51 153 */
  coloradd ("red", 0x00ff0000);	/* color 639 r/g/b decimal 255 0 0 */
  coloradd ("red1", 0x00ff0000);	/* color 640 r/g/b decimal 255 0 0 */
  coloradd ("red2", 0x00ee0000);	/* color 641 r/g/b decimal 238 0 0 */
  coloradd ("red3", 0x00cd0000);	/* color 642 r/g/b decimal 205 0 0 */
  coloradd ("red4", 0x008b0000);	/* color 643 r/g/b decimal 139 0 0 */
  coloradd ("rosy brown", 0x00bc8f8f);	/* color 644 r/g/b decimal 188 143 143 */
  coloradd ("RosyBrown", 0x00bc8f8f);	/* color 645 r/g/b decimal 188 143 143 */
  coloradd ("RosyBrown1", 0x00ffc1c1);	/* color 646 r/g/b decimal 255 193 193 */
  coloradd ("RosyBrown2", 0x00eeb4b4);	/* color 647 r/g/b decimal 238 180 180 */
  coloradd ("RosyBrown3", 0x00cd9b9b);	/* color 648 r/g/b decimal 205 155 155 */
  coloradd ("RosyBrown4", 0x008b6969);	/* color 649 r/g/b decimal 139 105 105 */
  coloradd ("royal blue", 0x004169e1);	/* color 650 r/g/b decimal 65 105 225 */
  coloradd ("RoyalBlue", 0x004169e1);	/* color 651 r/g/b decimal 65 105 225 */
  coloradd ("RoyalBlue1", 0x004876ff);	/* color 652 r/g/b decimal 72 118 255 */
  coloradd ("RoyalBlue2", 0x00436eee);	/* color 653 r/g/b decimal 67 110 238 */
  coloradd ("RoyalBlue3", 0x003a5fcd);	/* color 654 r/g/b decimal 58 95 205 */
  coloradd ("RoyalBlue4", 0x0027408b);	/* color 655 r/g/b decimal 39 64 139 */
  coloradd ("saddle brown", 0x008b4513);	/* color 656 r/g/b decimal 139 69 19 */
  coloradd ("SaddleBrown", 0x008b4513);	/* color 657 r/g/b decimal 139 69 19 */
  coloradd ("salmon", 0x00fa8072);	/* color 658 r/g/b decimal 250 128 114 */
  coloradd ("salmon1", 0x00ff8c69);	/* color 659 r/g/b decimal 255 140 105 */
  coloradd ("salmon2", 0x00ee8262);	/* color 660 r/g/b decimal 238 130 98 */
  coloradd ("salmon3", 0x00cd7054);	/* color 661 r/g/b decimal 205 112 84 */
  coloradd ("salmon4", 0x008b4c39);	/* color 662 r/g/b decimal 139 76 57 */
  coloradd ("sandy brown", 0x00f4a460);	/* color 663 r/g/b decimal 244 164 96 */
  coloradd ("SandyBrown", 0x00f4a460);	/* color 664 r/g/b decimal 244 164 96 */
  coloradd ("sea green", 0x002e8b57);	/* color 665 r/g/b decimal 46 139 87 */
  coloradd ("SeaGreen", 0x002e8b57);	/* color 666 r/g/b decimal 46 139 87 */
  coloradd ("SeaGreen1", 0x0054ff9f);	/* color 667 r/g/b decimal 84 255 159 */
  coloradd ("SeaGreen2", 0x004eee94);	/* color 668 r/g/b decimal 78 238 148 */
  coloradd ("SeaGreen3", 0x0043cd80);	/* color 669 r/g/b decimal 67 205 128 */
  coloradd ("SeaGreen4", 0x002e8b57);	/* color 670 r/g/b decimal 46 139 87 */
  coloradd ("seashell", 0x00fff5ee);	/* color 671 r/g/b decimal 255 245 238 */
  coloradd ("seashell1", 0x00fff5ee);	/* color 672 r/g/b decimal 255 245 238 */
  coloradd ("seashell2", 0x00eee5de);	/* color 673 r/g/b decimal 238 229 222 */
  coloradd ("seashell3", 0x00cdc5bf);	/* color 674 r/g/b decimal 205 197 191 */
  coloradd ("seashell4", 0x008b8682);	/* color 675 r/g/b decimal 139 134 130 */
  coloradd ("sienna", 0x00a0522d);	/* color 676 r/g/b decimal 160 82 45 */
  coloradd ("sienna1", 0x00ff8247);	/* color 677 r/g/b decimal 255 130 71 */
  coloradd ("sienna2", 0x00ee7942);	/* color 678 r/g/b decimal 238 121 66 */
  coloradd ("sienna3", 0x00cd6839);	/* color 679 r/g/b decimal 205 104 57 */
  coloradd ("sienna4", 0x008b4726);	/* color 680 r/g/b decimal 139 71 38 */
  coloradd ("silver", 0x00c0c0c0);	/* color 681 r/g/b decimal 192 192 192 */
  coloradd ("sky blue", 0x0087ceeb);	/* color 682 r/g/b decimal 135 206 235 */
  coloradd ("SkyBlue", 0x0087ceeb);	/* color 683 r/g/b decimal 135 206 235 */
  coloradd ("SkyBlue1", 0x0087ceff);	/* color 684 r/g/b decimal 135 206 255 */
  coloradd ("SkyBlue2", 0x007ec0ee);	/* color 685 r/g/b decimal 126 192 238 */
  coloradd ("SkyBlue3", 0x006ca6cd);	/* color 686 r/g/b decimal 108 166 205 */
  coloradd ("SkyBlue4", 0x004a708b);	/* color 687 r/g/b decimal 74 112 139 */
  coloradd ("slate blue", 0x006a5acd);	/* color 688 r/g/b decimal 106 90 205 */
  coloradd ("slate gray", 0x00708090);	/* color 689 r/g/b decimal 112 128 144 */
  coloradd ("slate grey", 0x00708090);	/* color 690 r/g/b decimal 112 128 144 */
  coloradd ("SlateBlue", 0x006a5acd);	/* color 691 r/g/b decimal 106 90 205 */
  coloradd ("SlateBlue1", 0x00836fff);	/* color 692 r/g/b decimal 131 111 255 */
  coloradd ("SlateBlue2", 0x007a67ee);	/* color 693 r/g/b decimal 122 103 238 */
  coloradd ("SlateBlue3", 0x006959cd);	/* color 694 r/g/b decimal 105 89 205 */
  coloradd ("SlateBlue4", 0x00473c8b);	/* color 695 r/g/b decimal 71 60 139 */
  coloradd ("SlateGray", 0x00708090);	/* color 696 r/g/b decimal 112 128 144 */
  coloradd ("SlateGray1", 0x00c6e2ff);	/* color 697 r/g/b decimal 198 226 255 */
  coloradd ("SlateGray2", 0x00b9d3ee);	/* color 698 r/g/b decimal 185 211 238 */
  coloradd ("SlateGray3", 0x009fb6cd);	/* color 699 r/g/b decimal 159 182 205 */
  coloradd ("SlateGray4", 0x006c7b8b);	/* color 700 r/g/b decimal 108 123 139 */
  coloradd ("SlateGrey", 0x00708090);	/* color 701 r/g/b decimal 112 128 144 */
  coloradd ("snow", 0x00fffafa);	/* color 702 r/g/b decimal 255 250 250 */
  coloradd ("snow1", 0x00fffafa);	/* color 703 r/g/b decimal 255 250 250 */
  coloradd ("snow2", 0x00eee9e9);	/* color 704 r/g/b decimal 238 233 233 */
  coloradd ("snow3", 0x00cdc9c9);	/* color 705 r/g/b decimal 205 201 201 */
  coloradd ("snow4", 0x008b8989);	/* color 706 r/g/b decimal 139 137 137 */
  coloradd ("spring green", 0x0000ff7f);	/* color 707 r/g/b decimal 0 255 127 */
  coloradd ("SpringGreen", 0x0000ff7f);	/* color 708 r/g/b decimal 0 255 127 */
  coloradd ("SpringGreen1", 0x0000ff7f);	/* color 709 r/g/b decimal 0 255 127 */
  coloradd ("SpringGreen2", 0x0000ee76);	/* color 710 r/g/b decimal 0 238 118 */
  coloradd ("SpringGreen3", 0x0000cd66);	/* color 711 r/g/b decimal 0 205 102 */
  coloradd ("SpringGreen4", 0x00008b45);	/* color 712 r/g/b decimal 0 139 69 */
  coloradd ("steel blue", 0x004682b4);	/* color 713 r/g/b decimal 70 130 180 */
  coloradd ("SteelBlue", 0x004682b4);	/* color 714 r/g/b decimal 70 130 180 */
  coloradd ("SteelBlue1", 0x0063b8ff);	/* color 715 r/g/b decimal 99 184 255 */
  coloradd ("SteelBlue2", 0x005cacee);	/* color 716 r/g/b decimal 92 172 238 */
  coloradd ("SteelBlue3", 0x004f94cd);	/* color 717 r/g/b decimal 79 148 205 */
  coloradd ("SteelBlue4", 0x0036648b);	/* color 718 r/g/b decimal 54 100 139 */
  coloradd ("tan", 0x00d2b48c);	/* color 719 r/g/b decimal 210 180 140 */
  coloradd ("tan1", 0x00ffa54f);	/* color 720 r/g/b decimal 255 165 79 */
  coloradd ("tan2", 0x00ee9a49);	/* color 721 r/g/b decimal 238 154 73 */
  coloradd ("tan3", 0x00cd853f);	/* color 722 r/g/b decimal 205 133 63 */
  coloradd ("tan4", 0x008b5a2b);	/* color 723 r/g/b decimal 139 90 43 */
  coloradd ("teal", 0x00008080);	/* color 724 r/g/b decimal 0 128 128 */
  coloradd ("thistle", 0x00d8bfd8);	/* color 725 r/g/b decimal 216 191 216 */
  coloradd ("thistle1", 0x00ffe1ff);	/* color 726 r/g/b decimal 255 225 255 */
  coloradd ("thistle2", 0x00eed2ee);	/* color 727 r/g/b decimal 238 210 238 */
  coloradd ("thistle3", 0x00cdb5cd);	/* color 728 r/g/b decimal 205 181 205 */
  coloradd ("thistle4", 0x008b7b8b);	/* color 729 r/g/b decimal 139 123 139 */
  coloradd ("tomato", 0x00ff6347);	/* color 730 r/g/b decimal 255 99 71 */
  coloradd ("tomato1", 0x00ff6347);	/* color 731 r/g/b decimal 255 99 71 */
  coloradd ("tomato2", 0x00ee5c42);	/* color 732 r/g/b decimal 238 92 66 */
  coloradd ("tomato3", 0x00cd4f39);	/* color 733 r/g/b decimal 205 79 57 */
  coloradd ("tomato4", 0x008b3626);	/* color 734 r/g/b decimal 139 54 38 */
  coloradd ("turquoise", 0x0040e0d0);	/* color 735 r/g/b decimal 64 224 208 */
  coloradd ("turquoise1", 0x0000f5ff);	/* color 736 r/g/b decimal 0 245 255 */
  coloradd ("turquoise2", 0x0000e5ee);	/* color 737 r/g/b decimal 0 229 238 */
  coloradd ("turquoise3", 0x0000c5cd);	/* color 738 r/g/b decimal 0 197 205 */
  coloradd ("turquoise4", 0x0000868b);	/* color 739 r/g/b decimal 0 134 139 */
  coloradd ("violet", 0x00ee82ee);	/* color 740 r/g/b decimal 238 130 238 */
  coloradd ("violet red", 0x00d02090);	/* color 741 r/g/b decimal 208 32 144 */
  coloradd ("VioletRed", 0x00d02090);	/* color 742 r/g/b decimal 208 32 144 */
  coloradd ("VioletRed1", 0x00ff3e96);	/* color 743 r/g/b decimal 255 62 150 */
  coloradd ("VioletRed2", 0x00ee3a8c);	/* color 744 r/g/b decimal 238 58 140 */
  coloradd ("VioletRed3", 0x00cd3278);	/* color 745 r/g/b decimal 205 50 120 */
  coloradd ("VioletRed4", 0x008b2252);	/* color 746 r/g/b decimal 139 34 82 */
  coloradd ("web gray", 0x00808080);	/* color 747 r/g/b decimal 128 128 128 */
  coloradd ("web green", 0x00008000);	/* color 748 r/g/b decimal 0 128 0 */
  coloradd ("web grey", 0x00808080);	/* color 749 r/g/b decimal 128 128 128 */
  coloradd ("web maroon", 0x00800000);	/* color 750 r/g/b decimal 128 0 0 */
  coloradd ("web purple", 0x00800080);	/* color 751 r/g/b decimal 128 0 128 */
  coloradd ("WebGray", 0x00808080);	/* color 752 r/g/b decimal 128 128 128 */
  coloradd ("WebGreen", 0x00008000);	/* color 753 r/g/b decimal 0 128 0 */
  coloradd ("WebGrey", 0x00808080);	/* color 754 r/g/b decimal 128 128 128 */
  coloradd ("WebMaroon", 0x00800000);	/* color 755 r/g/b decimal 128 0 0 */
  coloradd ("WebPurple", 0x00800080);	/* color 756 r/g/b decimal 128 0 128 */
  coloradd ("wheat", 0x00f5deb3);	/* color 757 r/g/b decimal 245 222 179 */
  coloradd ("wheat1", 0x00ffe7ba);	/* color 758 r/g/b decimal 255 231 186 */
  coloradd ("wheat2", 0x00eed8ae);	/* color 759 r/g/b decimal 238 216 174 */
  coloradd ("wheat3", 0x00cdba96);	/* color 760 r/g/b decimal 205 186 150 */
  coloradd ("wheat4", 0x008b7e66);	/* color 761 r/g/b decimal 139 126 102 */
  coloradd ("white", 0x00ffffff);	/* color 762 r/g/b decimal 255 255 255 */
  coloradd ("white smoke", 0x00f5f5f5);	/* color 763 r/g/b decimal 245 245 245 */
  coloradd ("WhiteSmoke", 0x00f5f5f5);	/* color 764 r/g/b decimal 245 245 245 */
  coloradd ("x11 gray", 0x00bebebe);	/* color 765 r/g/b decimal 190 190 190 */
  coloradd ("x11 green", 0x0000ff00);	/* color 766 r/g/b decimal 0 255 0 */
  coloradd ("x11 grey", 0x00bebebe);	/* color 767 r/g/b decimal 190 190 190 */
  coloradd ("x11 maroon", 0x00b03060);	/* color 768 r/g/b decimal 176 48 96 */
  coloradd ("x11 purple", 0x00a020f0);	/* color 769 r/g/b decimal 160 32 240 */
  coloradd ("X11Gray", 0x00bebebe);	/* color 770 r/g/b decimal 190 190 190 */
  coloradd ("X11Green", 0x0000ff00);	/* color 771 r/g/b decimal 0 255 0 */
  coloradd ("X11Grey", 0x00bebebe);	/* color 772 r/g/b decimal 190 190 190 */
  coloradd ("X11Maroon", 0x00b03060);	/* color 773 r/g/b decimal 176 48 96 */
  coloradd ("X11Purple", 0x00a020f0);	/* color 774 r/g/b decimal 160 32 240 */
  coloradd ("yellow", 0x00ffff00);	/* color 775 r/g/b decimal 255 255 0 */
  coloradd ("yellow green", 0x009acd32);	/* color 776 r/g/b decimal 154 205 50 */
  coloradd ("yellow1", 0x00ffff00);	/* color 777 r/g/b decimal 255 255 0 */
  coloradd ("yellow2", 0x00eeee00);	/* color 778 r/g/b decimal 238 238 0 */
  coloradd ("yellow3", 0x00cdcd00);	/* color 779 r/g/b decimal 205 205 0 */
  coloradd ("yellow4", 0x008b8b00);	/* color 780 r/g/b decimal 139 139 0 */
  coloradd ("YellowGreen", 0x009acd32);	/* color 781 r/g/b decimal 154 205 50 */

  return;
}

/* add 1 color to database */
static void
coloradd (const char *name, int code)
{
  struct skls_n *node = NULL;
  node = skls_add (gucolor, (char *) name);
  if (node)
    {
      node->value.i = code;
    }
  return;
}

/* search colorname in database and return argb or -1 on unknown color name */
int
colorcode (const char *name)
{
  struct skls_n *spn = NULL;
  int n = 0;
  unsigned int red = 0;
  unsigned int green = 0;
  unsigned int blue = 0;

  if (name == NULL)
    {
      return ((int) -1);
    }

  /* check for "" */
  if (strlen (name) == 0)
    {
      return ((int) -1);
    }

  if (gucolor == NULL)
    {
      color_init ();
    }

  if (name[0] == '#')
    {
      /* assume html color #rrggbb */
      n = sscanf (name, "#%02x%02x%02x", &red, &green, &blue);
      if (n != 3)
	{
	  return ((int) -1);
	}
      return ((red << 16) | (green << 8) | blue);
    }

  spn = skls_find (gucolor, (char *) name);

  if (spn)
    {
      return ((int) spn->value.i);
    }

  /* unknown color name */
  return ((int) -1);
}

/* end */

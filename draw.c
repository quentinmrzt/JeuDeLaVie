/******************************************************************/
/* draw.c                                                         */
/* Quentin MORIZOT                                                */
/* Creation: 29/11/15                                             */
/* Last modification: 30/11/15                                    */
/******************************************************************/

#include "constant.h"
#include "draw.h"

/****************************************************************************************************/
/* DRAW */

void draw(int x_max, int y_max, int tab[y_max][x_max], s_surface sprite, int size_cell)
{
  int x,y; 
  SDL_Rect pos_sprite, pos_screen;

  pos_sprite.x = 0;
  pos_sprite.y = 0;
  pos_sprite.w = size_cell;
  pos_sprite.h = size_cell;

  for (y=0 ; y<y_max ; y++) {
    for (x=0 ; x<x_max ; x++) {
      pos_screen.x = x*size_cell;
      pos_screen.y = y*size_cell;
      if (tab[y][x] == 1) {
	SDL_BlitSurface(sprite.white, &pos_sprite, sprite.screen, &pos_screen);
      } else if (tab[y][x] == 2) {
	SDL_BlitSurface(sprite.green, &pos_sprite, sprite.screen, &pos_screen);
      } else {
	SDL_BlitSurface(sprite.black, &pos_sprite, sprite.screen, &pos_screen);
      }
    }
  }
}

/******************************************************************/
/* draw.c                                                         */
/* Quentin MORIZOT                                                */
/* Creation: 02/12/15                                             */
/* Last modification: 02/12/15                                    */
/******************************************************************/

#include "constant.h"
#include "draw.h"

/****************************************************************************************************/
/* DRAW */

void draw(int x_max, int y_max, int tab[y_max][x_max], s_surface sprite, int size_cell, SDL_Rect min, SDL_Rect max)
{
  int x,y,a,b; 
  SDL_Rect pos_sprite, pos_screen;

  pos_sprite.x = 0;
  pos_sprite.y = 0;
  pos_sprite.w = size_cell;
  pos_sprite.h = size_cell;

  b=0;
  for (y=min.y ; y<max.y ; y++) {
    a=0;
    for (x=min.x ; x<max.x ; x++) {
      pos_screen.x = a*size_cell;
      pos_screen.y = b*size_cell;
      if (tab[y][x] == 1) {
	SDL_BlitSurface(sprite.white, &pos_sprite, sprite.screen, &pos_screen);
      } else if (tab[y][x] == 2) {
	SDL_BlitSurface(sprite.green, &pos_sprite, sprite.screen, &pos_screen);
      } else {
	SDL_BlitSurface(sprite.black, &pos_sprite, sprite.screen, &pos_screen);
      }
      a++;
    }
    b++;
  }
}

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

void draw_text_cursor(s_surface sprite, int x_screen, SDL_Rect line, SDL_Rect cursor, int min, int max)
{
  char sentence[20] = "";
  SDL_Rect pos_screen;
  SDL_Color white_color = {255,255,255,0};
  SDL_Surface *text;
  TTF_Font *font = NULL;

  font = TTF_OpenFont("pixelmix.ttf", 10);

  // Text: size
  sprintf(sentence, "Taille de l'ecran: %d",x_screen);
  text = TTF_RenderText_Blended(font, sentence, white_color);
  pos_screen.x = line.x + line.w/2 - text->w/2;
  pos_screen.y = cursor.y - text->h - 5;
  SDL_BlitSurface(text, NULL, sprite.screen, &pos_screen);
  SDL_FreeSurface(text);

  // Text: size min
  sprintf(sentence, "%d",min);
  text = TTF_RenderText_Blended(font, sentence, white_color);
  pos_screen.x = line.x - text->w/2;
  pos_screen.y = (cursor.y+cursor.h) + 3;
  SDL_BlitSurface(text, NULL, sprite.screen, &pos_screen);
  SDL_FreeSurface(text);

  // Text: size max
  sprintf(sentence, "%d",max);
  text = TTF_RenderText_Blended(font, sentence, white_color);
  pos_screen.x = (line.x+line.w) - text->w/2;
  pos_screen.y = (cursor.y+cursor.h) + 3;
  SDL_BlitSurface(text, NULL, sprite.screen, &pos_screen);
  SDL_FreeSurface(text);

  TTF_CloseFont(font);

}

void draw_line_cursor(s_surface sprite, SDL_Rect line)
{
  SDL_Rect pos_screen, pos_sprite;
  int x,y;

  pos_sprite.x = 0;
  pos_sprite.y = 0;
  pos_sprite.w = 1;
  pos_sprite.h = 1;

  for (y=line.y ; y<line.y+line.h ; y++) {
    for (x=line.x ; x<line.x+line.w ; x++) {
      pos_screen.x = x;
      pos_screen.y = y;
      SDL_BlitSurface(sprite.white, &pos_sprite, sprite.screen, &pos_screen);
    }
  }
}

void draw_button_cursor(s_surface sprite, SDL_Rect cursor)
{
  SDL_Rect pos_screen, pos_sprite;
  int x,y;

  pos_sprite.x = 0;
  pos_sprite.y = 0;
  pos_sprite.w = 1;
  pos_sprite.h = 1;

  for (y=cursor.y ; y<cursor.y+cursor.h ; y++) {
    for (x=cursor.x ; x<cursor.x+cursor.w ; x++) {
      pos_screen.x = x;
      pos_screen.y = y;
      if (x == cursor.x || y == cursor.y || x == cursor.x+cursor.w-1 || y == cursor.y+cursor.h-1) {
	SDL_BlitSurface(sprite.white, &pos_sprite, sprite.screen, &pos_screen);
      } else {
	SDL_BlitSurface(sprite.black, &pos_sprite, sprite.screen, &pos_screen);
      }
    }
  }
}

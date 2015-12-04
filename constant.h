/******************************************************************/
/* constant.h                                                     */
/* Quentin MORIZOT                                                */
/* Creation: 02/12/15                                             */
/* Last modification: 02/12/15                                    */
/******************************************************************/

#ifndef CONSTANT_H
#define CONSTANT_H

#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

struct s_surface
{
  SDL_Surface *screen;
  SDL_Surface *black;
  SDL_Surface *white;
  SDL_Surface *green;
};
typedef struct s_surface s_surface;

struct s_time
{
  int current; 
  int previous;
};
typedef struct s_time s_time;


typedef struct
{
  char key[SDLK_LAST];
  int mousex,mousey;
  int mousexrel,mouseyrel;
  /* SDL_BUTTON_LEFT  SDL_BUTTON_MIDDLE  SDL_BUTTON_RIGHt  SDL_BUTTON_WHEELUP
     SDL_BUTTON_WHEELDOWN  SDL_BUTTON_X1  SDL_BUTTON_X2 */
  char mousebuttons[8];
  char quit;
} Input;

#endif 

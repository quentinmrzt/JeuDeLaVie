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
  char mousebuttons[8];
  char quit;
} Input;

#endif 

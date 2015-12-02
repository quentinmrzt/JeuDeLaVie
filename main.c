/******************************************************************/
/* main.c                                                         */
/* Quentin MORIZOT                                                */
/* Creation: 02/12/15                                             */
/* Last modification: 02/12/15                                    */
/******************************************************************/

#include "constant.h"
#include "game.h"
#include "draw.h"
#include "control.h"

int main(int argc, char* argv[])
{
  int close, x_max, y_max, generation, size_cell, x_screen, y_screen, waiting;
  s_surface sprite;
  s_time time;

  /****************************************************************************************************/
  /* INITIALIZE VARIABLE */
  size_cell = ask_size_cell();
  x_screen = (ask_x()/size_cell)*size_cell;
  y_screen = (ask_y()/size_cell)*size_cell;

  x_max = x_screen/size_cell;
  y_max = y_screen/size_cell;
  int tab_one[y_max][x_max];
  int tab_two[y_max][x_max];
  ini_tab(x_max,y_max,tab_one);
  ini_tab(x_max,y_max,tab_two);
  choice_pattern(x_max,y_max,tab_one,tab_two,ask_pattern());

  waiting = ask_waiting();
  time = ini_time(time);
  close = 0;
  generation = 0;

  /****************************************************************************************************/
  /* INITIALIZE VIDEO */
  if (SDL_Init(SDL_INIT_VIDEO) == -1) {
    fprintf(stderr,"Erreur lors de l'initialisation de la SDL\n");
    return -1;
  }
  putenv("SDL_VIDEO_WINDOW_POS=center");
  SDL_WM_SetCaption("Jeu de la vie", NULL);

  sprite.screen = SDL_SetVideoMode(x_screen, y_screen, 0, 0);
  if (sprite.screen == NULL) {
    fprintf(stderr,"Erreur lors de l'ouverture de la fenetre\n");
    SDL_Quit();
    return -2;
  }
  sprite = load_sprite(sprite);

  while (!close) {
    /****************************************************************************************************/
    /* TIME */
    time.current = SDL_GetTicks();

    /****************************************************************************************************/
    /* KEYBOARD AND MOUSE */
    close = quit(close);

    /****************************************************************************************************/
    /* GAME */
    next_generation(x_max,y_max,tab_one,tab_two,&generation);
    time.previous = time.current;

    /****************************************************************************************************/
    /* DRAW */
    draw(x_max,y_max,tab_one,sprite,size_cell);

    /****************************************************************************************************/
    /* OTHER */
    SDL_UpdateRect(sprite.screen,0,0,0,0);
    SDL_Delay(waiting);
  }

  printf("Generation: %d\n",generation);

  /****************************************************************************************************/
  /* CLEAN */
  free_all_sprite(sprite);
  SDL_Quit();

  return 0;
}

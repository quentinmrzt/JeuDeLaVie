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
  int x_max, y_max, generation, size_cell, x_screen, y_screen, waiting;
  s_surface sprite;
  s_time time;
  SDL_Event event;
  Input in;


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
  generation = 0;
  memset(&in,0,sizeof(in)); // ini tout a 0

  /****************************************************************************************************/
  /* INITIALIZE VIDEO */
  if (SDL_Init(SDL_INIT_VIDEO) == -1) {
    printf("Erreur lors de l'initialisation de la SDL\n");
    return -1;
  }
  putenv("SDL_VIDEO_WINDOW_POS=center");
  SDL_WM_SetCaption("Jeu de la vie", NULL);

  sprite.screen = SDL_SetVideoMode(x_screen, y_screen, 0, SDL_DOUBLEBUF);
  if (sprite.screen == NULL) {
    printf("Erreur lors de l'ouverture de la fenetre\n");
    SDL_Quit();
    return -2;
  }
  sprite = load_sprite(sprite); // prevoir le cas == NULL

  while (!in.key[SDLK_ESCAPE] && !in.quit) {
    /****************************************************************************************************/
    /* TIME */
    time.current = SDL_GetTicks();

    /****************************************************************************************************/
    /* KEYBOARD AND MOUSE */
    UpdateEvents(&in);
    //printf("mouse pos:  x: %d  y: %d\n",in.mousex,in.mousey);
    //printf("mouse rel:  x: %d  y: %d\n",in.mousexrel,in.mouseyrel);
    if (in.mousebuttons[SDL_BUTTON_LEFT]) {
      printf("CLICK\n");
      in.mousebuttons[SDL_BUTTON_LEFT] = 0;
    }
    /****************************************************************************************************/
    /* GAME */
    next_generation(x_max,y_max,tab_one,tab_two,&generation);
    time.previous = time.current;

    /****************************************************************************************************/
    /* DRAW */
    SDL_FillRect(sprite.screen, NULL, SDL_MapRGB(sprite.screen->format, 0, 0, 0)); // ecran noir
    draw(x_max,y_max,tab_one,sprite,size_cell);

    /****************************************************************************************************/
    /* OTHER */
    SDL_Flip(sprite.screen); 
    SDL_Delay(waiting);
  }

  printf("Generation: %d\n",generation);

  /****************************************************************************************************/
  /* CLEAN */
  free_all_sprite(sprite);
  SDL_Quit();

  return 0;
}

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
  SDL_Rect min, max;

  /****************************************************************************************************/
  /* INITIALIZE VARIABLE */
  size_cell = 1;
  x_screen = (ask_x()/size_cell)*size_cell;
  y_screen = (ask_y()/size_cell)*size_cell;

  x_max = x_screen/size_cell;
  y_max = y_screen/size_cell;

  max.x = x_max;
  max.y = y_max;
  min.x = 0;
  min.y = 0;

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

    /***** CLICK *****/
    if (in.mousebuttons[SDL_BUTTON_LEFT]) {
      if (tab_two[min.y+(in.mousey/size_cell)][min.x+(in.mousex/size_cell)] == 2) {
	tab_one[min.y+(in.mousey/size_cell)][min.x+(in.mousex/size_cell)] = 1;
	tab_two[min.y+(in.mousey/size_cell)][min.x+(in.mousex/size_cell)] = 1;
      } else {
	tab_one[min.y+(in.mousey/size_cell)][min.x+(in.mousex/size_cell)] = 2;
	tab_two[min.y+(in.mousey/size_cell)][min.x+(in.mousex/size_cell)] = 2;
      }
      in.mousebuttons[SDL_BUTTON_LEFT] = 0;
    }

    /***** ZOOM + *****/
    if (in.mousebuttons[SDL_BUTTON_WHEELUP]  && size_cell != 10) {
      size_cell++;
      if (size_cell > 10) {
	size_cell = 10;
      }
      max.x = (min.x+(in.mousex/(size_cell-1))) + (x_screen/size_cell)/2;
      max.y = (min.y+(in.mousey/(size_cell-1))) + (y_screen/size_cell)/2;
      if (max.x > x_screen) {
	max.x = x_screen;
      }
      if (max.y > y_screen) {
	max.y = y_screen;
      }
      min.x = max.x - (x_screen/size_cell);
      min.y = max.y - (y_screen/size_cell);
      if (min.x < 0) {
	min.x = 0;
	max.x = x_screen/size_cell;
      }
      if (min.y < 0) {
	min.y = 0;
	max.y = y_screen/size_cell;
      }
    }

    /***** ZOOM - *****/
    if (in.mousebuttons[SDL_BUTTON_WHEELDOWN] && size_cell != 1) {
      size_cell--;
      if (size_cell <= 0) {
	size_cell = 1;
      }
      max.x = (min.x+(in.mousex/(size_cell+1))) + (x_screen/size_cell)/2;
      max.y = (min.y+(in.mousey/(size_cell+1))) + (y_screen/size_cell)/2;
      if (max.x >= x_screen) {
	max.x = x_screen;
      }
      if (max.y >= y_screen) {
	max.y = y_screen;
      }
      min.x = max.x - (x_screen/size_cell);
      min.y = max.y - (y_screen/size_cell);
      if (min.x < 0) {
	min.x = 0;
	max.x = x_screen/size_cell;
      }
      if (min.y < 0) {
	min.y = 0;
	max.y = y_screen/size_cell;
      }
    }

    /***** MOUVE *****/
    if (in.key[SDLK_UP]) {
      max.y--;
      min.y--;
      if (max.y > y_screen || min.y < 0) {
	max.y++;
	min.y++;
      }
    }
    if (in.key[SDLK_DOWN]) {
      max.y++;
      min.y++;
      if (max.y > y_screen || min.y < 0) {
	max.y--;
	min.y--;
      }
    }
    if (in.key[SDLK_LEFT]) {
      max.x--;
      min.x--;
      if (max.x > x_screen || min.x < 0) {
	max.x++;
	min.x++;
      }
    }
    if (in.key[SDLK_RIGHT]) {
      max.x++;
      min.x++;
      if (max.x > x_screen ||min.x < 0) {
	max.x--;
	min.x--;
      }
    }


    /****************************************************************************************************/
    /* GAME */
    if (in.key[SDLK_RETURN]) {
      next_generation(x_max,y_max,tab_one,tab_two,&generation);
      time.previous = time.current;
    }

    /****************************************************************************************************/
    /* DRAW */
    SDL_FillRect(sprite.screen, NULL, SDL_MapRGB(sprite.screen->format, 0, 0, 0)); // ecran noir
    draw(x_max,y_max,tab_one,sprite,size_cell,min,max);

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

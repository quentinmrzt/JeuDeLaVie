/******************************************************************/
/* game.c                                                         */
/* Quentin MORIZOT                                                */
/* Creation: 29/11/15                                             */
/* Last modification: 30/11/15                                    */
/******************************************************************/

#include "constant.h"
#include "game.h"


/****************************************************************************************************/
/* INITIALIZE */

SDL_Surface* load(SDL_Surface *surface, char name[], SDL_Surface *screen) 
{
  SDL_Surface *temp;
  int colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
  temp = SDL_LoadBMP(name);
  surface = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  SDL_SetColorKey(surface, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  return surface;
}

s_surface load_sprite(s_surface sprite) 
{
  char name[] = "sprite/sprite_01.bmp";
  sprite.black = load(sprite.black, name, sprite.screen);
  name[15] = '2';
  sprite.white = load(sprite.white, name, sprite.screen);
  name[15] = '3';
  sprite.green = load(sprite.green, name, sprite.screen);

  return sprite;
}

s_time ini_time(s_time time)
{
  time.current = 0; 
  time.previous = 0;

  return time;
}

void ini_tab(int x_max, int y_max,int tab[y_max][x_max])
{
  int x,y;

  for (y=0 ; y<y_max ; y++) {
    for (x=0 ; x<x_max ; x++) {
      tab[y][x] = 0;
    }
  }
}


/****************************************************************************************************/
/* GAME */

int nb_life(int x_max, int y_max,int tab[y_max][x_max], int x, int y)
{
  int nb = 0;

  /* 1 */
  if (x > 0 && y > 0) {
    if (tab[y-1][x-1] == 1) {
      nb++;
    }
  }

  /* 2 */
  if (y > 0) {
    if (tab[y-1][x] == 1) {
      nb++;
    }
  }

  /* 3 */
  if (x < x_max-1 && y > 0) {
    if (tab[y-1][x+1] == 1) {
      nb++;
    }
  }

  /* 4 */
  if (x > 0) {
    if (tab[y][x-1] == 1) {
      nb++;
    }
  }

  /* 5 */
  if (x < x_max-1) {
    if (tab[y][x+1] == 1) {
      nb++;
    }
  }

  /* 6 */
  if (x > 0 && y < y_max-1) {
    if (tab[y+1][x-1] == 1) {
      nb++;
    }
  }

  /* 7 */
  if (y < y_max-1) {
    if (tab[y+1][x] == 1) {
      nb++;
    }
  }

  /* 8 */
  if (x < x_max-1 && y < y_max-1) {
    if (tab[y+1][x+1] == 1) {
      nb++;
    }
  }

  return nb;
}

void next_generation(int x_max, int y_max, int tab_one[y_max][x_max], int tab_two[y_max][x_max], int *generation)
{
  int x, y;

  for (y=0 ; y<y_max ; y++) {
    for (x=0 ; x<x_max ; x++) {
      if ((tab_one[y][x] == 0 || tab_one[y][x] == 2) && nb_life(x_max,y_max,tab_one,x,y) == 3) {
	tab_two[y][x] = 1;
      } else if (tab_one[y][x] == 1 && (nb_life(x_max,y_max,tab_one,x,y) < 2 || nb_life(x_max,y_max,tab_one,x,y) > 3)) {
	tab_two[y][x] = 2;
      }
    }
  }

  for (y=0 ; y<y_max ; y++) {
    for (x=0 ; x<x_max ; x++) {
      tab_one[y][x] = tab_two[y][x];
    }
  }

  *generation = *generation+1;
}

int ask_size_cell(void)
{
  int size_cell;

  printf("Taille de la cellule: ");
  scanf("%d", &size_cell);
  if (size_cell <= 0) {
    printf("Chiffre invalide, initialise a 1.\n");
    size_cell = 1;
  } else if (size_cell > 10) {
    printf("Chiffre invalide, initialise a 10.\n");
    size_cell = 10;
  }

  return size_cell;
}

int ask_x(void)
{
  int x;

  printf("Taille de l'ecran en x: ");
  scanf("%d", &x);
  if (x <= 0) {
    printf("Chiffre invalide, initialise a 1000.\n");
    x = 1000;
  }
  
  return x;
}

int ask_y(void)
{
  int y;

  printf("Taille de l'ecran en y: ");
  scanf("%d", &y);
  if (y <= 0) {
    printf("Chiffre invalide, initialise a 600.\n");
    y = 600;
  }
  
  return y;
}

int ask_pattern(void)
{
  int pattern;

  printf("1: Acorn  2: Gun  3: line\nChoix: ");
  scanf("%d", &pattern);

  return pattern;
}

void choice_pattern(int x_max, int y_max, int tab_one[y_max][x_max], int tab_two[y_max][x_max], int pattern)
{
  if (pattern == 1) {
    acorn(x_max,y_max,tab_one,x_max/2,y_max/2);
    acorn(x_max,y_max,tab_two,x_max/2,y_max/2);
  } else if (pattern == 2) {
    gun(x_max,y_max,tab_one,10,10);
    gun(x_max,y_max,tab_two,10,10);
  } else if (pattern == 3) {
    line(x_max,y_max,tab_one,y_max/2);
    line(x_max,y_max,tab_two,y_max/2);
  } else {
    printf("Chiffre invalide, initialise a 1.\n");
    pattern = 1;
  } 
}

int ask_waiting(void)
{
  int waiting;

  printf("Temps d'attente entre chaque boucle: ");
  scanf("%d", &waiting);
  if (waiting < 0) {
    printf("Chiffre invalide, initialise a 0.\n");
    waiting = 0;
  }

  return waiting;
}

/****************************************************************************************************/
/* PATTERNS */

void acorn(int x_max, int y_max,int tab[y_max][x_max], int x, int y) 
{
  tab[y][x] = 1;
  tab[y][x+1] = 1;
  tab[y-2][x+1] = 1;
  tab[y-1][x+3] = 1;
  tab[y][x+4] = 1;
  tab[y][x+5] = 1;
  tab[y][x+6] = 1;
}

void gun(int x_max, int y_max,int tab[y_max][x_max], int x, int y) 
{
  /* carre */
  tab[y+4][x] = 1;
  tab[y+5][x] = 1;
  tab[y+4][x+1] = 1;
  tab[y+5][x+1] = 1;

  /* rond */
  tab[y+4][x+10] = 1;
  tab[y+5][x+10] = 1;
  tab[y+6][x+10] = 1;
  tab[y+3][x+11] = 1;
  tab[y+7][x+11] = 1;
  tab[y+2][x+12] = 1;
  tab[y+8][x+12] = 1;
  tab[y+2][x+13] = 1;
  tab[y+8][x+13] = 1;
  tab[y+5][x+14] = 1;
  tab[y+3][x+15] = 1;
  tab[y+7][x+15] = 1;
  tab[y+4][x+16] = 1;
  tab[y+5][x+16] = 1;
  tab[y+6][x+16] = 1;
  tab[y+5][x+17] = 1;

  /* c */
  tab[y+2][x+20] = 1;
  tab[y+3][x+20] = 1;
  tab[y+4][x+20] = 1;
  tab[y+2][x+21] = 1;
  tab[y+3][x+21] = 1;
  tab[y+4][x+21] = 1;
  tab[y+1][x+22] = 1;
  tab[y+5][x+22] = 1;
  tab[y][x+24] = 1;
  tab[y+1][x+24] = 1;
  tab[y+5][x+24] = 1;
  tab[y+6][x+24] = 1;

  /* carre */
  tab[y+2][x+34] = 1;
  tab[y+3][x+34] = 1;
  tab[y+2][x+35] = 1;
  tab[y+3][x+35] = 1;
}

void line(int x_max, int y_max,int tab[y_max][x_max], int y)
{
  int x;

  for (x=0 ; x<x_max ; x++) {
    tab[y][x] = 1;
  }
}


/****************************************************************************************************/
/* CLEAN */

void free_all_sprite(s_surface sprite) 
{
  SDL_FreeSurface(sprite.screen);
  SDL_FreeSurface(sprite.black);
  SDL_FreeSurface(sprite.white);
  SDL_FreeSurface(sprite.green);
}

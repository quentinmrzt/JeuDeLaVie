/******************************************************************/
/* game.h                                                         */
/* Quentin MORIZOT                                                */
/* Creation: 02/12/15                                             */
/* Last modification: 02/12/15                                    */
/******************************************************************/

#ifndef GAME_H
#define GAME_H

/****************************************************************************************************/
/* INITIALIZE */
SDL_Surface* load(SDL_Surface *surface, char name[], SDL_Surface *screen);
s_surface load_sprite(s_surface sprite);
s_time ini_time(s_time time);
void ini_tab(int x_max, int y_max,int tab[y_max][x_max]);

/****************************************************************************************************/
/* GAME */
int nb_life(int x_max, int y_max,int tab[y_max][x_max], int x, int y);
void next_generation(int x_max, int y_max, int tab_one[y_max][x_max], int tab_two[y_max][x_max], int *generation);
int ask_size_cell(void);
int ask_x(void);
int ask_y(void);
int ask_pattern(void);
void choice_pattern(int x_max, int y_max, int tab_one[y_max][x_max], int tab_two[y_max][x_max], int pattern);
int ask_waiting(void);
int in_mouse(Input in, SDL_Rect min, SDL_Rect max);

/****************************************************************************************************/
/* PATTERNS */
void acorn(int x_max, int y_max,int tab[y_max][x_max], int x, int y);
void gun(int x_max, int y_max,int tab[y_max][x_max], int x, int y);
void line(int x_max, int y_max,int tab[y_max][x_max], int y);

/****************************************************************************************************/
/* CLEAN */
void free_all_sprite(s_surface sprite);


SDL_Rect ini_line_cursor(int x, int y, int w, int h);
SDL_Rect ini_button_cursor(SDL_Rect line, int w, int h);
int cross_product(SDL_Rect cursor, SDL_Rect line, int min, int max);
SDL_Rect move_cursor(Input in, SDL_Rect cursor, SDL_Rect line);

#endif

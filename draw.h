/******************************************************************/
/* draw.h                                                         */
/* Quentin MORIZOT                                                */
/* Creation: 02/12/15                                             */
/* Last modification: 02/12/15                                    */
/******************************************************************/

#ifndef DRAW_H
#define DRAW_H

/****************************************************************************************************/
/* DRAW */

void draw(int x_max, int y_max, int tab[y_max][x_max], s_surface sprite, int size_cell, SDL_Rect min, SDL_Rect max);
void draw_text_cursor(s_surface sprite, int x_screen, SDL_Rect line, SDL_Rect cursor, int min, int max);
void draw_line_cursor(s_surface sprite, SDL_Rect line);
void draw_button_cursor(s_surface sprite, SDL_Rect cursor);

#endif

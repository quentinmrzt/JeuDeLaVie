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

#endif

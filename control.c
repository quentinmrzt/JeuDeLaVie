/******************************************************************/
/* control.c                                                      */
/* Quentin MORIZOT                                                */
/* Creation: 02/12/15                                             */
/* Last modification: 02/12/15                                    */
/******************************************************************/

#include "constant.h"
#include "control.h"

/****************************************************************************************************/
/* KEYBOARD AND MOUSE */

int quit(int close) 
{
  SDL_Event event;

  /* look for an event */
  if (SDL_PollEvent(&event)) {
    /* an event was found */
    switch (event.type) 
      {
	/* close button clicked */
      case SDL_QUIT:
	close = 1;
	break;	 
	/* handle the keyboard */     
      case SDL_KEYDOWN:
	switch (event.key.keysym.sym) 
	  {
	  case SDLK_ESCAPE:
	    close = 1;
	    break;
	  }
	break;
      }
  }

  return close;
}

void UpdateEvents(Input* in)
{
  SDL_Event event;
  in->mousebuttons[SDL_BUTTON_WHEELUP] = 0;
  in->mousebuttons[SDL_BUTTON_WHEELDOWN] = 0;
  while(SDL_PollEvent(&event))
    {
      switch (event.type)
	{
	case SDL_KEYDOWN:
	  in->key[event.key.keysym.sym]=1;
	  break;
	case SDL_KEYUP:
	  in->key[event.key.keysym.sym]=0;
	  break;
	case SDL_MOUSEMOTION:
	  in->mousex=event.motion.x;
	  in->mousey=event.motion.y;
	  in->mousexrel=event.motion.xrel;
	  in->mouseyrel=event.motion.yrel;
	  break;
	case SDL_MOUSEBUTTONDOWN:
	  in->mousebuttons[event.button.button]=1;
	  break;
	case SDL_MOUSEBUTTONUP:
	  if (event.button.button!=SDL_BUTTON_WHEELUP && event.button.button!=SDL_BUTTON_WHEELDOWN)
	    in->mousebuttons[event.button.button]=0;
	  break;
	case SDL_QUIT:
	  in->quit = 1;
	  break;
	default:
	  break;
	}
    }
}

#ifndef _Line_H_
#define _Line_H_

void swap(int* A, int* B);
void VLine(int x, int y1, int y2, SDL_Surface *screen, SDL_Color color);
void HLine(int x1, int x2, int y, SDL_Color color, SDL_Surface *screen);
void Line(int x1, int y1, int x2, int y2, SDL_Color color, SDL_Surface* screen);
void  LinearMove(SDL_Rect *rectDest, int mx, int my);

#endif
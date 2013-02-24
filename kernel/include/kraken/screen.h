#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED

#include <stdint.h>
#include <kraken/portio.h>

enum DISP_COLORS {
	BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN,
	LGRAY, DGRAY, LBLUE, LGREEN, LCYAN, LRED,
	LMAGENTA, LBROWN, WHITE
};

#define COLOR(BG, FG) ((BG << 4) | FG) << 8
#define SCREEN_H 25
#define SCREEN_W 80

void screen_putchar (const char c);
void screen_clear ();
void screen_scroll (void);
void screen_print (const char *l);
void screen_setcolor (uint8_t bg, uint8_t fg);
void screen_defcolor (void);
void screen_setcursor (uint8_t x, uint8_t y);
char screen_hascolor (void);

#endif // SCREEN_H_INCLUDED

#include <kraken/screen.h>

uint16_t *screen_vmem = (uint16_t *) 0xb8000;
int screen_cx = 0, screen_cy = 0;
uint16_t current_color = COLOR (BLACK, GREEN);

void
screen_putchar (const char c)
{
	if (c == 0x08 && screen_cx)
		{
			screen_cx --;
			screen_putchar (' ');
			screen_cx--;
		}
	else if (c == 0x09)
		{
			screen_cx = (screen_cx + 8) & ~(8 - 1);
		}
	else if (c == '\r')
		{
			screen_cx = 0;
		}
	else if (c == '\n')
		{
			screen_cx = 0;
			screen_cy++;
		}
	else if (c >= ' ')
		{
			*(screen_vmem + screen_cy * SCREEN_W + screen_cx) = c | current_color;
			screen_cx++;
		}

	if (screen_cx >= SCREEN_W)
		{
			screen_cx = 0;
			screen_cy++;
		}
	if (screen_cy >= SCREEN_H)
		screen_scroll ();

	screen_setcursor (screen_cx, screen_cy);
}

void
screen_scroll (void)
{
	int i;

	for (i = 0; i < SCREEN_H * SCREEN_W; i++)
		{
			screen_vmem[i] = screen_vmem[i + 80];
		}
	screen_cy--;
}

void
screen_print (const char *l)
{
	while (*l)
		{
			screen_putchar (*l);
			l++;
		}
}

void
screen_clear (void)
{
	int i;

	for (i = 0; i <= SCREEN_W * SCREEN_H; i++)
		screen_vmem[i] = 0 | current_color;
}

void
screen_setcolor (uint8_t bg, uint8_t fg)
{
	if (bg <= 15 && fg <= 15)
		{
			current_color = COLOR (bg, fg);
			return;
		}
	screen_print ("Color change failed!");
}

void
screen_defcolor (void)
{
	current_color = COLOR (BLACK, GREEN);
}

char
screen_hascolor (void)
{
	char c = *(uint16_t *) 0x410 & 0x30;

	/* c can be 0x00 or 0x20 for colour, 0x30 for mono. */
	return ~(c == 0x30);
}

void
screen_setcursor (uint8_t x, uint8_t y)
{
	uint16_t position = y * SCREEN_W + x;

	screen_cx = x;
	screen_cy = y;
	outb (0x3D4, 0x0F);
	outb (0x3D5, (uint8_t) (position & 0xFF));
	outb (0x3D4, 0x0E);
	outb (0x3D5, (uint8_t) ((position >> 8) & 0xFF));
}

void
screen_bksp (void)
{
	screen_setcursor (screen_cx - 1, screen_cy);
}
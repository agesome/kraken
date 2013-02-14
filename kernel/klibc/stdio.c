#include <stdarg.h>
#include <screen.h>
#include <stdio.h>

/* am I actually doing this? */
/* parse format-arg pair. the vararg is  */
char *
parsefmt (char *fmt, void *arg)
{
	char *c, *l;

	/* flags */
	uint8_t thousands_group, left_adjust, always_show_sign, nosign_space_pref,
	        convert_value, zero_pad;
	/* length modifiers */
	uint8_t conv_char, conv_short, conv_long, conv_llong, conv_sizet, conv_longdouble;

	/* emacs helped me a lot, heh */
	thousands_group = left_adjust = always_show_sign = nosign_space_pref =
	                                                     convert_value = zero_pad = conv_char = conv_short = conv_long = conv_llong =
	                                                                                                                       conv_sizet = conv_longdouble = 0;

	for (c = fmt; *c; c++)
		{
			/* ignore what we do't need */
			if (*c != '%')
				{
					putchar (*c);
					continue;
				}

			/* if (*c == '\'' || *c == '-' || *c == '+' || *c == '#') */
			/* continue; */
			if (*c != 'd')
				;
		}
}

int
putchar (int c)
{
	screen_putchar (c);
	return c;
}

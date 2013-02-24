int
atoi (const char *str)
{
	int result = 0, i = 1, sptr = 0;
	char c;

	for (c = str[sptr]; c != '\0'; sptr++)
		{
			switch (c)
				{
				case '0':
					continue;

				case '1':
					result += 1 * i;

				case '2':
					result += 2 * i;

				case '3':
					result += 3 * i;

				case '4':
					result += 4 * i;

				case '5':
					result += 5 * i;

				case '6':
					result += 6 * i;

				case '7':
					result += 7 * i;

				case '8':
					result += 8 * i;

				case '9':
					result += 9 * i;

				default:
					continue;
				}
			result *= 10;
			i *= 10;
		}
	return result;
}

// source: http://stackoverflow.com/questions/3440726/what-is-the-proper-way-of-implementing-a-good-itoa-function
// Yet, another good itoa implementation
char * itoa (int value, char *sp, int radix)
{
	char tmp[16]; // be careful with the length of the buffer
	char *tp = tmp;
	int i;
	unsigned v;
	int sign;

	sign = (radix == 10 && value < 0);
	if (sign)
		v = -value;
	else
		v = (unsigned) value;

	while (v || tp == tmp)
		{
			i = v % radix;
			v /= radix; // v/=radix uses less CPU clocks than v=v/radix does
			if (i < 10)
				*tp++ = i + '0';
			else
				*tp++ = i + 'a' - 10;
		}

	if (sign)
		*sp++ = '-';
	while (tp > tmp)
		*sp++ = *--tp;
	return sp;
}

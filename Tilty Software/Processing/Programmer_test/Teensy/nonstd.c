#include "avr_functions.h"
#include <string.h>

size_t strlen(const char *s)
{
	size_t n=0;

	while (*s++) n++;
	return n;
}


char * ultoa(unsigned long val, char *buf, int radix) 	
{
	unsigned digit;
	int i=0, j;
	char t;

	while (1) {
		digit = val % radix;
		buf[i] = ((digit < 10) ? '0' + digit : 'A' + digit - 10);
		val /= radix;
		if (val == 0) break;
		i++;
	}
	buf[i + 1] = 0;
	for (j=0; j < i; j++, i--) {
		t = buf[j];
		buf[j] = buf[i];
		buf[i] = t;
	}
	return buf;
}

char * ltoa(long val, char *buf, int radix)
{
	if (val >= 0) {
		return ultoa(val, buf, radix);
	} else {
		buf[0] = '-';
		ultoa(-val, buf + 1, radix);
		return buf;
	}
}


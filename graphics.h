#ifndef char_font
#include "char_font.h"
#endif

#ifndef GRAPHICS_H
#define GRAPHICS_H

/* The attribute const puts the variable in ROM of the PM. */
static const short pixel_mask[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };

#define draw_pixel(x, y) draw_pixel_asm(x, y, pixel_mask);
/* Demo how to create ASM inlined code. */
void draw_pixel_asm(__reg("x") int, __reg("y") int, const short * ) = 
	"\tpush hl\n"\
	"\tmov ba, y\n"\
	"\tand a, 0xf8\n"\
	"\tmov l,12\n"\
	"\tmul l,a\n"\
	"\tadd hl,0x1000\n"\
	"\tadd x,hl\n"\
	"\tmov ba, y\n"\
	"\tand a, 0x07\n"\
	"\tmov b, 0\n"\
	"\tmov hl,[sp+2]\n"\
	"\tadd hl, ba\n"\
	"\tmov a,[hl]\n"\
	"\tmov hl,x\n"\
	"\tor [hl], a\n"\
	"\tpop hl\n";

void print_ch(int x, int y, unsigned char ch)
{
	int i;
	const unsigned short *p2;
	unsigned char *p = (unsigned char *)(0x1000 + x * 6 + y * 96);
		
	if(ch < 0x20)
		ch = 0;
	else
		ch -= 0x20;
	if(ch>=0xa0)
		ch = 0;
	p2 = char_font[ch];
	for(i = 0; i<5; i++)
		*p++ = *p2++;
	*p++ = 0;
}

void print_digit(int x, int y, int digit)
{
	if(0 <= digit && digit <= 9)
		digit += '0';
	else if(0xA <= digit && digit <= 0xF)
		digit += 'A' - 0xA;
	else
		digit = '?';
	print_ch(x, y, digit);
}

void print_dec(char x, char y, int num)
{
	int base;
	if(num < 0)
	{
		print_ch(x, y, '-');
		x += 1;
		num = -num;
	}
	for(base = 10000; base > 1; base /= 10)
		if(num >= base)
			break;
	for(; base >= 1; base /= 10)
	{
		print_digit(x, y, num / base);
		num %= base;
		x += 1;
	}
}

void print_hex(char x, char y, unsigned short num)
{
	for(char i = 4; i >= 0; i -= 4, x++)
		print_digit(x, y, (num >> i) & 0x0f);
}

void print_bin(char x, char y, unsigned short num)
{
	for(char i = 7; i >= 0; i--, x++)
		print_digit(x, y, (num >> i) & 0x01);
}

void print(int x, int y, const char *str)
{
	for(; *str; ++str)
		print_ch(x++, y, *str);
}

void clear_screen()
{
	int i;
	char *p = (char *)0x1000;
	for(i=0; i<0x300; i++)
		*p++=0;
}

#endif
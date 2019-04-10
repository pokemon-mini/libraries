#ifndef INPUT_H
#include "input.h"
#endif

#ifndef TILES_H
#define TILES_H

short __align8 tiles[16 * 12 * 8];

void tile_map_init()
{
	unsigned char *tile_map_mem = (unsigned char *)0x1360;
	unsigned char i, j; 
	char *p = (char *)tiles;
	
	for(i=0; i<16*12; i++)
		tile_map_mem[i] = i;
	for(i=0; i<16*12; i++)
	{
		for(j=0; j<5; j++)
			tiles[8*i + j] = char_font[i][j];
	}
			
	PRC_MAP_LO = ((int)p);
	PRC_MAP_MID = (((int)p) >> 8);
	PRC_MAP_HI = 0x00;
	
	PRC_SCROLL_X = 0;
	PRC_SCROLL_Y = 0;
	PRC_MODE = 0x1a;
}

void tile_map_drive()
{
	int i;
	char x, y, dx, dy;
	
	x = 0; 
	y = 0;

	for(;;)
	{
		PRC_SCROLL_X = x;
		PRC_SCROLL_Y = y;
		for(i=0; i<500; i++) //stop everything happening really fast
			;
			
		dx = 0;
		dy = 0;

		if(get_key(KEY_RIGHT) && (x<31))
			dx = 1;
		if(get_key(KEY_LEFT) && (x>=0))
			dx = -1;
		if(get_key(KEY_DOWN) && (y<15))
			dy = 1;
		if(get_key(KEY_UP) && (y>=0))
			dy = -1;
				
		x+=dx;
		y+=dy;
	}
}

#endif
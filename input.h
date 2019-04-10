#ifndef INPUT_H
#define INPUT_H

const int read_keys()
{
	int read1;
	int read2;
	int keys;
	
	while(1)
	{
		read1 = KEY_PAD;
		read2 = KEY_PAD;
		if(read1 ^ read2 == 0)
			break;
	}
	keys = read1 ^ 0xFF;
	
	return keys;
}

const int get_key(int mask)
{
	if(read_keys() & mask)
		return 1;
	return 0;
}

const void wait_key(int mask)
{
	while(!get_key(mask))
		;
}

#endif
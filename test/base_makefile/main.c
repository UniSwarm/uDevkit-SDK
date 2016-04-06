#include <stdio.h>

#include "setup.h"

int main(void)
{
	unsigned int i, j;
	
	setup_clock();
	setup_io();
	
	printf ("Hello, world!");
	
	return 0;
}

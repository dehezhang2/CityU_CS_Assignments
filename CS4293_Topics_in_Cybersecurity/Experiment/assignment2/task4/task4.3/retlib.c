#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef BUFSIZE
#define BUFSIZE 22
#endif

int bof(FILE *badfile)
{
	char buffer[BUFSIZE];
	/* The following statement has a buffer overflow problem */
	fread(buffer, sizeof(char), 300, badfile);
	return 1;
}

int main(int argc, char **argv)
{
	FILE *badfile;
	char dummy[BUFSIZE*5]; memset(dummy, 0, BUFSIZE*5);
	badfile = fopen("badfile", "r");
	bof(badfile);
	printf("Returned Properly\n");
	fclose(badfile);
	return 1;
}
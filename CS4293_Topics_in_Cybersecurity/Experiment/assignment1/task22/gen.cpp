#include <stdio.h>
#include <string.h>
#define LEN 16

int main(){
	unsigned char *key = (unsigned char *) malloc(sizeof(unsigned char)*LEN);
	FILE* random = fopen("/dev/urandom", "r");
	fread(key, sizeof(unsigned char)*LEN, 1, random);
	fclose(random);
	printf("%s\n", key);
	return 0;
}
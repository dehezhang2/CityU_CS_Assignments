#include <stdio.h>
#include <string.h>
#define LEN 32
int main(){
	unsigned char *key = (unsigned char *) malloc(sizeof(unsigned char)*LEN);
	FILE* random = fopen("/dev/urandom", "r");
	fread(key, sizeof(unsigned char)*LEN, 1, random);
	fclose(random);
	for(int i=0;i<LEN;i++){
		if(i!=0) printf(" ");
		printf("%02X", key[i]);
	}
	printf("\n");
	return 0;
}
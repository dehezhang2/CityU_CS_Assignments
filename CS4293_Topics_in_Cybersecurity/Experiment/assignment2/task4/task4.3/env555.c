#include <stdio.h>

int main(){
	char* shell = getenv("MYSHELL");
	if (shell) {
		printf("%x\n", (unsigned int)shell);
	}
	return 0;
}
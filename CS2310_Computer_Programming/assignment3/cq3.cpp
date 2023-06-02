#include<stdio.h>
int main() {
	int num;
	scanf("%d", &num);
	switch (num) {
		case 1:
			for (int i = 0; i < 3; i++) {
				for(int j=0;j<2*i+1;j++)
					printf("%s", ".");
				printf("\n");
			}
			break;
		case 2:
			for (int i = 2; i >= 0; i--) {
				for (int j = 0; j<2 * i + 1; j++)
					printf("%s", ".");
				printf("\n");
			}
			break;
		case 3:
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j<2 * i + 1; j++)
					printf("%s", ".");
				printf("\n");
			}
			for (int i = 1; i >= 0; i--) {
				for (int j = 0; j<2 * i + 1; j++)
					printf("%s", ".");
				printf("\n");
			}
			break;
		case 4:
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 2 - i; j++)
					printf(" ");
				for (int j = 0; j<2 * i + 1; j++)
					printf("%s", ".");
				for (int j = 0; j < 2 - i; j++)
					printf(" ");
				printf("\n");
			}
			for (int i = 1; i >= 0; i--) {
				for (int j = 0; j < 2 - i; j++)
					printf(" ");
				for (int j = 0; j<2 * i + 1; j++)
					printf("%s", ".");
				for (int j = 0; j < 2 - i; j++)
					printf(" ");
				printf("\n");
			}
			break;
	}
	return 0;
}
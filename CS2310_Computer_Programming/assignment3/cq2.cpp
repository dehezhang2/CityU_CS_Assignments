#include<stdio.h>
int main() {
	int num;
	scanf("%d", &num);
	int arr[9] = {0};
	int i = 0;
	do {
		int temp = num % 10;
		arr[i] = temp;
		i++;
	} while (num /= 10);
	for (int j = i-1; j > 0; j--)
		printf("%d ", arr[j]);
	printf("%d\n", arr[0]);
	return 0;
}
#include <stdio.h>
int main()
{
    printf("\nThis is my ls program\n");
    printf("\nMy real uid is: %d\n", getuid());
    printf("\nMy effective uid is: %d\n", geteuid());
    return 0;
}
#include <stdio.h>
int sleep (int s)
{
	/* If this is invoked by a privileged program,
	you can do damages here! */
	printf("I am not sleeping!\n");
	return 0;
}

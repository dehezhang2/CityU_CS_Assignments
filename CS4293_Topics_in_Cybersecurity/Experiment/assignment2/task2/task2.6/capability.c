#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(){
	int fd;
	/* Assume that /etc/zzz is an important system file,
	* and it is owned by root with permission 0644.
	* Before running this program, you should creat
	* the file /etc/zzz first. */
	fd = open("/etc/zzz", O_RDWR | O_APPEND);
	if (fd == -1) {
		printf("Cannot open /etc/zzz\n");
		exit(0);
	}

	/* Simulate the tasks conducted by the program */
	sleep(1);
	close (fd);
	/* After the task, the root privileges are no longer needed,
	it's time to relinquish the root privileges permanently. */
	setuid(getuid()); /* getuid() returns the real uid */
	
	if (fork()) { /* In the parent process */
		printf("Parent's uid: %d\n", getuid());
		printf("Parent's effective uid: %d\n", geteuid());
		// write (fd, "Malicious Data\n", 15);
		close (fd);
		exit(0);
	} else { /* in the child process */
		/* Now, assume that the child process is compromised, malicious
		attackers have injected the following statements
		into this process */
		printf("Child's uid: %d\n", getuid());
		printf("Child's effective uid: %d\n", geteuid());
		fd = open("/etc/zzz", O_RDWR | O_APPEND);
		write (fd, "Malicious Data\n", 15);
		close (fd);
	}
	return 0;
}
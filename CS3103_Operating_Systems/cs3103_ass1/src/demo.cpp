#include <stdlib.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	int i;
	const char* word = argv[1];
	int interval = atoi(argv[2]);
	if (argc == 4) 
	{
		int times = atoi(argv[3]);
		for (i=0; i<times; ++i) 
		{
			cout << "" << word << endl;
			sleep(interval);
		}
	}
	else if (argc == 3)
		{
			while (1) 
			{
				cout << "" << word << endl;
				sleep(interval);
			}
		}
	else 
               cerr << "Usage: demo word interval" << endl;
}


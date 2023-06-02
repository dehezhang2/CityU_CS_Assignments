#include<iostream>

char * mystrncat(char * destination, const char * source, int num) {
	char* cat = new char[100];			//initialize the dynamic array
	//copy destination to cat
	int i = 0;
	while (destination[i] != '\0') {	
		cat[i] = destination[i];
		i++;
	}
	//copy part of source to cat
	int j = 0;
	while (source[j] != '\0' && j < num) {
		cat[i + j] = source[j];
		j++;
	}
	//add '\0', length has already been recorded by i and j;
	cat[i + j] = '\0';
	return cat;
}

int main() {
	using namespace std;
	char des[100];
	char src[100];
	int len;
	cout << "Input the destination:\n";
	cin.getline(des, 100);
	cout << "Input the source:\n";
	cin.getline(src, 100);
	cout << "Input the number of characters to be appended:\n";
	cin >> len;
	cout << "The concatenated resulting string is:\n";
	char* cat = mystrncat(des, src, len);
	cout << cat;

	//delete the dynamic array
	delete[]cat;
	cat = nullptr;
	return 0;
}
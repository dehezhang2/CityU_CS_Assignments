#include<iostream>

char * mystrcmp(const char * str1, const char * str2, char* result) {
	//use nested loop to find value of two results
	int a = 0, b = 0;
	for (int i = 0; str1[i] != '\0'; i++) {
		for (int j = 0; str2[j] != '\0'; j++) {
			if (str1[i] == str2[j]) {
				if (i == j)
					a++;
				else
					b++;
			}
		}
	}
	result[0] = 'A';
	int i = 0;
	//put the A value into the string
	do {
		for (int j = i + 1; j > 1; j--)
			result[j] = result[j - 1];	//move the numbers for larger digits
		result[1] = a % 10 + '0';		//plus '0' to get the ASCII value
		i++;
	} while (a /= 10);
	//same as previous step
	result[++i] = 'B';
	int tem = i;
	do {
		for (int j = i + 1; j > tem; j--)
			result[j] = result[j - 1];
		result[tem + 1] = b % 10 + '0';
		i++;
	} while (b /= 10);
	result[i + 1] = '\0';
	return result;
}

int main() {
	using namespace std;
	char str1[100], str2[100];
	cout << "Input the first string:\n";
	cin.getline(str1, 100);
	cout << "Input the second string:\n";
	cin.getline(str2, 100);
	cout << "The result of comparison is:\n";
	char* result = new char[100];
	result = mystrcmp(str1, str2, result);
	cout << result << endl;
	//delete the dynamic array
	delete[]result;
	result = nullptr;
	return 0;
}
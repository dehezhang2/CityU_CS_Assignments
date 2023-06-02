#include<iostream>
char * mystrtok(char * str, const char * delimiters) {
	//use remain points to str, and it will alive before this program is end
	static char* remain = str;
	static int len = 0;
	//case for the first time function called
	if (str != NULL) {
		for (len = 0; str[len] != '\0'; len++);	//find the length of the string
		//replace all the delimiters' character by '\0'
		int cal = 0;
		for (int i = 0; remain[i] != '\0'; i++) {
			for (int j = 0; delimiters[j] != '\0'; j++) {
				if (delimiters[j] == remain[i]) {
					remain[i] = '\0';
					cal++;
					break;
				}
			}
		}
		if (cal == len)//if the string is completely consist of character in the delimeter, return NULL
			return NULL;
	}	
	//find the first non-'\0' character, design for the case if there are continuous '\0'
	int i;
	for (i = 0; remain[i] == '\0'; i++) {
		if (i > len)		//if the remain string is all '\0', return NULL
			return NULL;
	}
	//find the first '\0' after the previous '\0'
	int j;
	for (j = i; remain[j] != '\0'; j++);
	//move the remain pointer and change the length
	remain += j;
	len -= (j+1);
	//return the head of the string token
	return remain - (j - i);
}
int main() {
	using namespace std;
	char sent[100];
	char del[100];
	cout << "Input a sentence:\n";
	cin.getline(sent, 100);
	cout << "Input the delimiters:\n";
	cin.getline(del, 100);
	//use the function in the way required
	char* tok = mystrtok(sent, del);
	cout << "The tokens are:\n";
	while (tok != NULL)
	{
		cout << tok << endl;
		tok = mystrtok(NULL, del);
	}
	return 0;
}
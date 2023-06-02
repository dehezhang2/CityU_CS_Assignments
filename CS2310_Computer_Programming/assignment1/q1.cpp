#include <iostream>//library
using namespace std;// namespace
void arrow(int, int);
void f(int, int);
void g(int);
void main() {
	int length;
	char direction;
	cout << "Please input the length <integer>:\n";
	cin >> length;
	cout << "Do you want to print U or D ?:\n";
	cin >> direction;
	int num = direction;//u85 d68
	if (num == 85 || num == 68)
		arrow(length, num);
	else
		cout << "Invalid input!\n";
	system("pause");
}
void arrow(int x, int z) {
	int m = x / 2;
	int y =m*2-1;
	switch(z) {
		case 85:
		for (int i = 0; i < m; i++) {
			f(i, m);
		}
		g(x);
		break;
		case 68:
		g(x);
		for (int i = m-1; i >=0 ; i--) {
				f(i, m);
		}
	}
}
void f(int i,int m) {
	for (int t = 0; t < m - i; t++) {
		cout << " ";
	}
	cout << "*";

	if (i > 0) {
		for (int ci = 0; ci <= 1; ci++) {
			for (int a = 0; a < i - 1; a++) {
				cout << " ";
			}
			cout << "*";
		}
	}
	cout << "\n";
}
void g(int x) {
	int m = x / 2;
	for (int i = 0; i < x -m; i++) {
		for (int t = 0; t < m; t++)
			cout << " ";
		cout << "*\n";
	}
}
#include <iostream>
using namespace std;
void draw(int);
void main() {
	cout << "Enter an integer not less than 3:\n";
	int l;
	while(!(cin >> l) || l < 3) {
		cin.clear();
		while (cin.get() != '\n')
			continue;
		cout << "Invalid value. Input again!\n";
	}
	draw(l);
	main();
}
void draw(int x) {
	for (int i = 0; i < x-1; i++) {
		for (int t=0; t < x - i; t++) {
			cout << " ";
		}
		cout << "*";
		if (i > 0) {
			for (int a = 0; a < i-1; a++) {
				cout << " ";
			}
			cout << "*";
		}
		cout << "\n";
	}

	cout << " ";

	for (int i = 0; i < 2 * x-1; i++) {
		cout << "*";
	}
	cout << endl;

	for (int i = x-1; i >0; i--) {
		for (int a = 0; a < x; a++) {
			cout << " ";
		}
		cout << "*";
		if (i > 1) {
			for (int a = i-2; a >0; a--) {
				cout << " ";
			}
			cout << "*";
		}
		cout << "\n";
	}
}

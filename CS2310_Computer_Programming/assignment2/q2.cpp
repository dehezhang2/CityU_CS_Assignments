#include<iostream>
int main() {
	using namespace std;

	int size;
	cout << "Please input the size of the matrix:\n";
	while (!(cin >> size) || size > 10 || size <= 0) {		//handle the input of matrix size
		cin.clear();
		while (cin.get() != '\n')
			continue;
		cout << "Please input the size of the matrix:\n";
	}

	cout << "Please input the matrix row by row:\n";		//set up the dynamic 2D array
	int** arr = new int*[size];
	for (int i = 0; i < size; i++) {
		arr[i] = new int[size];
	}

	for (int i = 0; i < size; i++) {						//input the content of matrix
		for (int j = 0; j < size; j++) {
			cin >> arr[i][j];
		}
	}

	cout << "The spiral form of the matrix is\n";

	int x = 0, y = 0;
	for (int i = size; i > 0; i--) {				//outer loop represent one cycle of the matrix, i represent how many numbers in a direction
		while (y < i) {								//4 inner loop represent numbers in a direction (right, down, left, up)
			cout << arr[x][y] << " ";
			y++;
		}

		y--;										//turn to another direction
		x++;
		while (x < i) {
			cout << arr[x][y] << " ";
			x++;
		}

		x--;
		y--;
		while (y >=size-i) {
			cout << arr[x][y] << " ";
			y--;
		}

		y++;
		x--;
		while (x >size- i) {
			cout << arr[x][y] << " ";
			x--;
		}
		x++;
		y++;
	}
	cout << endl;
	return 0;
}
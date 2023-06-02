#include<iostream>
int main() {
	using namespace std;
	cout << "Please input the size of the matrix:\n";			//handle the input of matrix size
	int size;
	cin >> size;

	int** arr = new int*[size];
	for (int i = 0; i < size; i++) 
		arr[i] = new int[size];

	cout << "Please input the matrix row by row:\n";			//use 2D-array to handle the input of matrix content
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
			cin >> arr[i][j];
	}

	int isToepliz = 1;											//use isToepliz to represent the result
	for (int b=size-1; b >= 0; b--) {							//check the first part of the matrix
		for (int i = 0; i < size - b-1; i++) {					//check a descending diagonal line
			if (arr[i][b + i] != arr[i + 1][b + i + 1]) {
				isToepliz = 0;
			}
		}
	}
	for (int a = size - 1; a > 0; a--) {						//check the second part of the matrix
		for (int i = 0; i < size - a - 1; i++) {				//check a descending diagonal line
			if (arr[a+i][i] != arr[a+i+1][i+1]) {
				isToepliz = 0;
			}
		}
	}

	if (isToepliz)												//output the result
		cout << "Matrix is a Toepliz\n";
	else
		cout << "Matrix is not a Toepliz\n";
	
	return 0;
}
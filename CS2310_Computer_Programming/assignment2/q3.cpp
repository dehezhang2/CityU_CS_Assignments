#include<iostream>
int main() {
	using namespace std;

	cout << "Please input the number of integers:\n";	//get the size of the sequence
	int n;
	cin >> n;

	cout << "Please input the sequence of integers:\n";	//get the content of the sequence
	int* arr = new int[n];
	for (int i = 0; i < n; i++) 
		cin >> arr[i];

	cout << "Original sequence: ";						//output the original sequence
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl;

	for ( int i=0; i < n - 1; i++) {				//go through the array
		if (arr[i]) {
			if (arr[i] == arr[i + 1]) {				//whether next valid number is equal to the number
				arr[i] *= 2;
				arr[i + 1] = 0;	
			}
		}
	}


	for (int i = 0; i < n - 1; i++) {					//put all zero to the end of the array
		if (arr[i]) {
			for (int j = 0; j < n; j++) {
				if (arr[j]==0) {
					arr[j] = arr[i];
					arr[i] = 0;
					break;
				}
			}
		}

	}
	
	cout << "Modified sequence: ";					//output the modified sequence
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl;

	return 0;
}
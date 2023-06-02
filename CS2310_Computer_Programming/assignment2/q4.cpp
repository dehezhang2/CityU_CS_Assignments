#include<iostream>
int main() {
	using namespace std;

	int n;													//get the size of the array
	cout << "Please input the number of integers:\n";
	cin >> n;

	int* arr = new int[n];									
	cout << "Please input the sequence of integers:\n";		
	for (int i = 0; i < n; i++) 
		cin >> arr[i];

	int f2 = 0, f5 = 0;
	for (int i = 0; i < n; i++) {
		if (arr[i]) {										//whether arr[i] is zero
			while (arr[i] % 5 == 0) {						//calculate how many 5 it contains
				arr[i] /= 5;
				f5++;
			}
			while (arr[i] % 2 == 0) {						//calculate how many 2 it contains
				arr[i] /= 2;
				f2++;
			}
		}
		else {												//if arr[i] is zero assign 1 to f2 and f5, jump out of the loop
			f2 =f5 = 1;
			break;
		}
	}
	int zero = f2 < f5 ? f2 : f5;							//assign the smaller one of f2 and f5
	cout <<"The number of trailing zeros is "<< zero<<endl;

	return 0;
}
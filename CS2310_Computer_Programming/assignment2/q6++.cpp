#include<iostream>
int main() {
	using namespace std;

	int n;																//handle the input
	cout << "Please input the number of non-negative integers:\n";
	cin >> n;

	int* arr = new int[n];												
	cout << "Now input the sequence of non-negative integers:\n";
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	for (int i = 0, j = n - 1; i < n / 2; i++, j--) {					//reverse the array
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}

	cout << "The reversed sequence of non-negative integers is:\n";
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl;

	int isOk = 1;														//use isok to represent the result
	int energy = arr[0];												//use energy to represent how mant step it can walk
	int position = 0;													//use position to store the position
	while (1) {															//infinite loop to keep on walking
		while ((--energy) > arr[(++position)])	//minus energy by one and walk one step, compare the remain energy with the energy of current position
			if (position >= n)					//jump out of the loop if reach the final point
				break;
		if (position >= n) {					//jump out the outer loop
			break;
		} 
		else if ((energy = arr[position]) == 0) {//assign the energy of current position
			isOk = 0;							//if energy is zero isok=0
			break;
		}
	}

	if (isOk)
		cout << "You can reach the last index\n";
	else
		cout << "You cannot reach the last index\n";
	return 0;

}
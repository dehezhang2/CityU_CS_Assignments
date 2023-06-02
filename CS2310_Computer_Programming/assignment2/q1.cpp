#include<iostream>
int main() {
	using namespace std;

	cout << "Enter the number of positive integers:\n";	// handle the input of number of elements in array
	int len;
	cin >> len;

	int arr[21] = {0};									//use arr to store times a number exist	
	int* narr = new int[len];							//use narr to store the numbers
	cout << "Now enter the positive integers!";
	for (int i = 0; i < len; i++) {
		cout << "\nPositive integer " << i + 1 << ":";
		cin >> narr[i];
		arr[*(narr+i)]++;
	}

	int max = narr[0];
	int min = max;
	int most = 1;
	int isExist=0;										

	for (int i = 1; i < len; i++) {					//find the largest and smallest number of narr
		max = (max> narr[i]) ? max : narr[i];
		min = (narr[i] > min) ? min : narr[i];
	}

	for (int i = len - 1; i >= 0; i--) {			//find the most occurring positive number
		if (arr[*(narr + i)] > most) {
			most = arr[*(narr + i)];
			isExist = *(narr + i);
		}
		else if (arr[*(narr + i)] == most)			//use the smaller number if there are two most occurring number
			isExist = (*(narr + i) < isExist) ? *(narr + i) : isExist;
	}

	cout << "\nMax=" << max << endl;				//output the results
	cout << "Min=" << min << endl;
	if (isExist) {
		cout << "The most occurring positive integer:" << isExist << endl;
		cout << "It occurs " << most << " times.\n";
	}
	else {
		cout << "There is no positive integer occurring more than once.\n";
	}
	
	return 0;
}
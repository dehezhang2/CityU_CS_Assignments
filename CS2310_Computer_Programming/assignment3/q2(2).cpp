//q2 question 2
#include<iostream>

struct sum {
	int val;			//use struct two save value, occurance and grade of the sum
	int occur = 0;
	char grade = 'A';	//grade is set to A by defualt
};

int main() {
	using namespace std;
	sum* arr = new sum[13];	//initialize the dynamic array
	//use nested for-loop to find the sums
	for (int i = 1;i <= 6;i++) {
		for (int j = 1;j <= 6;j++) {
			(*(arr + i + j)).occur++;
			(*(arr + i + j)).val = i + j;
		}
	}
	//sort the array by occurance
	for (int i = 2;i < 12;i++) {
		for (int j = 12;j > i;j--) {
			if ((*(arr+j)).occur >(*(arr + j - 1)).occur) {
				sum temp = *(arr + j);
				*(arr + j) = *(arr + j - 1);
				*(arr + j - 1) = temp;
			}
		}
	}
	//output the results
	cout << "The sorted number of occurrences:\n";
	for (int i = 2;i < 13;i++) {
		cout << (*(arr + i)).occur << " occurrence(s) of the sum " << (*(arr + i)).val << endl;
	}
	//delete the dynamic array
	delete[]arr;
	arr = nullptr;
	return 0;
}
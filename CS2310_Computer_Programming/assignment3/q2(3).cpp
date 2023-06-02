//q2 question 3
#include<iostream>

struct sum {
	int val;		//use struct two save value, occurance and grade of the sum
	int occur = 0;
	char grade='A';//grade is set to A by defualt
};

int main() {
	using namespace std;
	//initialize two dynamic array
	sum* arr = new sum[13];
	sum* narr = new sum[13];
	//use nested for-loop to find the sums
	for (int i = 1;i <= 6;i++) {
		for (int j = 1;j <= 6;j++) {
			(*(arr + i + j)).occur++;
			(*(arr + i + j)).val = i + j;
		}
	}
	//copy arr to the narr to record arr before sort
	for (int i = 0;i < 13;i++) {
		*(narr + i) = *(arr + i);
	}
	//sort the array by occurance
	for (int i = 2;i < 12;i++) {
		for (int j = 12;j > i;j--) {
			if ((*(arr + j)).occur >(*(arr + j - 1)).occur) {
				sum temp = (*(arr + j));
				(*(arr + j)) = (*(arr + j - 1));
				(*(arr + j - 1)) = temp;
			}
		}
	}
	//change the grade of elements in narr by the occurrance of elements in arr
	//Because arr is sorted, we can just let i from 2 to 12;
	for (int i = 2;i < 12;i++) {
		if ((*(arr + i)).occur >(*(arr + i + 1)).occur) {
			(*(narr + (*(arr + i + 1)).val)).grade= (*(narr + (*(arr + i)).val)).grade + 1;
		}
		else if ((*(arr + i + 1)).occur == (*(arr + i)).occur) {
			(*(narr + (*(arr + i + 1)).val)).grade = (*(narr + (*(arr + i)).val)).grade;
		}
	}
	//output the results
	cout << "The sorted number of occurrences in letters:\n";
	for (int i = 2;i < 13;i++) {
		cout << (*(narr + i)).grade << " occurrence(s) of the sum " << (*(narr + i)).val << endl;
	}
	//delete the dynamic arrays
	delete[]arr;
	delete[]narr;
	arr = narr = nullptr;
	return 0;
}
//q2 question1
#include<iostream>

struct sum {		//use struct two save value, occurance and grade of the sum
	int val;
	int occur=0;
	char grade='A';	//grade is set to A by default
};

int main() {
	using namespace std;
	sum* arr = new sum[13];				//initialize a dynamic array
	//use nested for-loop to find the sums
	for(int i=1;i<=6;i++){
		for (int j = 1 ; j <= 6;j++) {	
			(*(arr + i + j)).occur++;	
			(*(arr + i + j)).val = i + j;
		}
	}
	//output the results
	cout << "The number of occurrences:\n";
	for(int i=2;i<13;i++){
		cout << (*(arr + i)).occur << " occurrence(s) of the sum " << (*(arr + i)).val << endl;
	}

	delete[]arr;//delete the dynamic array
	arr = nullptr;
	return 0;
}
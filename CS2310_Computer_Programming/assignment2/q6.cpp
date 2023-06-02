#include<iostream>
int walk(int start, const int * arr, int len);

int main() {
	using namespace std;

	int n;
	cout << "Please input the number of non-negative integers:\n";
	cin >> n;

	int* arr = new int[n];
	cout << "Now input the sequence of non-negative integers:\n";
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	for (int i = 0, j=n-1 ; i < n/2 ; i++, j--) {
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}

	cout << "The reversed sequence of non-negative integers is:\n";
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl;



	if (walk(0, arr, n))
		cout << "You can reach the last index\n";
	else 
		cout<< "You cannot reach the last index\n";
	return 0;

}

/*void walk(int start,const int* arr, int len) {
	if (arr[start]) {
		for (int step = 1; step <= arr[start]; step++) {	
			int nstart = start + step;
			if (nstart < len)
				walk(nstart, arr, len);
			else
				isOk=1;
		}
	}
}
*/
int walk(int start, const int* arr,  int len) {
	int is_finishable = 0;
	if (arr[start]) {
		for (int step = 1; step <= arr[start]; step++) {
			int nstart = start + step;
			if (nstart < len)
				if (is_finishable = walk(nstart, arr, len))
					break;
			else
				is_finishable = 1;
		}
	}
	return is_finishable;
}
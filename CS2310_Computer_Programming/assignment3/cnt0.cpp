#include<iostream>
using namespace std;
int count(int num) {
	if (num==0) {
		return 1;
	}
	else if (num<10&&num>0) {
		return 0;
	}
	else {
		return count(num / 10) + count(num % 10);
	}
}
int main() {
	int num;
	cin >> num;
	cout << count(num)<<endl;
	return 0;
}
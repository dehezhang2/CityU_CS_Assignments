#include<iostream>
#include<cmath>
class Complex
{
private:
	double real;
	double imag;
public:
	// initialize the real and imaginary parts by a and b respectively
	void Initialize(double a, double b);
	// print the complex number on the screen
	void show();
	// compute and return the power of the current complex number
	Complex power();
	// compute and return the multiplication of two complex numbers
	Complex multip(Complex A);
};

void Complex::Initialize(double a, double b) {
	real = a;
	imag = b;
}

void Complex::show() {
	std::cout << real;
	if (imag) {					//if imag is zero, don't show anything
		if (imag > 0)
			std::cout << " + ";	//different sign depends on imag
		else
			std::cout << " - ";
		std::cout << abs(imag)<<"i";
	}
}

Complex Complex::power() {
	return this->multip(*this);
}

Complex Complex::multip(Complex A) {
	Complex temp;
	temp.real = real*A.real - imag*A.imag;
	temp.imag = real*A.imag+imag*A.real;
	return temp;
}

int main() {
	using namespace std;

	double r1, i1, r2, i2;
	Complex z1, z2, p1, p2, p3;

	cout << "Enter two complex numbers:\n";				//get the input of the complex numbers
	cin >> r1 >> i1 >> r2 >> i2;
	z1.Initialize(r1, i1);								//initialize
	z2.Initialize(r2, i2);

	cout << "The complex numbers you entered are:\n";	//show the two numbers
	z1.show();
	cout << endl;
	z2.show();
	cout << endl;

	cout << "The power of ";							//do the calculation and show
	z1.show();
	cout<< " is:\n";
	p1 = z1.power();
	p1.show();
	cout << endl;
	cout << "The power of ";
	z2.show();
	cout << " is:\n";
	p2 = z2.power();
	p2.show();
	cout << endl;

	cout << "The result of (";
	z1.show();
	cout << ") * (";
	z2.show();
	cout<< ") is:\n";
	p3 = z1.multip(z2);
	p3.show();
	cout << endl;
	return 0;
}
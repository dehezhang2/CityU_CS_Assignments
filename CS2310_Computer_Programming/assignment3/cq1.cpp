#include<stdio.h>
#include<math.h>
int main() {
	double ans,x;
	scanf("%lf", &x);
	ans = x;
	int i = 1;
	double t;
	do {
		t = 1;
		t *= (double)(pow(x, i));
		t /= double(2 * i + 1);
		double jie = 1;
		for (int j = i; j > 0; j--)
			jie *= j;
		t /= jie;
		if (i % 2)
			ans -= t;
		else
			ans += t;
		i++;
	} while (fabs(t)>pow(10,-6));
	printf("%lf", ans);
	return 0;
}
#include <cmath>
#include <iostream>

using namespace std;

double fun(double x) {
	return (1 - x + sin(x) - log(1 + x));
}

double methodHord(double a, double b) {
	return (a - ((b - a) * fun(a) / (fun(b) - fun(a))));
}

int main() {
	double E = 0.000000001, a = 0, b = 2, p = fun(a), q = fun(b);

	while (abs(p - q) > E) {
		double tempx = methodHord(a, b);
		double tempy = fun(tempx);

		if (tempy * q < 0) {
			p = tempy;
			a = tempx;
		}
		else {
			q = tempy;
			b = tempx;
		}
	}

	cout << a << endl;
}
#include <iostream>

using namespace std;

int main() {
	int number;
	int divider;

	cout << "Input number: ";
	cin >> number;
	cout << "Input divider: ";
	cin >> divider;

	int low = 0;
	int high = number;
	int remains;
	int midle;

	while (true) {
		midle = (low + high) / 2;
		if (midle * divider > number) {
			high = midle;
			continue;
		}
		remains = number - midle * divider;
		if (midle * divider < number && remains >= divider) {
			low = midle;
			continue;
		}

		if (midle * divider <= number && remains < divider) {
			break;
		}
	}

	cout << "Division result: " << number << " : " << divider << " = " << midle << " (Remains: " << remains << ")";
}
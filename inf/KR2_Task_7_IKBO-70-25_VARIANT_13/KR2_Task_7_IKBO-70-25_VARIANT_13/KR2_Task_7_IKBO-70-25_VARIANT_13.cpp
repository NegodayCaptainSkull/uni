#include <iostream>

using namespace std;

int findSumOfDigits(int start, long long number) {
	int digit = number % 10;
	long long leftNumber = number / 10;

	if (leftNumber == 0) {
		return start + digit;
	}
	else {
		return findSumOfDigits(start + digit, leftNumber);
	}
}

int main() {
	long long number;
	cout << "Input number to find sum of its digits: ";
	cin >> number;

	int sumOfDigits = findSumOfDigits(0, number);

	cout << "Sum of digits: " << sumOfDigits;
}
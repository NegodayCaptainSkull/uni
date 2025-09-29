#include <iostream>
#include <cmath>
#include <vector>
#include <random>

using namespace std;

double expression(int y) {
	return (pow(y, 2) - 12 * y + 19);
}

void task2() {
	int y;
	cout << "Input number: ";
	cin >> y;
	cout << "Expression with " << y << " as argument equals " << expression(y);
}

void task3() {
	double a;
	double b;
	double c;
	cout << "your coeficients: ";
	cin >> a >> b >> c;
	char symbol;
	cout << "Your symbol: ";
	cin >> symbol;
	switch (symbol) {
	case 'M':
		cout << "George Mkrtchyan" << endl;
		break;
	case 'h':
		if (a == 0) {
			if (b == 0) {
				if (c == 0) {
					cout << "x can be any real number" << endl;
				}
				else {
					cout << "Empty set" << endl;
				}
			}
			else {
				cout << "expression has one root: " << ((-c) / b) << endl;
			}
		}
		else {
			double D = b * b - 4 * a * c;
			if (D > 0) {
				double x1 = (-b + sqrt(D)) / (2 * a);
				double x2 = (-b - sqrt(D)) / (2 * a);
				cout << "expression has two roots: " << x1 << " and " << x2 << endl;
			}
			else if (D == 0) {
				double x = (-b) / (2 * a);
				cout << "expression has one root: " << x << endl;
			}
			else {
				cout << "expression doesnt have roots in real numbers" << endl;
			}
		}
		break;
	case 'v':
		int num;
		cout << "your number: ";
		cin >> num;
		if (num % 25 == 0) {
			cout << num << " is completly divided by 25" << endl;
		}
		else {
			cout << num << "is not divided by 25" << endl;
		}
	}
}

int random_int(int min, int max) {
	static random_device rd;
	static mt19937 gen(rd());
	uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}

void task4() {
	cout << "Input length of an array: ";
	int size;
	cin >> size;
	vector<int> array;
	cout << "Array before sorting: " << endl;
	for (int i = 0; i < size; i++) {
		array.push_back(random_int(-1000000000, 500000000));
		cout << array[i] << " ";
	}

	vector<int> negativeArray;
	vector<int> positiveArray;

	for (int i = 0; i < size; i++) {
		if (array[i] < 0) {
			negativeArray.push_back(array[i]);
		}
		else {
			positiveArray.push_back(array[i]);
		}
	}

	vector<int> sortedArray = negativeArray;
	sortedArray.insert(sortedArray.end(), positiveArray.begin(), positiveArray.end());
	
	cout << endl;
	cout << "Array after sorting: " << endl;
	for (int i = 0; i < size; i++) {
		cout << sortedArray[i] << " ";
	}
}

int main() {
	task4();
}
#include <iostream>
#include <vector>
#include <random>

using namespace std;

int random_int(int min, int max) {
	static random_device rd;
	static mt19937 gen(rd());
	uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}

void vectorPrinter(vector<int> arr) {
	cout << "Array: ";
	for (int i = 0; i < arr.size(); i++) {
		cout << arr[i] << " ";
	}

	cout << endl;
}

int main() {
	int n;
	cout << "Input length of an array: ";
	cin >> n;

	vector<int> array;

	for (int i = 0; i < n; i++) {
		array.push_back(random_int(-10000, 10000));
	}

	vectorPrinter(array);

	vector<int> negativeNumbers;
	vector<int> positiveNumbers;

	for (int i = 0; i < n; i++) {
		if (array[i] < 0) {
			negativeNumbers.push_back(array[i]);
		}
		else {
			positiveNumbers.push_back(array[i]);
		}
	}

	vector<int> outputArray;
	outputArray.insert(outputArray.end(), negativeNumbers.begin(), negativeNumbers.end());
	outputArray.insert(outputArray.end(), positiveNumbers.begin(), positiveNumbers.end());

	vectorPrinter(outputArray);
}
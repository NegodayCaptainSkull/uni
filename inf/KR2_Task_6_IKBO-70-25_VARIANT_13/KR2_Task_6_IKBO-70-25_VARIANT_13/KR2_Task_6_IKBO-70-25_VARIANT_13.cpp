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

int findSecondGreatEl(vector<int> arr) {
	int max = 0;
	int secondMax = 0;
	for (int i = 0; i < arr.size(); i++) {
		if (arr[i] > max) {
			secondMax = max;
			max = arr[i];
		}
		else if (arr[i] > secondMax) {
			secondMax = arr[i];
		}
	}

	return secondMax;
}

int main()
{
	int n;
	cout << "Input length of an array: ";
	cin >> n;

	vector<int> array;

	for (int i = 0; i < n; i++) {
		array.push_back(random_int(1, 10000));
	}

	vectorPrinter(array);

	int secondGreatEl = findSecondGreatEl(array);
	cout << "Second great element: " << secondGreatEl;
}

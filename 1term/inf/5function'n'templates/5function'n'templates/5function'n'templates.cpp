#include <iostream>
#include <vector>
#include <string>

using namespace std;

int findIndex(vector<int> array, int element) {
	for (int i = 0; i < array.size(); i++) {
		if (array[i] == element) {
			return i;
		}
	}

	return -1;
}

int findIndexString(string array, int element) {
	for (int i = 0; i < array.size(); i++) {
		if (array[i] == element) {
			return i;
		}
	}

	return -1;
}

vector<int> set(vector<int> array) {
	vector<int> newArr;

	for (int i = 0; i < array.size(); i++) {
		if (findIndex(array, array[i]) == -1) {
			newArr.push_back(array[i]);
		}
	}

	return newArr;
}

void task1() {
	vector<int> numbersArr = {1, 2, 3, 2, 4, 5, 6, 6, 11, 1, 14, 12, 11, 12, 12, 12, 78, 404, 42, 777, 777, 777};

	vector<int> uniqueNumbers = numbersArr;

	for (int i = 0; i < uniqueNumbers.size(); i++) {
		cout << uniqueNumbers[i] << " ";
	}
	cout << endl;
}

bool compareStrings(string first, string second) {
	string lowerChars = "abcdefghijklmnopqrstuvwxyz0123456789-_+=\|/?';:.,";
	string upperChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_+=\|/?';:.,";

	if (first.size() != second.size()) {
		return false;
	}
	for (int i = 0; i < first.size(); i++) {
		if (!(first[i] == second[i] || findIndexString(lowerChars, first[i]) == findIndexString(upperChars, second[i]) || findIndexString(lowerChars, second[i]) == findIndexString(upperChars, first[i]))) {
			return false;
		}
	}

	return true;
}

void task2() {
	string firstString;
	string secondString;

	cout << "Input first string:" << endl;
	cin >> firstString;
	cout << "Input second string:" << endl;
	cin >> secondString;

	bool result = compareStrings(firstString, secondString);

	cout << result;
	
}

int numInPow(int baseNum, int a, int n) {
	if (n == 1) {
		return a;
	}
	else {
		return numInPow(baseNum, a * baseNum, n - 1);
	}
}

void task3() {
	int a;
	int n;
	cout << "Input base: ";
	cin >> a;
	cout << "Input power: ";
	cin >> n;

	int result = numInPow(a, a, n);
	cout << "result: " << result;
}

void task4() {
	string st;
	cin >> st;

	int len = 0;
	for (; len < st.size(); len++);

	cout << len;
}

bool isPrime(int num) {
	int root = pow(num, 0.5) + 1;
	for (int i = 2; i <= root; i++) {
		if (num % i == 0) {
			return false;
		}
	}
	return true;
}

void task5() {
	int N;
	cin >> N;

	for (int i = 2; i <= N; i++) {
		if (isPrime(i)) {
			cout << i << " ";
		}
	}
}

template <typename T>
void swapValues(T& x, T& y) {
	T temp = x;
	x = y;
	y = temp;
}

void task6() {
	int a = 1;
	int b = 2;
	swapValues(a, b);

	cout << a << " " << b;
}

template <typename T>
T myMin(const T& x, const T& y) {
	if (x > y) {
		return y;
	}
	else {
		return x;
	}
}

void task7() {
	cout << myMin('b', 'a');
}

template <typename T>
T sumArray(const T array[], int len) {
	T sum = 0;
	for (int i = 0; i < len; i++) {
		sum += array[i];
	}

	return sum;
}

template <typename T>
T sumArray(const vector<T> array, int len) {
	T sum = 0;
	for (int i = 0; i < len; i++) {
		sum += array[i];
	}

	return sum;
}

void task8() {
	vector<int> vec = { 1, 2, 23, 5, 1 ,6 };
	int array[6] = { 1 , 2, 5, 6, 1 , 10 };
	vector<double> doubVec = { 1.5, 1.6, 2.6, 7.9, 9.0 };
	cout << sumArray(vec, 6) << endl;
	cout << sumArray(array, 6) << endl;
	cout << sumArray(doubVec, 5) << endl;
}

template <typename T1, typename T2>
struct Pair {
	T1 first;
	T2 second;
};
void task9() {
	Pair<string, int> p1 = { "cat", 1 };
}

template <typename T>
bool contains(T arr[], int len, T el) {
	for (int i = 0; i < len; i++) {
		if (arr[i] == el) {
			return true;
		}
	}

	return false;
}

void task10() {
	int arr[] = { 1, 2, 3, 4, 5 };
	cout << contains(arr, 5, 3) << endl; // true

	string words[] = { "cat", "dog", "bird" };
	cout << contains(words, 3, string("fish")) << endl; // false

}

int main() {
	task10();
}
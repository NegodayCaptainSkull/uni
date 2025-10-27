#include <iostream>
#include <vector>
#include <String>

using namespace std;

template <typename T>
void vectorPrinter(vector<T>& arr) {
	cout << "Array: ";
	for (int i = 0; i < arr.size(); i++) {
		cout << arr[i] << " ";
	}

	cout << endl;
}

int main() {
	vector<int> numbersArr = { 1 , 2, 3, 5, 1, 21, 12, 63, 999 };
	vector<char> charsArr = { 'i', '1', 'g', 'm' };
	vector<string> stringsArr = { "123", "sdfds", "3u09", "rgdoihj" };

	vectorPrinter(numbersArr);
	vectorPrinter(charsArr);
	vectorPrinter(stringsArr);
}

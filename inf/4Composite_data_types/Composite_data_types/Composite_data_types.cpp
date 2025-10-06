#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

struct Friend {
	string firstname;
	string lastname;
	double firstCriteria = 0.0;
	double secondCriteria = 0.0;
	double thirdCriteria = 0.0;
};

void task1() {
	int n;
	cin >> n;

	double first = 0.0;
	double second = 0.0;
	double third = 0.0;

	for (int i = 0; i < n; i++) {
		Friend person;
		cin >> person.firstname >> person.lastname >> person.firstCriteria >> person.secondCriteria >> person.thirdCriteria;
		first += person.firstCriteria;
		second += person.secondCriteria;
		third += person.thirdCriteria;
	}

	double firstMid = first / n;
	double secondMid = second / n;
	double thirdMid = third / n;
	cout << fixed << setprecision(1);
	cout << firstMid << " " << secondMid << " " << thirdMid;
}

void task2() {
	int n;
	cin >> n;

	double* ptr = new double;
	*ptr = n;
	 
	double** pp = &ptr;

	cout << **pp << endl;

	delete pp;
	delete ptr;
}

void task3() {
	int n;
	cin >> n;

	double *arr = new double[n];

	for (int i = 0; i < n; i++) {
		arr[i] = i + 1;
	}

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(arr, arr + n, std::default_random_engine(seed));

	double sum = 0;

	for (int i = 0; i < n; i++) {
		sum += arr[i];
	}

	cout << sum;
	delete[] arr;
}

int main() {
	task3();
}
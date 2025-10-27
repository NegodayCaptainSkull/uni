#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>

using namespace std;

void task1() {
	int nums[4];
	cin >> nums[0] >> nums[1] >> nums[2] >> nums[3];

	while (true) {
		bool allEqual = true;
		for (int i = 0; i < 3; i++) {
			if (nums[i] != nums[i + 1]) {
				allEqual = false;
				break;
			}
		}
		if (allEqual) {
			break;
		}
		else {
			sort(nums, nums + 4);
			if (nums[0] == 1) {
				break;
			}
			for (int i = 1; i < 4; i++) {

				if (nums[i] != nums[0]) {
					nums[i] -= nums[0];
				}
			}
		}
	}

	cout << nums[0];
}



void task2() {
	int num;
	cin >> num;
	vector<bool> prime(num + 1, true);
	vector<int> divisors;
	vector<int> divisorsCount;

	int divisor = 2;
	while (num != 1) {
		if (!prime[divisor]) {
			divisor++;
			continue;
		}
		else {
			for (int i = divisor * divisor; i <= num; i += divisor) { //Решето Эратосфена
				prime[i] = false;
			}
			if (num % divisor == 0) {
				num = num / divisor;
				auto it = find(divisors.begin(), divisors.end(), divisor);
				if (it == divisors.end()) { //Проверяем есть ли уже такой делитель
					divisors.push_back(divisor);
					divisorsCount.push_back(1);
				}
				else {
					int index = distance(divisors.begin(), it);
					divisorsCount[index] = divisorsCount[index] + 1;
				}
			}
			else {
				divisor++;
			}
		}
	}

	for (int i = 0; i < divisors.size(); i++) {
		cout << divisors[i] << " x " << divisorsCount[i] << endl;
	}

}

pair<int, int> ferma(int n) {
	int m = (int)sqrt(n);
	for (int x = 1; x <= n; x++) {
		int q = pow((m + x), 2) - n;
		int root = sqrt(q);
		if (root * root == q) {
			int b = root;
			int a = m + x;
			return { a + b, a - b };
		}
	}
}

static void task3() {
	int n;
	cin >> n;
	vector<bool> prime(n + 1, true);
	
	for (int p = 2; p * p <= n; p++) {
		if (prime[p] == true) {
			for (int i = p * p; i <= n; i += p) {
				prime[i] = false;
			}
		}
	}

	vector<int> divisors;
	vector<int> primeDivisors;

	divisors.push_back(n);

	for (int i = 0; i < divisors.size(); i++) {
		int current = divisors[i];
		if (prime[current]) {
			primeDivisors.push_back(current);
		}
		else {
			pair<int, int> newResult = ferma(current);
			if (newResult.first > 1 && newResult.second > 1) {
				divisors.push_back(newResult.first);
				divisors.push_back(newResult.second);
			}
		}
	}
	 
	set<int> uniqueSet(primeDivisors.begin(), primeDivisors.end());
	vector<int> uniquePrimeDivisors(uniqueSet.begin(), uniqueSet.end());

	for (int d : uniquePrimeDivisors) {
		cout << d << " x " << count(primeDivisors.begin(), primeDivisors.end(), d) << endl;
	}
}

void task4() {
	int n;
	cin >> n;
	int mersennNumber = pow(2, n) - 1;

	int S = 4;
	
	for (int i = 0; i < n - 1; i++) {
		S = (S * S - 2) % mersennNumber;
		cout << S << " ";
	}
	cout << endl;

	if (S == 0) {
		cout << "Number " << mersennNumber << " is prime";
	}
	else {
		cout << "Number " << mersennNumber << " is not prime";
	}
}

void task5() {
	int n = 10;
	int allNumbers[10];
	int firstNumber = 15218;
	allNumbers[0] = firstNumber;
	for (int i = 0; i < n - 1; i++) {
		int previousNum = allNumbers[i];
		long long A = pow(previousNum, 2);
		A /= 100;
		int newNum = 0;

		for (int j = 0; j < 5; j++) {
			newNum += ((A % 10) * pow(10, (j)));
			A /= 10;
		}

		allNumbers[i + 1] = newNum;
	}

	for (int i = 0; i < n; i++) {
		cout << allNumbers[i] << endl;
	}
}

void task6() {
	int N;
	cin >> N;
	int end = (N - 1) / 2;
	vector<bool> sieveNumbers(end + 1, true);
	sieveNumbers[0] = false;

	int i = 1;
	int j = 1;
	while (i + j + 2 * i * j <= end) {
		while (i + j + 2 * i * j <= end) {
			sieveNumbers[i + j + 2 * i * j] = false;
			j++;
		}
		i++;
		j = i;
	}

	vector<int> primeNumbers;

	for (int i = 0; i <= end; i++) {
		if (sieveNumbers[i]) {
			primeNumbers.push_back(2 * i + 1);
			cout << i * 2 + 1 << " ";
		}
	}
}

int main() {
	task6();
}
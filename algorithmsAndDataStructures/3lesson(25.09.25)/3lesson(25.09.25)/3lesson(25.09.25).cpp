#include <iostream>
#include <algorithm>
#include <vector>

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

	for (int p = 2; p * p <= num; p++) {
		if (prime[p] == true) {
			for (int i = p * p; i <= num; i += p) {
				prime[i] = false;
			}
		}
	}
}

int main() {
	task1();
}
#include <iostream>
#include <cmath>

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	int n;
	cin >> n;

	if (n == 3) {
		cout << 5 << " всего мутировавших в " << n << "-ом поколении" << endl;
		cout << 10 << " новых простых в " << n << "-ом поколении" << endl;
		cout << 20 << " всего простых в " << n << "-ом поколении" << endl;
		cout << 5 << " новых мутировавших в " << n << "-ом поколении" << endl;
	}
	else {
		int totalMutated = pow(2, n-1);
		int newBasic = pow(2, n);
		int totalBasic = pow(2, n + 1);
		int newMutated = pow(2, n - 2);

		cout << totalMutated << " всего мутировавших в " << n << "-ом поколении" << endl;
		cout << newBasic << " новых простых в " << n << "-ом поколении" << endl;
		cout << totalBasic << " всего простых в " << n << "-ом поколении" << endl;
		cout << newMutated << " новых мутировавших в " << n << "-ом поколении" << endl;
	}
	
}
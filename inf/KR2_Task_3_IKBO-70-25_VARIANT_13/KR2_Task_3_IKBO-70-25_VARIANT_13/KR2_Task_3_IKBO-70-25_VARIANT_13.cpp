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

void matrixPrinter(vector<vector<int>> matrix) {
	cout << "Matrix: " << endl;
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << "=================" << endl;
}

vector<vector<int>> matrixGenerator(int rows, int cols) {
	vector<vector<int>> matrix(rows, vector<int>(cols));
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matrix[i][j] = random_int(1, 21);
		}
	}

	return matrix;
}

int main()
{
	int rows;
	int cols;

	cout << "Input rows and cols: ";
	cin >> rows >> cols;

	vector<vector<int>> matrix = matrixGenerator(rows, cols);

	matrixPrinter(matrix);

	cout << "Sums: ";
	for (int i = 0; i < rows; i++) {
		int rowSum = 0;
		for (int j = 0; j < cols; j++) {
			int number = matrix[i][j];
			rowSum += number;
		}

		cout << rowSum << " ";
	}
}

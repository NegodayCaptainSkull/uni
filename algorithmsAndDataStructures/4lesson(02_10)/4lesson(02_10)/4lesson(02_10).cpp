#include <iostream>
#include <random>
#include <vector>

using namespace std;

int random_int(int min, int max) {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

vector<int> numberGenerator() {
    int n;
    cout << "Input length of number: ";
    cin >> n;

    vector<int> number;

    for (int i = 0; i < n; i++) {
        if (i == n - 1) {
            number.push_back(random_int(1, 9));
        }
        else {
            number.push_back(random_int(0, 9));
        }
    }

    return number;
}

void vectorPrinter(vector<int> number) {
    for (int i = number.size() - 1; i >= 0; i--) {
        cout << number[i];
    }

    cout << endl;
}

pair<vector<int>, vector<int>> sortNumbers(vector<int> firstNumber, vector<int> secondNumber) {
    if (firstNumber.size() > secondNumber.size()) {
        return { firstNumber, secondNumber };
    }
    else if (firstNumber.size() < secondNumber.size()) {
        return { secondNumber, firstNumber };
    }
    else if (firstNumber.size() == secondNumber.size()) {
        for (int i = firstNumber.size(); i >= 0; i--) {
            if (firstNumber[i] > secondNumber[i]) {
                return { firstNumber, secondNumber };
            }
            else if (firstNumber[i] < secondNumber[i]) {
                return { secondNumber, firstNumber };
            }
            else if (i == 0 && firstNumber[i] == secondNumber[i]) {
                return { firstNumber, secondNumber };
            }
        }
    }
}

vector<int> numberOperations(vector<int> firstNumber, vector<int> secondNumber, char operation) {
    pair<vector<int>, vector<int>> result = sortNumbers(firstNumber, secondNumber);
    vector<int> greaterNumber = result.first;
    vector<int> lowerNumber = result.second;
    vector<int> resultNumber;
    int numberInMind = 0;
    switch (operation) {
    case '+':
        for (int i = 0; i < greaterNumber.size(); i++) {
            if (i < lowerNumber.size()) {
                int middleResult = greaterNumber[i] + lowerNumber[i] + numberInMind;
                resultNumber.push_back(middleResult % 10);
                numberInMind = middleResult / 10;
            }
            else {
                int middleResult = greaterNumber[i] + numberInMind;
                resultNumber.push_back(middleResult % 10);
                numberInMind = middleResult / 10;
            }
        }
        return resultNumber;
    case '-':
        for (int i = 0; i < greaterNumber.size(); i++) {
            if (i < lowerNumber.size()) {
                int middleResult = greaterNumber[i] - lowerNumber[i] - numberInMind;
                if (middleResult < 0) {
                    resultNumber.push_back(middleResult + 10);
                    numberInMind = 1;
                }
                else {
                    resultNumber.push_back(middleResult);
                    numberInMind = 0;
                }
            }
            else {
                int middleResult = greaterNumber[i] - numberInMind;
                if (middleResult < 0) {
                    resultNumber.push_back(middleResult + 10);
                    numberInMind = 1;
                }
                else {
                    resultNumber.push_back(middleResult);
                    numberInMind = 0;
                }
            }
        }
        return resultNumber;
    }
}

int main() {
    vector<int> firstNumber = numberGenerator();
    vector<int> secondNumber = numberGenerator();

    char operation;
    cout << "What you want to do with numbers? (+/-): ";
    cin >> operation;

    vectorPrinter(firstNumber);
    vectorPrinter(secondNumber);

    vector<int> result = numberOperations(firstNumber, secondNumber, operation);

    vectorPrinter(result);
}
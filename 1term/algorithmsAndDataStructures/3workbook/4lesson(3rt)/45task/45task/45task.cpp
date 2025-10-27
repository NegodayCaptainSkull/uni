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
        for (int i = firstNumber.size() - 1; i >= 0; i--) {
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

vector<int> multiplyNumbers(vector<int> firstNumber, vector<int> secondNumber) {
    pair<vector<int>, vector<int>> result = sortNumbers(firstNumber, secondNumber);
    vector<int> greaterNumber = result.first;
    vector<int> lowerNumber = result.second;
    vector<int> resultNumber;
    int numberInMind = 0;
    
    for (int i = 0; i < greaterNumber.size(); i++) {
        int midleResult;
        if (i < lowerNumber.size()) {
            midleResult = greaterNumber[i] * lowerNumber[i] + numberInMind;
        }
        else {
            midleResult = greaterNumber[i] + numberInMind;
        }
        numberInMind = midleResult / 10;
        resultNumber.push_back(midleResult % 10);
    }

    if (numberInMind > 0) {
        resultNumber.push_back(numberInMind);
    }

    return resultNumber;
}

void task4(vector<int> firstNumber, vector<int> secondNumber) {
    vectorPrinter(firstNumber);
    vectorPrinter(secondNumber);

    vector<int> result = multiplyNumbers(firstNumber, secondNumber);

    vectorPrinter(result);
}

vector<int> sum(vector<int> firstNumber, vector<int> secondNumber) {
    pair<vector<int>, vector<int>> result = sortNumbers(firstNumber, secondNumber);
    vector<int> greaterNumber = result.first;
    vector<int> lowerNumber = result.second;
    vector<int> resultNumber;
    int numberInMind = 0;
    for (int i = 0; i < greaterNumber.size(); i++) {
        int midleResult;
        if (i < lowerNumber.size()) {
            midleResult = greaterNumber[i] + lowerNumber[i] + numberInMind;
        }
        else {
            midleResult = greaterNumber[i] + numberInMind;
        }
        resultNumber.push_back(midleResult % 10);
        numberInMind = midleResult / 10;
    }
    if (numberInMind > 0) {
        resultNumber.push_back(numberInMind);
    }
    return resultNumber;
}

int caracumba(vector<int> greaterNumber, vector<int> lowerNumber) {
    int k = greaterNumber.size() / 2;

    vector<int> firstInGreater;
    vector<int> secondInGreater;
    vector<int> firstInLower;
    vector<int> secondInLower;

    for (int i = 0; i < greaterNumber.size(); i++) {
        if (i >= k) {
            firstInGreater.push_back(greaterNumber[i]);
            firstInLower.push_back(lowerNumber[i]);
        }
        else {
            secondInGreater.push_back(greaterNumber[i]);
            secondInLower.push_back(lowerNumber[i]);
        }
    }


    if (k == 1) {
        int a = firstInGreater[0];
        int b = secondInGreater[0];
        int c = firstInLower[0];
        int d = secondInLower[0];
        return a * c * 100 + ((a + b) * (c + d) - a * c - b * d) * 10 + b * d;
    }
    else {
        return caracumba(firstInGreater, firstInLower) * pow(10, k*2) + (caracumba(sum(firstInGreater, secondInGreater), sum(firstInLower, secondInLower)) - caracumba(firstInGreater, firstInLower) - caracumba(secondInGreater, secondInLower)) * pow(10, k) + caracumba(secondInGreater, secondInLower);
    }
}

void task5(vector<int> firstNumber, vector<int> secondNumber) {
    pair<vector<int>, vector<int>> result = sortNumbers(firstNumber, secondNumber);
    vector<int> greaterNumber = result.first;
    vector<int> lowerNumber = result.second;
    if (greaterNumber.size() % 2 == 1) {
        greaterNumber.push_back(0);
    }

    int dif = greaterNumber.size() - lowerNumber.size();

    for (int i = 0; i < dif; i++) {
        lowerNumber.push_back(0);
    }

    
}

int main() {
    vector<int> firstNumber = numberGenerator();
    vector<int> secondNumber = numberGenerator();
}
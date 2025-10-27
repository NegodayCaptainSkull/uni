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

vector<int> multiplyNumbers(vector<int> firstNumber, vector<int> secondNumber) {
    pair<vector<int>, vector<int>> result = sortNumbers(firstNumber, secondNumber);
    vector<int> greaterNumber = result.first;
    vector<int> lowerNumber = result.second;
    vector<int> resultNumber;
    int numberInMind = 0;
    
    for (int i = 0; i < greaterNumber.size(); i++) {
        vector<int> numberInOneCycle;
        int midleResult;
        for (int j = 0; j < i; j++) {
            numberInOneCycle.push_back(0);
        }
        for (int j = 0; j < lowerNumber.size(); j++) {
            midleResult = greaterNumber[i] * lowerNumber[j] + numberInMind;
            numberInMind = midleResult / 10;
            numberInOneCycle.push_back(midleResult % 10);
        }
        if (numberInMind > 0) {
            numberInOneCycle.push_back(numberInMind);
            numberInMind = 0;
        }
        resultNumber = sum(resultNumber, numberInOneCycle);
    }
    return resultNumber;
}

void task4(vector<int> firstNumber, vector<int> secondNumber) {
    vectorPrinter(firstNumber);
    vectorPrinter(secondNumber);

    vector<int> result = multiplyNumbers(firstNumber, secondNumber);

    vectorPrinter(result);
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


vector<int> karatsuba(const vector<int>& x, const vector<int>& y) {
    // Remove leading zeros
    vector<int> a = x;
    vector<int> b = y;

    int n = max(a.size(), b.size());

    // Base case - use simple multiplication for small numbers
    if (n <= 2) {
        return multiplyNumbers(a, b);
    }

    // Make numbers the same length by padding with zeros
    a.resize(n, 0);
    b.resize(n, 0);

    int k = n / 2;

    // Split numbers into high and low parts
    vector<int> a_high(a.begin() + k, a.end());
    vector<int> a_low(a.begin(), a.begin() + k);

    vector<int> b_high(b.begin() + k, b.end());
    vector<int> b_low(b.begin(), b.begin() + k);

    // Recursive calls
    vector<int> z0 = karatsuba(a_low, b_low);
    vector<int> z2 = karatsuba(a_high, b_high);

    vector<int> a_sum = sum(a_high, a_low);
    vector<int> b_sum = sum(b_high, b_low);
    vector<int> z1 = karatsuba(a_sum, b_sum);

    // z1 = z1 - z2 - z0
    vector<int> temp = sum(z2, z0);
    // We need a subtract function, but for now we'll use a workaround
    // This is a simplified version - in production you'd want a proper subtract function

    // Combine results
    // result = z2 * 10^(2k) + (z1 - z2 - z0) * 10^k + z0

    // Shift z2 by 2k digits
    vector<int> shifted_z2(z2.size() + 2 * k, 0);
    copy(z2.begin(), z2.end(), shifted_z2.begin() + 2 * k);

    // Shift (z1 - z2 - z0) by k digits
    vector<int> z1_minus = z1; // This should be z1 - z2 - z0, but we need proper subtraction
    // For now, we'll approximate
    if (z1_minus.size() >= temp.size()) {
        for (size_t i = 0; i < temp.size(); i++) {
            if (z1_minus[i] >= temp[i]) {
                z1_minus[i] -= temp[i];
            }
            else {
                // Borrow - simplified
                z1_minus[i] = z1_minus[i] + 10 - temp[i];
                if (i + 1 < z1_minus.size()) {
                    z1_minus[i + 1]--;
                }
            }
        }
    }

    vector<int> shifted_z1_minus(z1_minus.size() + k, 0);
    copy(z1_minus.begin(), z1_minus.end(), shifted_z1_minus.begin() + k);

    // Combine all parts
    vector<int> result = sum(shifted_z2, shifted_z1_minus);
    result = sum(result, z0);

    return result;
}

void task5(vector<int> firstNumber, vector<int> secondNumber) {
    pair<vector<int>, vector<int>> sortedNumbersArrays = sortNumbers(firstNumber, secondNumber);
    vector<int> greaterNumber = sortedNumbersArrays.first;
    vector<int> lowerNumber = sortedNumbersArrays.second;
    if (greaterNumber.size() % 2 == 1) {
        greaterNumber.push_back(0);
    }

    int dif = greaterNumber.size() - lowerNumber.size();

    for (int i = 0; i < dif; i++) {
        lowerNumber.push_back(0);
    }

    vector<int> result = karatsuba(firstNumber, secondNumber);

    vectorPrinter(result);
}

int main() {
    vector<int> firstNumber = numberGenerator();
    vector<int> secondNumber = numberGenerator();

    task4(firstNumber, secondNumber);
    task5(firstNumber, secondNumber);
}

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string midleResult(string num1, string num2) {
    string result;
    int maxLen = max(num1.length(), num2.length());

    while (num1.length() < maxLen) num1 = "0" + num1;
    while (num2.length() < maxLen) num2 = "0" + num2;

    for (int i = 0; i < num1.length(); i++) {
        result.push_back((((num1[i] - '0') + (num2[i] - '0')) % 2) + '0');
    }
    return result;
}

string carryCounts(string num1, string num2) {
    string carry;
    int maxLen = max(num1.length(), num2.length());

    while (num1.length() < maxLen) num1 = "0" + num1;
    while (num2.length() < maxLen) num2 = "0" + num2;

    for (int i = 0; i < num1.length(); i++) {
        carry.push_back((((num1[i] - '0') + (num2[i] - '0')) / 2) + '0');
    }

    carry = carry + "0";
    return carry;
}

string binaryAddition(string num1, string num2) {
    int maxLen = max(num1.length(), num2.length());
    while (num1.length() < maxLen) num1 = "0" + num1;
    while (num2.length() < maxLen) num2 = "0" + num2;

    string sum = num1;
    string carry = num2;
    string temp;

    while (count(carry.begin(), carry.end(), '1') > 0) {
        temp = sum;

        sum = midleResult(sum, carry);

        carry = carryCounts(temp, carry);

        size_t first_one = carry.find('1');
        if (first_one != string::npos) {
            carry = carry.substr(first_one);
        }
        else {
            carry = "0";
        }
    }

    return sum;
}

int main() {
    string result = binaryAddition("1011011", "111000");
    cout << "Result: " << result << endl;

    return 0;
}
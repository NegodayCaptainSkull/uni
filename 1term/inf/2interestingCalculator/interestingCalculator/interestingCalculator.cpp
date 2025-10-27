#include <iostream>
#include <string>
using namespace std;

string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int hexToDecimal(string hex) {
    int decimal = 0, power = 0;

    for (int i = hex.length() - 1; i >= 0; i--) {
        char c = toupper(hex[i]);
        int value = (c >= '0' && c <= '9') ?
            (c - '0') : (c - 'A' + 10);

        decimal += value * pow(16, power++);
    }

    return decimal;
}

string decimalToHex(int decimal) {
    string hexChars = "0123456789ABCDEF";
    string hexResult;

    while (decimal > 0) {
        hexResult = hexChars[decimal % 16] + hexResult;
        decimal /= 16;
    }

    return hexResult.empty() ? "0" : hexResult;
}

string sum(string a, string b, int system) {
    string greaterString = a.length() >= b.length() ? a : b;
    string shorterString = a.length() <= b.length() ? b : a;

    string reversedGreaterString = string(greaterString.rbegin(), greaterString.rend());
    string reversedShorterString = string(shorterString.rbegin(), shorterString.rend());

    string result = "";
    string inMind = "0";

    for (int i = 0; i < reversedGreaterString.length(); i++) {
        int indexOfNumInMind = chars.find_first_of(inMind);
        int indexOfGreaterNum = chars.find_first_of(reversedGreaterString[i]);

        string charToWrite = "";

        if (reversedShorterString[i]) {
            int indexOfShorterNum = chars.find_first_of(reversedShorterString[i]);
            
            int numToWrite = indexOfGreaterNum + indexOfShorterNum + indexOfNumInMind;
            if (numToWrite >= system) {
                inMind = "1";
                charToWrite = chars[numToWrite - system];
            }
            else {
                charToWrite = chars[numToWrite];
                inMind = "0";
            }
        }
        else {
            int numToWrite = indexOfGreaterNum + indexOfNumInMind;
            if (numToWrite >= system) {
                inMind = "1";
                charToWrite = chars[numToWrite - system];
            }
            else {
                charToWrite = chars[numToWrite];
                inMind = "0";
            }
        }

        result += charToWrite;
    }

    if (inMind == "1") {
        result += inMind;
    }

    string properResult = string(result.rbegin(), result.rend());
    return properResult;
}

string subtraction(string a, string b, int system) {
    string greaterString = a.length() >= b.length() ? a : b;
    string shorterString = a.length() <= b.length() ? b : a;

    string reversedGreaterString = string(greaterString.rbegin(), greaterString.rend());
    string reversedShorterString = string(shorterString.rbegin(), shorterString.rend());

    string result = "";
    string inMind = "0";

    for (int i = 0; i < reversedGreaterString.length(); i++) {
        int indexOfNumInMind = chars.find_first_of(inMind);
        int indexOfGreaterNum = chars.find_first_of(reversedGreaterString[i]);

        string charToWrite = "";

        if (reversedShorterString[i]) {
            int indexOfShorterNum = chars.find_first_of(reversedShorterString[i]);

            int numToWrite = indexOfGreaterNum - indexOfShorterNum - indexOfNumInMind;
            if (numToWrite < 0) {
                inMind = "1";
                charToWrite = chars[numToWrite + system];
            }
            else {
                charToWrite = chars[numToWrite];
                inMind = "0";
            }
        }
        else {
            int numToWrite = indexOfGreaterNum - indexOfNumInMind;
            if (numToWrite < 0) {
                inMind = "1";
                charToWrite = chars[numToWrite + system];
            }
            else {
                charToWrite = chars[numToWrite];
                inMind = "0";
            }
        }

        result += charToWrite;
    }

    if (inMind == "1") {
        return "wrong numbers";
    }

    string properResult = string(result.rbegin(), result.rend());
    return properResult;
}

string multiplication(string a, string b, int system) {
    string greaterString = a.length() >= b.length() ? a : b;
    string shorterString = a.length() <= b.length() ? b : a;

    string reversedGreaterString = string(greaterString.rbegin(), greaterString.rend());
    string reversedShorterString = string(shorterString.rbegin(), shorterString.rend());

    string result = "";
    string inMind = "0";

    for (int i = 0; i < reversedGreaterString.length(); i++) {
        int indexOfNumInMind = chars.find_first_of(inMind);
        int indexOfGreaterNum = chars.find_first_of(reversedGreaterString[i]);

        string charToWrite = "";

        if (reversedShorterString[i]) {
            int indexOfShorterNum = chars.find_first_of(reversedShorterString[i]);

            int numToWrite = indexOfGreaterNum * indexOfShorterNum + indexOfNumInMind;
            if (numToWrite >= system) {
                int category = numToWrite / system;
                inMind = to_string(category);
                charToWrite = chars[numToWrite - system * category];
            }
            else {
                charToWrite = chars[numToWrite];
                inMind = "0";
            }
        }
        else {
            int numToWrite = indexOfGreaterNum + indexOfNumInMind;
            if (numToWrite >= system) {
                int category = numToWrite / system;
                inMind = to_string(category);
                charToWrite = chars[numToWrite - system*category];
            }
            else {
                charToWrite = chars[numToWrite];
                inMind = "0";
            }
        }

        result += charToWrite;
    }

    if (inMind != "0") {
        result += inMind;
    }

    string properResult = string(result.rbegin(), result.rend());
    return properResult;
}

string division(string a, string b, int system) {

}

int main()
{
    string a;
    string b;
    char operation;
    int system;

    cin >> a >> operation >> b >> system;

    switch (operation) {
    case '+':
        cout << sum(a, b, system) << endl;
        break;
    case '-':
        cout << subtraction(a, b, system);
        break;
    case '*':
        cout << multiplication(a, b, system);
        break;
    }
}

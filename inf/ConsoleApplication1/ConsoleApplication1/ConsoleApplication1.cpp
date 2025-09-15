#include <iostream>

using namespace std;

void theme3() {
    double x;
    double y;

    cin >> x >> y;

    int counter = 1;

    while (x <= y) {
        x *= 1.1;
        counter++;
    }

    cout << counter;
}

void theme4q1() {
    int32_t a;
    int32_t b;
    char operation;

    cin >> a >> operation >> b;

    int64_t result;
    switch (operation) {
    case '+':
        result = a + b;
        break;
    case '-':
        result = a - b;
        break;
    case '*':
        result = a * b;
        break;
    case '/':
    case ':':
        result = a / b;
        break;
    default:
        result = 0;
    }

    cout << result;
}

void theme4q2() {
    int A;
    int B;

    cin >> A >> B;

    while (A > B) {
        switch (A % 2) {
        case 1:
            A -= 1;
            cout << "-1" << endl;
            break;
        case 0:
            A /= 2;
            cout << ":2" << endl;
            break;
        }
    }
}

int main()
{
    //theme3();
    //theme4q1();
    theme4q2();
}
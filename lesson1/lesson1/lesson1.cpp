#include <iostream>
#include <string>

int main() {
    // Задание 1
    //int a;
    //int b;
    //
    //std::cin >> a >> b;

    //int sum = a + b;

    //std::cout << sum;

    // 2
    //int a;
    //int b;
    //
    //std::cin >> a >> b;

    //int sum = a + b;
    //int dif = a - b;
    //int multiplication = a * b;
    //int division = a / b;

    //std::cout << sum << " " << dif << " " << multiplication << " " << division;

    // 3
    //float a;
    //float b;

    //std::cin >> a >> b;

    //float c = pow((pow(a, 2) + pow(b, 2)), 0.5);
    //std::cout << c;

    // 4
    //int length = 109;
    //int v;
    //int t;

    //std::cin >> v >> t;

    //int movement = v * t;
    //int mark = movement % length;
    //std::cout << mark;

    //5 

    int n;
    std::cin >> n;
    int h = n / 3600;
    int m = n / 60;
    int s = n % 60;
    std::string m_string = std::to_string(m);
    std::string s_string = std::to_string(s);

    if (m < 10) {
        m_string = "0" + m_string;
    }
    if (s < 10) {
        s_string = "0" + s_string;
    }

    std::cout << h << ":" << m_string << ":" << s_string;
}
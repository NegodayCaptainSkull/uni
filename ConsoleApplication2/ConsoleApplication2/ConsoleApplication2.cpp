
#include <cmath>
#include <iostream>

using namespace std;
double fun(double x) {
    return (1 - x + sin(x) - log2(x));
}

double methodHord(double a, double b) {
    double top = (b - a) * fun(a);
    //cout << fun(a) << endl;
    double bottom = fun(b) - fun(a);
    //cout << bottom << endl;
    double division = top / bottom;
    double newX = a - division;
    //cout << division << endl;
    //double newX = a - (((b - a) * (fun(a)) / (fun(b) - fun(a))));
    return newX;
}

int main()
{

    double E = 0.00000001, a = 0, b = 2, p = fun(a), q = fun(b);
    a += E;
    cout << p;
    //while (abs(p - q) > E) {
    //    double tempx = (a + b) / 2;
    //    double tempy = fun(tempx);

    //    if (tempy * q < 0) {
    //        p = tempy;
    //        a = tempx;
    //    }
    //    else {
    //        q = tempy;
    //        b = tempx;
    //    }
    //}
    //cout << a << endl;
    //cout << (1 - a + sin(a) - log2(a));

   
    while (abs(p - q) > E) {
        double temp2x = methodHord(a, b);
        cout << temp2x;
        double temp2y = fun(temp2x);
        if (temp2y * q < 0) {
            p = temp2y;
            a = temp2x;
        }
        else {
            q = temp2y;
            b = temp2x;
        }
    }

    cout << b << endl;
    cout << a << endl;
}
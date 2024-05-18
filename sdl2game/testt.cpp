#include <iostream>
#include <algorithm>
using namespace std;

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int g_c_d(int a, int b, int c, int d) {
    return gcd(gcd(gcd(a, b), c), d);
}

int main() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    int result = g_c_d(a, b, c, d);
    cout << result << endl;

    return 0;
}

#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int a = 1, b = n;
    while (true) {
        int m = (a + b) / 2;
        cout << m << endl << flush;
        int res;
        cin >> res;
        if (res == 0) {
            return 0;
        }
        if (res > 0) {
            a = m + 1;
        } else {
            b = m;
        }
    }
    return 0;
}

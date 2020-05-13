#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double X;
    cin >> X;
    cout << setiosflags(ios::fixed | ios::showpoint) << setprecision(2) << X * 3. / 5 << endl;
    return 0;
}

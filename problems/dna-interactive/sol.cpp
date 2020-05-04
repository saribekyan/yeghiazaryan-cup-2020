#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

int main() {
    string E;
    cin >> E;
    int n = E.size();

    int iters = 100;
    int qlen = 50;

    for (int i = 0; i < iters; ++i) {
        int s = rand() % (n - qlen + 1);
        cout << E.substr(s, qlen) << endl << flush;
        string ans;
        cin >> ans;
        if (ans == "Yes") {
            cout << "Earthovirus" << endl << flush;
            return 0;
        }
    }
    cout << "Marsovirus" << endl << flush;
    return 0;
}

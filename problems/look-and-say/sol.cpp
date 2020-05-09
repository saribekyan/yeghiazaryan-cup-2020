#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector< int > s;
    s.push_back(1);
    for (int i = 2; i <= n; ++i) {
        s.push_back(0);
        vector< int > t;
        int c = 1;
        for (int j = 1; j < s.size(); ++j) {
            if (s[j] != s[j - 1]) {
                t.push_back(c);
                t.push_back(s[j - 1]);
                c = 1;
            } else {
                c += 1;
            }
        }
        s = t;
    }
    for (int i = 0; i < s.size(); ++i) {
        cout << s[i];
    }
    cout << endl;
    return 0;
}

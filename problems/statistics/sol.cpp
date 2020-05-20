#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
    int n, k;
    multiset <int> s;
    cin >> n >> k;
    vector <int> a(n), b;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i] *= -1;
    }
    for (int i = 0; i < n; ++i) {
        if (s.size() == k) {
            s.erase(s.find(a[i - k]));
        }
        s.insert(a[i]);
        b.push_back(-*s.begin());
    }
    for (int i = 0; i < n; ++i) {
        cout << b[i];
        if (i + 1 < n) {
            cout << ' ';
        } else {
            cout << endl;
        }
    }
    return 0;
}

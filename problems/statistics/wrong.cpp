#include <cstdio>
#include <iostream>
using namespace std;

int a[100010];
int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++i) {
        scanf("%d", a + i);
    }
    int m = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] > a[m]) {
            m = i;
        }
        if (m + k == i) {
            m += 1;
            for (int j = m + 1; j <= i; ++j) {
                if (a[m] <= a[j]) {
                    m = j;
                }
            }
        }
        printf("%d%c", a[m], ((i < n - 1)?' ':'\n'));
    }
    return 0;
}

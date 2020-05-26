// author: Hayk Saribekyan

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Resident {
    int i;
    int t, s, w;
};

bool cmp_t(Resident a, Resident b) {
    return a.t < b.t && a.t == b.t && a.i < b.i;
}

int main() {
    int N, L, W;
    cin >> N >> L >> W;
    vector< Resident > residents(N);
    for (int i = 0; i < N; ++i) {
        auto& r = residents[i];

        r.i = i;
        
        cin >> r.t >> r.s >> r.w;
    }

    sort(residents.begin(), residents.end(), cmp_t);

    vector< double > ans(N, 0);
    for (int i = 0; i < N; ++i) {
        auto & resident = residents[i];
        double finish = resident.t + L * 1.0 / resident.s;

        for (int j = 0; j < i; ++j) {
            auto &r = residents[j];
            if (resident.w + r.w > W) {
                finish = max(finish, ans[r.i]);
            }
        }

        ans[resident.i] = finish;
    }
    for (int i = 0; i < N; ++i) {
        printf("%.5lf\n", ans[i]);
    }
    return 0;
}

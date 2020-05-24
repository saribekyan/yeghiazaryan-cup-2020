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
    return a.t < b.t;
}

struct Fenwick {
    int n;
    vector< double > d;

    Fenwick(int size) {
        n = size;
        d = vector < double >(n + 1, 0); // shifted indexing
    }

    void set(int i, double x) { // set i to x
        for (i += 1; i <= n; i += (i & (-i))) {
            d[i] = max(d[i], x);
        }
    }

    double get_max(int i) { // max of 0...i
        double res = 0.0;
        for (i += 1; i > 0; i -= (i & (-i))) {
            res = max(res, d[i]);
        }
        return res;
    }
};

int main() {
    int N, L, W;
    cin >> N >> L >> W;
    vector< Resident > residents(N);
    vector< int > widths;
    for (int i = 0; i < N; ++i) {
        auto& r = residents[i];

        r.i = i;
        
        cin >> r.t >> r.s >> r.w;

        widths.push_back(r.w);
    }

    sort(residents.begin(), residents.end(), cmp_t);
    sort(widths.begin(), widths.end());

    int n_ranks = 1;
    for (int i = 1; i < N; ++i) {
        if (widths[i] != widths[n_ranks - 1]) {
            widths[n_ranks] = widths[i];
            n_ranks += 1;
        }
    }
    widths.resize(n_ranks);

    vector< double > ans(N);

    auto F = Fenwick(n_ranks);

    for (auto resident : residents) {
        double finish = resident.t + L * 1.0 / resident.s;

        int w_left = W - resident.w; // largest size that can pass
        int first_not_passing = (int)(upper_bound(widths.begin(), widths.end(), w_left) - widths.begin());

        if (first_not_passing < n_ranks) {
            finish = max(finish, F.get_max(n_ranks - first_not_passing - 1));
        }

        int self_rank = (int)(lower_bound(widths.begin(), widths.end(), resident.w) - widths.begin());
        F.set(n_ranks - self_rank - 1, finish);

        ans[resident.i] = finish;
    }
    for (int i = 0; i < N; ++i) {
        printf("%.5lf\n", ans[i]);
    }
    return 0;
}

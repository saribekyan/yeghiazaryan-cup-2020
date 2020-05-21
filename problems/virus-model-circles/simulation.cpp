#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const double EPS = 1e-8;

int main() {
    long long T;
    long long ax, ay, avx, avy;
    long long bx, by, bvx, bvy;
    scanf("%lld", &T);
    scanf("%lld%lld%lld%lld", &ax, &ay, &avx, &avy);
    scanf("%lld%lld%lld%lld", &bx, &by, &bvx, &bvy);

    // bring A to (0, 0), and make it stay there
    long long x = bx - ax;
    long long y = by - ay;
    long long vx = bvx - avx;
    long long vy = bvy - avy;

    long long r = 2;

    double step = 1e-4;

    double sx = x;
    double sy = y;
    double t = 0.0;
    while (t <= T + EPS) {
        if (sx * sx + sy * sy <= r * r + EPS) {
            printf("%.4lf\n", t);
            return 0;
        }
        sx += step * vx;
        sy += step * vy;
        t += step;
    }
    printf("-1\n");
    return 0;
}

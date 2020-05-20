#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

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

    if (vx == 0 && vy == 0) {
        if (x * x + y * y <= 2 * 2) {
            printf("0\n");
        } else {
            printf("-1\n");
        }
        return 0;
    }

    double step = 1e-5 / 2;

    double sx = x;
    double sy = y;
    double t = 0.0;
    while (t <= T) {
        if (sx * sx + sy * sy <= r * r) {
            printf("%.5lf\n", t);
            return 0;
        }
        sx += step * vx;
        sy += step * vy;
        t += step;
    }
    printf("-1\n");
    return 0;
}

#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const double EPS = 1e-8;

// f - first; s - second
// because stupid g++ doesn't like y0 and y1
double xf, yf, xs, ys;

// http://e-maxx.ru/algo/circle_line_intersection
int intersections(double a, double b, double c, double r) {
    double xx = -a*c/(a*a+b*b), yy = -b*c/(a*a+b*b);
    if (c*c > r*r*(a*a+b*b)+EPS) {
        return 0;
    }
    else if (abs (c*c - r*r*(a*a+b*b)) < EPS) {
        xf = xx;
        yf = yy;
        return 1;
    }
    else {
        double d = r*r - c*c/(a*a+b*b);
        double mlt = sqrt (d / (a*a+b*b));
        double ax,ay,bx,by;
        xf = xx + b * mlt;
        xs = xx - b * mlt;
        yf = yy - a * mlt;
        ys = yy + a * mlt;
        return 2;
    }
}

double norm2(double x, double y) {
    return sqrt(x * x + y * y);
}

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
            printf("%.5lf\n", 0.0);
        } else {
            printf("-1\n");
        }
        return 0;
    }

    // http://e-maxx.ru/algo/segment_to_line 
    // P = (x, y); Q = (x, y) + (vx, vy)
    double a = -vy;
    double b = vx;
    double c = -a * x - b * y;

    int count = intersections(a, b, c, r);

    fprintf(stderr, "%d\n", count);

    if (count == 0) {
        printf("-1\n");
        return 0;
    }
    fprintf(stderr, "%.5lf %.5lf\n", xf, yf);

    double speed = norm2(vx, vy);

    double t = norm2(xf - x, yf - y) / speed;
    if (count == 2) {
        fprintf(stderr, "%.5lf %.5lf\n", xs, ys);
        t = min( t, norm2(xs - x, ys - y) / speed );
    }

    if (t <= T + EPS) {
        printf("%.5lf\n", t);
    } else {
        printf("-1\n");
    }
    return 0;
}

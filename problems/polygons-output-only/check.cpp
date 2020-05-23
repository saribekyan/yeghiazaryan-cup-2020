#define EJUDGE

#include <string>
#include <iostream>
#include <vector>
#include "../../testlib/testlib.h"
using namespace std;

const double error = 1.0 / 100; // 1 percent

int main(int argc, char * argv[]) {
    setName("compares outputs of numbers of corners; max error = %lf percent", error);
    registerTestlibCmd(argc, argv);

    int n = ans.readInt();
    cerr << n << " viruses" << endl;

    auto correct = ans.readIntegers(n);
    auto yours   = ouf.readIntegers(n);

    int n_wrong = 0;
    cerr << "Wrong classification\n";
    cerr << "    ";
    for (int i = 0; i < n; ++i) {
        if (correct[i] != yours[i]) {
            n_wrong++;
            cerr << " (" << i + 1 << ", " << correct[i] << ", " << yours[i] << "),";
        }
    }
    if (n_wrong == 0) {
        cerr << "None!";
    }
    cerr << endl;
    cerr << "Number of wrong: " << n_wrong << endl;

    if (n_wrong > error * n) {
        cerr << "More than " << error << "% errors... too many..." << endl;
        quitf(_wa, "%d errors; more than %.2lf errors... too many...",
                    n_wrong, error);
    } else {
        cerr << "Ok!" << endl;
        quitf(_ok, "%d errors - ok!", n_wrong);
    }
    return 0;
}

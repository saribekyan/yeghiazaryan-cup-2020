#define EJUDGE

#include <string>
#include <iostream>
#include <vector>
#include "../../testlib/testlib.h"
using namespace std;

const int N = 482;
const int error = 10;

bool is_ok(string a, string b) {
    for (int i = 0; i + 2 < a.size(); ++i) {
        for (int j = 0; j + 2 < b.size(); ++j) {
            bool ok = true;
            for (int k = 0; k < 3; ++k) {
                if (a[i + k] != b[j + k]) {
                    ok = false;
                }
            }
            if (ok) {
                return true;
            }
        }
    }
    return false;
}

int main(int argc, char * argv[]) {
    setName("compares outputs f1; max error = %d/%d percent", error, N);
    registerTestlibCmd(argc, argv);

    cerr << "Comparing for F1: Max errors = " << error << "/" << N << '\n';


    int n_wrong = 0;
    cerr << "Wrong classification\n";
    cerr << "    index    expected    received\n";
    for (int i = 0; i < N; ++i) {
        auto correct = ans.readLine();
        auto yours   = ouf.readLine();
        if (yours.size() > 100) {
            quitf(_wa, "Received a string longer than 100 chars");
        }
        if (!is_ok(correct, yours)) {
            n_wrong++;
            cerr << i + 1 << " \"" << correct << "\" \"" << yours << "\"\n";
        }
    }
    cerr << endl;
    cerr << "Number of wrong: " << n_wrong << endl;

    if (n_wrong > error) {
        cerr << "More than " << error << " errors... too many..." << endl;
        quitf(_wa, "%d errors; more than %d errors... too many...",
                    n_wrong, error);
    } else {
        cerr << "Ok!" << endl;
        quitf(_ok, "%d errors - ok!", n_wrong);
    }
    return 0;
}

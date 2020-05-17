// info - https://codeforces.com/testlib

#define EJUDGE

#include "../../testlib/testlib.h"
#include <iostream>

using namespace std;

const int MAX_Q = 100;

int main(int argc, char* argv[])
{
    setName("Interactor for Guess the Number");
    registerInteraction(argc, argv);

    // inf  - from input file
    // ans  - from answer file
    // ouf  - from output of the program to be tested
    // cout - to stdin of the program to be tested
    // tout - log of the interactor (which should be cleared by the checker)

    // reads number of queries from test (input) file
    int n = inf.readInt();
    int h = inf.readInt(1, n);

    // tell the program n
    cout << n << endl << flush;

    int nq = 0;
    while (true) {
        int x = ouf.readInt(1, n);
        if (h < x) {
            cout << -1 << endl << flush;
        } else if (h > x) {
            cout << 1 << endl << flush;
        } else {
            cout << 0 << endl << flush;
            tout << "ok";
            quitf(_ok, "ok");
        }
        nq += 1;
        if (nq > MAX_Q) {
            tout << "Too many steps";
            quitf(_wa, "Too many steps");
        }
    }

    // just message
    quitf(_ok, "shouldn't be here");
}

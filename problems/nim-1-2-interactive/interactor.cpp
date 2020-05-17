// info - https://codeforces.com/testlib

#define EJUDGE

#include "../../testlib/testlib.h"
#include <iostream>
using namespace std;

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

    tout << n << endl;
    cout << n << endl << flush;

    while (true) {
        int d = ouf.readInt(1, 2);

        n -= d;

        tout << "> " << d << " n = " << n << endl;
        if (n <= 0) {
            tout << "program reached 0 and lost" << endl;
            quitf(_wa, "program reached 0 and lost");
        }
        if (n == 1) {
            tout << "ok. we lost..." << endl;
            quitf(_ok, "ok");
        }
        if (n % 3 == 1) {
            d = rnd.next(1, 2);
        } else if (n % 3 == 2) {
            d = 1;
        } else {
            d = 2;
        }
        n -= d;
        tout << "< " << d << " n = " << n << endl;
        cout << d << endl << flush;
    }

    // just message
    quitf(_ok, "shouldn't be here");
}

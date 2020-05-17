#define EJUDGE

#include <string>
#include <iostream>
#include "../../testlib/testlib.h"
using namespace std;

int main(int argc, char * argv[]) {
    setName("compares log of interactor to actual output");
    registerTestlibCmd(argc, argv);
    
    // checker accepts the result because it trusts the interactor
    // it needs to empty the log file for some reason anyway.
    while ( !ouf.seekEof() ) {
        ouf.readToken();
    }

    quitf(_ok, "if we got here, we're good!");
    return 0;
}

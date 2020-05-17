// info - https://codeforces.com/testlib

// interactor program written using KMP
// the runtime per query is O(|S| + |E|), which is still ok
// because the total number of queries is up to 100 and the total
// number of characters allowed is 10^6

#define EJUDGE

#include "../../testlib/testlib.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_Q = 100;
const int MAX_TOTAL_CHARS = 1000000;

// from http://e-maxx.ru/algo/prefix_function
void compute_prefix_function(string& s, vector< int >& pi) {
	int n = (int) s.length();
    pi[0] = 0;
	for (int i = 1; i < n; ++i) {
		int j = pi[i - 1];
		while (j > 0 && s[i] != s[j]) {
			j = pi[j - 1];
        }
		if (s[i] == s[j]) {
            j += 1;
        }
		pi[i] = j;
	}
}

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

    string E = inf.readString();
    int same = inf.readInt(0, 1);
    int nx = inf.readInt();
    inf.nextLine();

    int L = 0; // the longest X
    string X = "#";
    for (int i = 0; i < nx; ++i) {
        string z = inf.readString();
        L = max(L, (int)z.size());
        X += z + "#";
    }
    int m = X.size();

    string ok = "Earthovirus";
    string wa = "Randovirus";
    if (same == 0) {
        swap(ok, wa);
    }

    //////////////// Preprocess //////////////////

    auto pi = vector< int >(L + 1 + m);

    // test
    // compute_prefix_function(E, pi);
    // for (int i = 0; i < E.size(); ++i) {
    //     cerr << pi[i] << ' ';
    // }
    // cerr << endl;

    //////////////// Start interaction ///////////

    cout << E << endl << flush;

    int nq = 0;
    int total_chars = 0;

    while (true) {
        string S = ouf.readString();
        int len_s = S.size();

        // check if found answer
        if (S == ok) {
            tout << "ok" << endl;
            quitf(_ok, "ok");
        } else if (S == wa) {
            tout << "Incorrectly answered " << S << endl;
            quitf(_wa, "wa");
        }

        // check number of queries
        nq += 1;
        if (nq > MAX_Q) {
            tout << "Too many queries" << endl;
            quitf(_wa, "Too many queries");
        }

        // check total number of characters
        total_chars += len_s;
        if (total_chars > MAX_TOTAL_CHARS) {
            tout << "Too many characters";
            quitf(_wa, "Too many characters");
        }

        // check the alphabet in the query
        for (char c : S) {
            if (c != 'A' && c != 'G' && c != 'C' && c != 'T') {
                tout << "Bad character: " << c;
                quitf(_pe, "Bad character: %c", c);
            }
        }

        if (len_s > L) {
            tout << "Query was very long" << endl;
            cout << "No" << endl << flush;
            continue;
        }

        bool found = false;
        S = S + "|" + X;
        compute_prefix_function(S, pi);
        for (int i = 2 * len_s; i < len_s + 1 + m; ++i) {
            if (pi[i] >= len_s) {
                found = true;
                break;
            }
        }

        if (found) {
            cout << "Yes" << endl << flush;
        } else {
            cout << "No" << endl << flush;
        }
    }

    // just message
    quitf(_ok, "shouldn't be here");
}

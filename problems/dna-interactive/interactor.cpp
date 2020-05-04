// info - https://codeforces.com/testlib

#include "../../testlib/testlib.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

const int MAX_Q = 100;
const int MAX_TOTAL_CHARS = 1000000;

const long long P = 1993;

const int SMALL = 16; // keep the hashes of strings up to SMALL separately

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
        string x = inf.readString();
        L = max(L, (int)x.size());
        X += x + "#";
    }
    int m = X.size();

    string ok = "Earthovirus";
    string wa = "Marsovirus";
    if (same == 0) {
        swap(ok, wa);
    }

    ///////////////// Preprocess ////////////////
    // Prepare hashes
    vector < long long > prefix_hash(m, 0), power(m, 0);
    prefix_hash[0] = X[0];
    power[0] = 1;
    for (int i = 1; i < m; ++i) {
        prefix_hash[i] = prefix_hash[i - 1] * P + X[i];
        power[i] = power[i - 1] * P;
    }

    vector< int > str_lengths;
    for (int l = 1; l < SMALL && l <= L; ++l) {
        str_lengths.push_back(l);
    }
    for (int l = SMALL; l <= L; l *= 2) {
        str_lengths.push_back(l);
    }
    int n_lengths = str_lengths.size();

    // keeps for each (length, hash) -> { set of positions which have that hash }
    vector < unordered_map < long long , vector < int > > > len_hash_locs(n_lengths);

    for (int i = 0; i < n_lengths; ++i) {
        int l = str_lengths[i];
        for (int p = 1; p + l < m; ++p) {
            int q = p + l - 1;
            long long h = prefix_hash[q] - prefix_hash[p - 1] * power[l];
            len_hash_locs[i][h].push_back(p);

            // cerr << l << ' ' << p << ' ' << h << '\n';
        }
    }

    // cerr << 65 * P + 65 << '\n';
    // cerr << len_hash_locs[0].begin()->first << ' ' << len_hash_locs[0].begin()->second[0] << '\n';
    // cerr << len_hash_locs[1].begin()->first << ' ' << len_hash_locs[1].begin()->second[0] << '\n';

    //////////////// End preprocess //////////////

    //////////////// Start interaction ///////////

    cout << E << endl << flush;

    int nq = 0;
    int total_chars = 0;

    while (true) {
        string S = ouf.readString();
        if (S == ok) {
            tout << "ok" << endl;
            quitf(_ok, "ok");
        } else if (S == wa) {
            tout << "Incorrectly answered " << S << endl;
            quitf(_wa, "wa");
        }

        nq += 1;
        if (nq > MAX_Q) {
            tout << "Too many queries" << endl;
            quitf(_wa, "Too many queries");
        }

        int len_s = S.size();

        total_chars += len_s;
        if (total_chars > MAX_TOTAL_CHARS) {
            tout << "Too many characters";
            quitf(_wa, "Too many characters");
        }

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

        int i = 0;
        while (i < n_lengths && str_lengths[i] <= len_s) {
            i++;
        }
        i -= 1;
        int l = str_lengths[i];
        long long hash_beg = 0, hash_end = 0;
        for (int j = 0; j < l; ++j) {
            hash_beg = hash_beg * P + S[j];
            hash_end = hash_end * P + S[len_s - l + j];
        }

        bool found = false;
        if (len_hash_locs[i].find(hash_beg) != len_hash_locs[i].end()) {
            for (int p : len_hash_locs[i][hash_beg]) {
                int q = p + len_s - 1;
                if (hash_end == prefix_hash[q] - prefix_hash[q - l] * power[l]) {
                    // all hashes match, let's just verify to make sure
                    bool almost_found = true;
                    for (int u = 0; u < len_s; ++u) {
                        if (S[u] != X[p + u]) {
                            almost_found = false;
                            break;
                        }
                    }
                    if (almost_found) {
                        found = true;
                        break;
                    }
                }
            }
        }

        if (found) {
            cout << "Yes" << endl << flush;
        } else {
            cout << "No" << endl << flush;
        }
        tout << "Query went through hash" << endl;
    }

    // just message
    quitf(_ok, "shouldn't be here");
}

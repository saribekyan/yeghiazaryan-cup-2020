#include <iostream>
#include <set>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

struct f1 {
    int year, round, place;
    f1(int y, int r, int p): year(y), round(r), place(p) {}
};
bool operator < (f1 a, f1 b) {
    if (a.year == b.year) {
        if (a.round == b.round) {
            return a.place < b.place;
        }
        return a.round < b.round;
    }
    return a.year < b.year;
}

int main() {
    srand(time(0));
    ofstream out("tests/002");
    set <f1> st;
    for (int i = 0; i < 500; ++i) {
        int year = 1970 + rand() % 44;
        int place = 1 + rand() % 10;
        int round = 1 + rand() % (year < 1990 ? 10 : 15);
        f1 obj(year, round, place);
        if (st.find(obj) == st.end()) {
            st.insert(obj);
            out << "Who finished at the position " << place << " in round " << round << " of " << year << " F1 championship" << endl;
        }
    }
}
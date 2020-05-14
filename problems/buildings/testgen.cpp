#include <iostream>
#include <set>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <random>
#include <limits>

using namespace std;

const int testsCount = 6;
const int predefinedTestsCount = 24; // these testes were already prepared without this generator

class Test {
    private: 
        vector <int> x;
        vector <int> y;
    public:
        Test() {}
    
    static long long rand(int L, int R) {
        std::random_device rd;
        std::mt19937_64 eng(rd());
        std::uniform_int_distribution<unsigned long long> distr;
        return L +  distr(eng) % (R - L + 1);
    }

    static Test generate(int testIndex, int testsCount) {
        const int minN = 100000;
        int L = max(1, testIndex * minN / testsCount);
        int R = min(minN, (testIndex + 1) * minN / testsCount);
        int n = min(2 * minN, minN + (int)Test::rand(L, R));
        Test t;
        long long P = 1000;
        for (int i = 0; i < testIndex; ++i) {
            P *= 10;
            P = min(P, 1000000000LL);
        }
        set <pair <int, int> > st;
        for (int i = 0; i < n; ++i) {
            int xt = Test::rand(0, P);
            int yt = Test::rand(0, P);
            auto pr = make_pair(xt, yt);
            if (st.find(pr) != st.end()) {
                --i;
                continue;
            }
            t.x.push_back(xt);
            t.y.push_back(yt);
            st.insert(pr);
        }
        return t;
    }
    friend ostream& operator << (ostream& oss, const Test& t) {
        oss << t.x.size() << endl;
        for (int i = 0; i < t.x.size(); ++i)
            oss << t.x[i] << " " << t.y[i] << endl;
        return oss;
    }
};

int main() {
    //system("rm -rf tests");
    //system("mkdir tests");
    vector <Test> tests;
    for (int i = 0; tests.size() < testsCount; ++i) {
        cout << "Generating test " << i << endl;
        tests.push_back(Test::generate(i, testsCount));
    }
    for (int i = 0; i < tests.size(); ++i) {
        int testNumber = i + 1 + predefinedTestsCount;
        cout << "Printing test " << testNumber << " to the file" << endl;
        ostringstream path;
        path << "tests/" << std::setfill('0') << std::setw(3) << to_string(testNumber);
        ofstream out(path.str().c_str());
        out << tests[i];
    }
}
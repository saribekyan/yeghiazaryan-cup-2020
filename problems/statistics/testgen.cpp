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

const int testsCount = 0;
const int predefinedTestsCount = 51; // these testes were already prepared without this generator

class Test {
    private: 
        int k;
        vector <int> a;
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
        if (testIndex < 10) {
            L = 1;
            R = 100;
        } else
        if (testIndex < 15) {
            L = 100;
            R = 1000;
        } else
        if (testIndex < 20) {
            L = 1000;
            R = 10000;
        }
        
        int n = (int)Test::rand(L, R);
        Test t;
        t.k = Test::rand(1, n);
        for (int i = 0; i < n; ++i) {
            t.a.push_back(Test::rand(0, (1 << (min(testIndex, 29)))));
        }
        return t;
    }
    static Test generateSpecialTest() {
        Test t;
        t.k = 80000;
        for (int i = 0; i < 100000; ++i)
            t.a.push_back(i);
        return t;
    }
    static Test generateSpecialTest2() {
        Test t;
        t.k = 80000;
        for (int i = 100000 - 1; i >= 0; --i) {
            t.a.push_back(i);
        }
        return t;
    }
    friend ostream& operator << (ostream& oss, const Test& t) {
        oss << t.a.size() << " " << t.k << endl;
        for (int i = 0; i < t.a.size(); ++i) {
            oss << t.a[i];
            if (i != t.a.size() -1) {
                oss << " ";
            }
        }
        oss << endl;
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
    tests.push_back(Test::generateSpecialTest2());
    for (int i = 0; i < tests.size(); ++i) {
        int testNumber = i + 1 + predefinedTestsCount;
        cout << "Printing test " << testNumber << " to the file" << endl;
        ostringstream path;
        path << "tests/" << std::setfill('0') << std::setw(3) << to_string(testNumber);
        ofstream out(path.str().c_str());
        out << tests[i];
    }
}
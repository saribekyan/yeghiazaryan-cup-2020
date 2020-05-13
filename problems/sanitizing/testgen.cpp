#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

const int testsCount = 30;

class Test {
    private: 
        int X;
    public:
        Test(int x): X(x) {}
    
    static Test generate(int testIndex, int testsCount) {
        srand(time(0));
        const int maxX = 100;
        int L = max(1, testIndex * maxX / testsCount);
        int R = min(maxX, (testIndex + 1) * maxX / testsCount);
        return Test(L + rand() % (R - L + 1));
    }
    friend ostream& operator << (ostream& oss, const Test& t) {
        oss << t.X << endl;
        return oss;
    }
};

int main() {
    system("rm -rf tests");
    system("mkdir tests");
    vector <Test> tests;
    tests.push_back(Test(10));
    tests.push_back(Test(15));
    for (int i = 3; tests.size() < testsCount; ++i) {
        cout << "Generating test " << i << endl;
        tests.push_back(Test::generate(i, testsCount));
    }
    for (int i = 0; i < tests.size(); ++i) {
        int testNumber = i + 1;
        cout << "Printing test " << testNumber << " to the file" << endl;
        ostringstream path;
        path << "tests/" << std::setfill('0') << std::setw(3) << to_string(testNumber);
        ofstream out(path.str().c_str());
        out << tests[i];
    }
}
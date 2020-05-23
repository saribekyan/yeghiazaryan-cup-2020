#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    const int rows = 1000000;
    const int cols = 500000;
    const string answer = "you_did_it.this_is_the_output.good_luck";
    int answerRow = (int)(rows * 0.22);
    ofstream out("big.txt");
    for (int i = 0; i < rows; ++i) {
        string s(cols / 2 + rand() % (cols/2), ' ');
        if (i == answerRow) {
            s = s + answer + s;
        }
        out << s << endl;
    }
}
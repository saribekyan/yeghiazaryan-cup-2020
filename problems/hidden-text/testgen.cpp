#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    const int tableSize = 100;
    const string hiddenText = "hayastan";
    int index = 0;
    vector <pair <int, int> > ans;
    srand(time(0));
    ofstream out("tests/001__.html");
    out << "<head>\n<style>\ntable, th, td\n{\nborder: 1px solid black;\n }\n th, td { \npadding: 1px;\n }\n</style>\n</head>" << endl;
    out << "<table borders>";
    for (int i = 0; i < tableSize; ++i) {
        out << "<tr>";
        for (int j = 0; j < tableSize; ++j) {
            char c = (char)('a' + rand() % 26);
            if (index < hiddenText.size() && c == hiddenText[index] && i > 15 && j > 10 && (ans.empty() || (ans.back().first < i - 5 && ans.back().second < j - 3))) {
                ans.push_back(make_pair(i, j));
                ++index;
            }
            out << "<td>" << c << "</td> ";
        }
        out << "</tr>" << endl;
    }
    out << "</table>";
    for (auto x: ans)
        cout << "(" << x.first + 1 << ", " << x.second + 1 << "); ";
}
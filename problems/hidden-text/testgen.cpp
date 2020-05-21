#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    const int tableSize = 255;
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
            if (index < hiddenText.size() && c == hiddenText[index] && i > 50 && j > 50 && (ans.empty() || (ans.back().first < i - 15 && ans.back().second < j - 7))) {
                ans.push_back(make_pair(i, j));
                ++index;
            }
            out << "<td>" << c << "</td> ";
        }
        out << "</tr>" << endl;
    }
    out << "</table>";
    for (auto x: ans)
        cout << x.first << " " << x.second << endl;
}
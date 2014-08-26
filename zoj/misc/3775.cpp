#include "cstdio"
#include "cstring"
#include "iostream"
#include "string"
using namespace std;

int main(int argc, char const *argv[])
{
    int T;
    cin >> T;
    string line;

    getline(cin, line);
    while (T--) {
        getline(cin, line);
        string out;
        for (int i=0; i<line.length(); i++) {
            if (line[i] == '_') {
                out += line;
            }
            else if (line[i] == '!') {
                out += "Hello, world!";
            }
        }

        puts(line == out ? "Yes" : "No");
    }
    return 0;
}
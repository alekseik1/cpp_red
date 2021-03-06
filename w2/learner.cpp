#include <algorithm>
#include <string>
#include <set>
#include <vector>

using namespace std;

class Learner {
private:
    set<string> _words;

public:
    int Learn(const vector<string>& words) {
        int newWords = 0;
        for (const auto& word : words) {
            if (_words.find(word) == _words.end()) {
                ++newWords;
                _words.insert(word);
            }
        }
        return newWords;
    }

    vector<string> KnownWords() {
        return {_words.begin(), _words.end()};
    }
};


using namespace std;
#include <iostream>
#include <sstream>
int main() {
    Learner learner;
    string line;
    while (getline(cin, line)) {
        vector<string> words;
        stringstream ss(line);
        string word;
        while (ss >> word) {
            words.push_back(word);
        }
        cout << learner.Learn(words) << "\n";
    }
    cout << "=== known words ===\n";
    for (auto word : learner.KnownWords()) {
        cout << word << "\n";
    }
}
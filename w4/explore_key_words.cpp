#include "test_runner.h"
//#include "profile.h"
//#include "paginator.h"

#include <future>
#include <list>
#include <map>
#include <string>
#include <sstream>
#include <utility>

using namespace std;

struct Stats {
  map<string, int> word_frequences;

  void operator += (const Stats& other) {
      for (const auto& pair : other.word_frequences) word_frequences[pair.first] += pair.second;
  }
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
    istringstream ss(line);
    Stats result;
    for (string s; ss >> s; ) {
        if (key_words.count(s) > 0) result.word_frequences[s] += 1;
    }
    return result;
}

Stats ExploreKeyWordsSingleThread(
  const set<string>& key_words, istream& input
) {
  Stats result;
  for (string line; getline(input, line); ) {
    result += ExploreLine(key_words, line);
  }
  return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    Stats result;
    vector<future<Stats>> v;
    list<stringstream> streams;
    const size_t threadLines = 5000;

    while (input) {
        stringstream ss;
        size_t i;
        for (i = 0; i < threadLines; ++i){
            string line;
            if (!getline(input, line)) break;
            ss << line << "\n";
        }
        if (i > 0) {
            streams.push_back(move(ss));
            v.push_back(async(ExploreKeyWordsSingleThread, ref(key_words), ref(streams.back())));
        }
    }
    for (auto &i : v) result += i.get();
    return result;
}

void TestBasic() {
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;
  ss << "this new yangle service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why yangle is the best IT company\n";
  ss << "yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

  const auto stats = ExploreKeyWords(key_words, ss);
  const map<string, int> expected = {
    {"yangle", 6},
    {"rocks", 2},
    {"sucks", 1}
  };
  ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestBasic);
}

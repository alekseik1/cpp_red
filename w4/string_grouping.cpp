#include "test_runner.h"

#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <utility>

using namespace std;

// Объявляем Group<String> для произвольного типа String
// синонимом vector<String>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор групп — vector<Group<String>>.
template <typename String>
using Group = vector<String>;

// Ещё один шаблонный синоним типа
// позволяет вместо громоздкого typename String::value_type
// использовать Char<String>
template <typename String>
using Char = typename String::value_type;

template <typename String>
using Key = String;

// Авторское решение
/**
template <typename String>
Key<String> getStringKey(const String& string) {
    String chars = string;
    sort(begin(chars), end(chars));
    chars.erase(unique(chars.begin(), chars.end()), chars.end());
    return chars;
}

template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
    map<Key<String>, Group<String>> groups_map;
    for (String& string : strings) {
        groups_map[ComputeStringKey(string)].push_back(move(string));
    }
    vector<Group<String>> groups;
    for (auto& [key, group] : groups_map) {
        groups.push_back(move(group));
    }
    return groups;
}
 */

template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
    // Напишите реализацию функции,
    // использовав не более 1 копирования каждого символа
    vector<bool> seen; seen.assign(strings.size(), false);
    vector<Group<String>> result;
    for (auto i=0; i < strings.size(); ++i) {
        if (seen.at(i)) continue;
        set<Char<String>> letters;
        for (auto tmp_it = strings.at(i).begin(); tmp_it != strings.at(i).end(); ++tmp_it)
            letters.insert(move(*tmp_it));
        Group<String> current_group;
        for (auto j=i; j < strings.size(); ++j) {
            if (seen.at(j)) continue;
            set<Char<String>> another_letters;
            for (auto tmp_it = strings.at(j).begin(); tmp_it != strings.at(j).end(); ++tmp_it)
                another_letters.insert(move(*tmp_it));
            if (another_letters == letters) {
                current_group.push_back(move(strings.at(j)));
                seen[j] = true;
            }
        }
        result.push_back(current_group);
    }
    return result;
}


void TestGroupingABC() {
    vector<string> strings = {"caab", "abc", "cccc", "bacc", "c"};
    auto groups = GroupHeavyStrings(strings);
    ASSERT_EQUAL(groups.size(), 2);
    sort(begin(groups), end(groups));  // Порядок групп не имеет значения
    ASSERT_EQUAL(groups[0], vector<string>({"caab", "abc", "bacc"}));
    ASSERT_EQUAL(groups[1], vector<string>({"cccc", "c"}));
}

void TestGroupingReal() {
    vector<string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
    auto groups = GroupHeavyStrings(strings);
    ASSERT_EQUAL(groups.size(), 4);
    sort(begin(groups), end(groups));  // Порядок групп не имеет значения
    ASSERT_EQUAL(groups[0], vector<string>({"laptop", "paloalto"}));
    ASSERT_EQUAL(groups[1], vector<string>({"law", "wall", "awl"}));
    ASSERT_EQUAL(groups[2], vector<string>({"port"}));
    ASSERT_EQUAL(groups[3], vector<string>({"top", "pot"}));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestGroupingABC);
    RUN_TEST(tr, TestGroupingReal);
    return 0;
}
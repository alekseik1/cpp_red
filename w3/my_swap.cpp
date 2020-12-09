#include <list>
#include <iostream>
#include <iterator>

using namespace std;

int main() {
    list<int> l{1, 2, 3, 4, 5, 6};
    auto it1 = next(l.begin(), 1);
    auto it2 = next(l.begin(), 4);

    list<int>& l2(l);
    auto next_ = next(it1);
    // two splice is enough though
    l.splice(it2, l2, it1, next(it1));
    l.splice(next_, l2, it2, next(it2));
    for (const auto item : l) cout << item << ' ';
    cout << endl;
}

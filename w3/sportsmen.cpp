#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    list<int> row;
    vector<list<int>::iterator> positions(100'001, row.end());
    for(auto i = 0; i < n; ++i) {
        int next_participant, stand_before;
        cin >> next_participant >> stand_before;
        positions[next_participant] = row.insert(
                positions[stand_before],
                next_participant
        );
    }
    for(const auto& item : row) {
        cout << item << '\n';
    }
}
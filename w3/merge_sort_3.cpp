#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>
#include <utility>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin < 2) return;
    vector<typename RandomIt::value_type> data(
            make_move_iterator(range_begin),
            make_move_iterator(range_end));
    auto step = data.size() / 3;
    MergeSort(data.begin(), data.begin() + step);
    MergeSort(data.begin() + step, data.begin() + 2 * step);
    vector<typename RandomIt::value_type> tmp;
    merge(
            make_move_iterator(data.begin()),
            make_move_iterator(data.begin() + step),
            make_move_iterator(data.begin() + step),
            make_move_iterator(data.begin() + 2 * step),
            back_inserter(tmp));
    MergeSort(data.begin() + 2 * step, data.end());
    merge(
           make_move_iterator(tmp.begin()),
           make_move_iterator(tmp.end()),
           make_move_iterator(data.begin() + 2*step),
           make_move_iterator(data.end()),
           range_begin);
}

void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}

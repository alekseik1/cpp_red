#include "test_runner.h"
#include <vector>
#include <future>
#include <numeric>
using namespace std;

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
  // Реализуйте эту функцию
  unsigned long TOTAL_THREADS = 4;
  vector<future<int>> futures;
  for (unsigned long thread = 0; thread < TOTAL_THREADS; ++thread) {
      futures.push_back(async([&matrix, thread, TOTAL_THREADS] {
          auto step = matrix.size() / TOTAL_THREADS;
          int result = 0;
          for (auto it = matrix.begin() + thread*step;
          it != (thread == TOTAL_THREADS - 1 ? matrix.end() : matrix.begin() + (thread+1)*step);
          ++it)
              result = accumulate(it->begin(), it->end(), result);
          return result;
      }));
  }
  int result = 0;
  for (auto& future : futures) result += future.get();
  return result;
}

void TestCalculateMatrixSum() {
  const vector<vector<int>> matrix = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestCalculateMatrixSum);
}

#include <doctest/doctest.h>

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
  os << "(";
  for (const auto& x : v) os << x << ", ";
  return os << ")";
}

template <typename ForwardIt, typename RandomIt>
void counting_sort(ForwardIt first, ForwardIt last, RandomIt out) {
  auto it = first;
  int min = *it;
  int max = *it;
  for (; it != last; ++it) {
    max = std::max(max, *it);
    min = std::min(min, *it);
  }

  const int offset = min;
  const int size = max - min + 1;

  int counts[size]{};
  for (auto it = first; it != last; ++it) ++counts[*it - offset];

  int sum = counts[0];
  counts[0] = 0;
  for (int i = 1; i < size; ++i) {
    int tmp = sum;
    sum += counts[i];
    counts[i] = tmp;
  }

  for (auto it = first; it != last; ++it) out[counts[*it - offset]++] = *it;
}

TEST_CASE("Counting Sort") {
  vector<int> in{0, 9, 5, 1, 5, -10, 2, 3, 5, 1, 5, 4, 7, 25};
  vector<int> out(size(in));

  auto test = in;
  sort(begin(test), end(test));
  cout << in << endl << test << endl;
  CHECK(is_sorted(begin(test), end(test)));

  counting_sort(begin(in), end(in), begin(out));
  cout << out << endl;
  CHECK(out == test);
}
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

void counting_sort(vector<int>::iterator first, vector<int>::iterator last,
                   vector<int>::iterator out) {
  constexpr int size = 10;
  int counts[size]{};
  for (auto it = first; it != last; ++it) ++counts[*it];

  int sum = counts[0];
  counts[0] = 0;
  for (int i = 1; i < size; ++i) {
    int tmp = counts[i];
    counts[i] = sum;
    sum += tmp;
  }

  for (auto it = first; it != last; ++it) out[counts[*it]++] = *it;
}

TEST_CASE("Counting Sort") {
  vector<int> in{9, 5, 1, 5, 2, 3, 5, 1, 5, 4, 7};
  vector<int> out(size(in));

  auto test = in;
  sort(begin(test), end(test));
  cout << in << endl << test << endl;
  CHECK(is_sorted(begin(test), end(test)));

  counting_sort(begin(in), end(in), begin(out));
  cout << out << endl;
  CHECK(out == test);
}
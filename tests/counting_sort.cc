#include <doctest/doctest.h>

#include <iostream>
#include <vector>

#include <counting_sort.h>

using namespace std;
using namespace linear_sort;

namespace {

template <typename T>
inline ostream& operator<<(ostream& os, const vector<T>& v) {
  os << "(";
  for (const auto& x : v) os << x << ", ";
  return os << ")";
}

template <typename T, typename U>
inline ostream& operator<<(ostream& os, const pair<T, U> p) {
  return os << "(" << p.first << "," << p.second << ")";
}

}  // namespace

TEST_CASE("Counting Sort for Integers") {
  vector<int> in{0, 9, 5, 1, 5, -10, 2, 3, 5, 1, 5, 4, 7, 25};
  decltype(in) out(size(in));

  auto test = in;
  std::sort(begin(test), end(test));
  cout << in << endl << test << endl;
  CHECK(is_sorted(begin(test), end(test)));

  counting_sort::sort(begin(in), end(in), begin(out));
  cout << out << endl;
  CHECK(out == test);
}

TEST_CASE("Counting Sort for Values with Integer Keys") {
  vector<pair<int, int>> in{{1, 1}, {3, 2}, {1, 3}, {3, 4}, {2, 5}, {0, 6}};
  decltype(in) out(size(in));

  auto test = in;
  std::sort(begin(test), end(test));
  cout << in << endl << test << endl;
  CHECK(is_sorted(begin(test), end(test)));

  // counting_sort::sort(begin(in), end(in), begin(out));
  counting_sort::sort(begin(in), end(in), begin(out),
                      [](auto x) { return x.first; });
  cout << out << endl;
  CHECK(out == test);
}
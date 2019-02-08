#include <doctest/doctest.h>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

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

template <typename T>
struct key {
  int operator()(const T& x) const noexcept { return x; }
};

template <typename T, typename U>
struct key<pair<T, U>> {
  int operator()(const pair<T, U>& x) const noexcept { return x.first; }
};

template <
    typename ForwardIt, typename RandomIt,
    typename KeyFunction = key<typename iterator_traits<ForwardIt>::value_type>>
void counting_sort(ForwardIt first, ForwardIt last, RandomIt out,
                   KeyFunction key = {}) {
  auto it = first;
  auto min = key(*it);
  auto max = key(*it);
  for (; it != last; ++it) {
    max = std::max(max, key(*it));
    min = std::min(min, key(*it));
  }

  const auto offset = min;
  const auto size = max - min + 1;

  int counts[size]{};  // this int is an independent implementation detail
  for (auto it = first; it != last; ++it) ++counts[key(*it) - offset];

  auto sum = counts[0];
  counts[0] = 0;
  for (int i = 1; i < static_cast<int>(size); ++i) {
    auto tmp = sum;
    sum += counts[i];
    counts[i] = tmp;
  }

  for (auto it = first; it != last; ++it)
    out[counts[key(*it) - offset]++] = *it;
}

TEST_CASE("Counting Sort for Integers") {
  vector<int> in{0, 9, 5, 1, 5, -10, 2, 3, 5, 1, 5, 4, 7, 25};
  decltype(in) out(size(in));

  auto test = in;
  sort(begin(test), end(test));
  cout << in << endl << test << endl;
  CHECK(is_sorted(begin(test), end(test)));

  counting_sort(begin(in), end(in), begin(out));
  cout << out << endl;
  CHECK(out == test);
}

TEST_CASE("Counting Sort for Values with Integer Keys") {
  vector<pair<int, int>> in{{1, 1}, {3, 2}, {1, 3}, {3, 4}, {2, 5}, {0, 6}};
  decltype(in) out(size(in));

  auto test = in;
  sort(begin(test), end(test));
  cout << in << endl << test << endl;
  CHECK(is_sorted(begin(test), end(test)));

  // counting_sort(begin(in), end(in), begin(out));
  counting_sort(begin(in), end(in), begin(out), [](auto x) { return x.first; });
  cout << out << endl;
  CHECK(out == test);
}
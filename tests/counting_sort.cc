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

  SUBCASE("Sorting with default key implementation") {
    counting_sort::sort(begin(in), end(in), begin(out));
    cout << out << endl;
    CHECK(out == test);
  }

  SUBCASE("Sorting with custom key function given by lambda expression") {
    counting_sort::sort(begin(in), end(in), begin(out),
                        [](auto x) { return x.first; });
    cout << out << endl;
    CHECK(out == test);
  }
}

SCENARIO(
    "Counting sort can be called with template arguments for minimal and "
    "maximal values.") {
  GIVEN("a sequence of integers") {
    vector<int> in{1, 9, 2, 8, 3, 7, 4, 6, 5};
    decltype(in) out(size(in));
    auto test = in;
    std::sort(begin(test), end(test));
    cout << in << endl << test << endl;

    WHEN(
        "the template arguments are describing correct minimal and maximal "
        "values") {
      counting_sort::sort<1, 9>(begin(in), end(in), begin(out));

      THEN(
          "the sequence will be sorted without computing minimal and maximal "
          "values") {
        cout << out << endl;
        CHECK(out == test);
      }
    }
  }
}

SCENARIO("Counting sort can be called with hints for minimum and maximum.") {
  GIVEN("a sequence of integers") {
    vector<int> in{1, 0, 0, 2, 1, 1, 2, 2, 0, 0, 0, 1};
    decltype(in) out(size(in));
    auto test = in;
    std::sort(begin(test), end(test));
    cout << in << endl << test << endl;

    WHEN(
        "hints for minimum and maximum are correct and called without key "
        "function") {
      counting_sort::sort(begin(in), end(in), begin(out), 0, 2);

      THEN(
          "the default key function is used and minimum and maximum are not "
          "computed") {
        cout << out << endl;
        CHECK(out == test);
      }
    }
  }

  GIVEN("a sequence of integer pairs") {
    vector<pair<int, int>> in{{0, 5}, {1, 4}, {2, 3}, {3, 2}, {4, 1}, {5, 0}};
    decltype(in) out(size(in));
    auto test = in;
    std::sort(begin(test), end(test),
              [](auto x, auto y) { return x.second <= y.second; });
    cout << in << endl << test << endl;

    WHEN("") {
      counting_sort::sort(begin(in), end(in), begin(out),
                          [](auto x) { return x.second; }, 0, 5);

      THEN("") {
        cout << out << endl;
        CHECK(out == test);
      }
    }
  }
}
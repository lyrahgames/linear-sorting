#ifndef LINEAR_SORTING_COUNTING_SORT_H_
#define LINEAR_SORTING_COUNTING_SORT_H_

#include <algorithm>
#include <iterator>

namespace linear_sort::counting_sort {

template <typename T>
struct key {
  int operator()(const T& x) const noexcept { return x; }
};

template <typename T, typename U>
struct key<std::pair<T, U>> {
  int operator()(const std::pair<T, U>& x) const noexcept { return x.first; }
};

template <typename ForwardIt, typename RandomIt,
          typename KeyFunction =
              key<typename std::iterator_traits<ForwardIt>::value_type>>
void sort(ForwardIt first, ForwardIt last, RandomIt out, KeyFunction key = {}) {
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

}  // namespace linear_sort::counting_sort

#endif  // LINEAR_SORTING_COUNTING_SORT_H_
#ifndef LINEAR_SORTING_COUNTING_SORT_H_
#define LINEAR_SORTING_COUNTING_SORT_H_

#include <algorithm>
#include <iterator>

namespace linear_sort {

template <typename T>
struct key {
  int operator()(const T& x) const noexcept { return x; }
};

template <typename T, typename U>
struct key<std::pair<T, U>> {
  int operator()(const std::pair<T, U>& x) const noexcept { return x.first; }
};

namespace counting_sort {

template <typename ForwardIt, typename RandomIt,
          typename KeyFunction =
              key<typename std::iterator_traits<ForwardIt>::value_type>>
void sort(
    ForwardIt first, ForwardIt last, RandomIt out, KeyFunction key,
    decltype(std::declval<KeyFunction>()(*std::declval<ForwardIt>())) min_hint,
    decltype(min_hint) max_hint) {
  const auto offset = min_hint;
  const auto size = max_hint - min_hint + 1;

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

template <typename ForwardIt, typename RandomIt,
          typename KeyFunction =
              key<typename std::iterator_traits<ForwardIt>::value_type>>
void sort(ForwardIt first, ForwardIt last, RandomIt out,
          decltype(KeyFunction{}(*std::declval<ForwardIt>())) min_hint,
          decltype(min_hint) max_hint) {
  sort(first, last, out, KeyFunction{}, min_hint, max_hint);
}

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

  sort(first, last, out, key, min, max);
}

template <int Min, int Max, typename ForwardIt, typename RandomIt,
          typename KeyFunction =
              key<typename std::iterator_traits<ForwardIt>::value_type>>
void sort(ForwardIt first, ForwardIt last, RandomIt out, KeyFunction key = {}) {
  constexpr auto offset = Min;
  constexpr auto size = Max - Min + 1;

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

}  // namespace counting_sort

namespace cycle_sort {

template <typename RandomIt,
          typename KeyFunction =
              key<typename std::iterator_traits<RandomIt>::value_type>>
void sort(RandomIt first, RandomIt last, KeyFunction key = {}) {
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

  for (int i = 1; i < static_cast<int>(size); ++i) counts[i] += counts[i - 1];

  const auto length = last - first;
  for (typename std::iterator_traits<RandomIt>::difference_type i = 0;
       i < length; ++i) {
    auto position = --counts[key(first[i]) - offset];
    if (position <= i) continue;
    auto value = first[i];
    do {
      std::swap(value, first[position]);
      position = --counts[key(value) - offset];
    } while (position > i);
    first[i] = value;
  }
}

}  // namespace cycle_sort

}  // namespace linear_sort

#endif  // LINEAR_SORTING_COUNTING_SORT_H_
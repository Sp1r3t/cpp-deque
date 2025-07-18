#pragma once

#include <deque>

template<class T, class Comp>
inline std::deque<T> Merge(const std::deque<T>& half1, const std::deque<T>& half2, const Comp& comparator) {
    if (half1.empty()) return half2;
    if (half2.empty()) return half1;

    std::deque<T> values;

    if(comparator(half1.front(), half2.front())) {
        values.push_back(half1.front());
        std::deque<T> new_arr(half1.begin() + 1, half1.end());
        auto rest = Merge(new_arr, half2, comparator);
        values.insert(values.end(), rest.begin(), rest.end());
    } else {
        values.push_back(half2.front());
        std::deque<T> new_arr(half2.begin() + 1, half2.end());
        auto rest = Merge(half1, new_arr, comparator);
        values.insert(values.end(), rest.begin(), rest.end());
    }

    return values;
}

template<class T, class Comp>
inline std::deque<T> MergeSort(const std::deque<T>& src, const Comp& comparator) {
    if (src.size() <= 1) {
        return src;
    }

    const size_t mid = src.size() / 2;
    const std::deque<T> left_sorted = MergeSort<T, Comp>({src.begin(), src.begin() + mid}, comparator);
    const std::deque<T> right_sorted = MergeSort<T, Comp>({src.begin() + mid, src.end()}, comparator);

    return Merge(left_sorted, right_sorted, comparator);
}

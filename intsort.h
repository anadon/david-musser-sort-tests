/*

Defines introsort, a new generic algorithm a new, hybrid sorting
algorithm, introsort (for ``introspective sort''), that behaves almost
exactly like median-of-3 quicksort for most inputs (and is just as
fast) but which is capable of detecting when partitioning is tending
toward quadratic behavior. By switching to heapsort in those
situations, introsort achieves the same O(N log N) time bound as
heapsort but is almost always faster than just using heapsort in the
first place.

*/

/*
 * Copyright (c) 1997 Rensselaer Polytechnic Institute
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Rensselaer Polytechnic Institute makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 */

#pragma once

#include <algorithm>

#include "recorder.h"

#define __stl_threshold 16

template <
  typename Size>
Size __lg(Size n) {
    Size k;
    for (k = Size(0); n != Size(1); n = n / Size(2)) ++k;
    return k;
}
/*
template <class _RandomAccessIterator>
_RandomAccessIterator
unguarded_partition_pivot(_RandomAccessIterator __first,
            _RandomAccessIterator __last)
{
  _RandomAccessIterator __mid = __first + (__last - __first) / 2;
  std::__move_median_to_first(__first, __mid, (__last - 1));
  return std::__unguarded_partition(__first + 1, __last, *__first);
}
//*/
template <class RandomAccessIterator, class Size, class Compare>
void
introsort_loop(
  RandomAccessIterator first,
  RandomAccessIterator last,
  Size depth_limit,
  Compare comp
){
  while (last - first > __stl_threshold) {
    if (depth_limit == 0) {
      partial_sort(first, last, last, comp);
      return;
    }
    RandomAccessIterator cut = std::__unguarded_partition_pivot(first, last, comp);
    introsort_loop(cut, last, depth_limit-1, comp);
    last = cut;
  }
}

template <
  typename RandomAccessIterator,
  typename Compare>
inline
void
introsort(
  RandomAccessIterator first,
  RandomAccessIterator last,
  Compare comp
){
    introsort_loop(first, last, __lg(last - first) * 2, comp);
    __final_insertion_sort(first, last, comp);
}

template <
  typename RandomAccessIterator>
inline void introsort(RandomAccessIterator first, RandomAccessIterator last)
{
    introsort(first, last, __gnu_cxx::__ops::__iter_less_iter());
}

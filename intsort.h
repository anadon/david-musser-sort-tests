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

template <class Size>
Size __lg(Size n) {
    Size k;
    for (k = 0; n != 1; n = n / 2) ++k;
    return k;
}

template <class RandomAccessIterator, class T, class Size>
void __introsort_loop(RandomAccessIterator first,
                      RandomAccessIterator last, T*,
                      Size depth_limit) {
    while (last - first > __stl_threshold) {
      if (depth_limit == 0) {
	partial_sort(first, last, last);
	return;
      }
      --depth_limit;
      RandomAccessIterator cut = __unguarded_partition
	(first, last, T(__median(*first, *(first + (last - first)/2),
				 *(last - 1))));
     __introsort_loop(cut, last, value_type(first), depth_limit);
     last = cut;
    }
}

template <class RandomAccessIterator, class T, class Size, class Compare>
void __introsort_loop(RandomAccessIterator first,
 		      RandomAccessIterator last, T*,
		      Size depth_limit, Compare comp) {
  while (last - first > __stl_threshold) {
    if (depth_limit == 0) {
      partial_sort(first, last, last, comp);
      return;
    }
    --depth_limit;
    RandomAccessIterator cut = __unguarded_partition
      (first, last, T(__median(*first, *(first + (last - first)/2),
			       *(last - 1), comp)), comp);
    __introsort_loop(cut, last, value_type(first), depth_limit, comp);
    last = cut;
  }
}

template <class RandomAccessIterator>
inline void introsort(RandomAccessIterator first, RandomAccessIterator last) {
    __introsort_loop(first, last, value_type(first), __lg(last - first) * 2);
    __final_insertion_sort(first, last);
}

template <class RandomAccessIterator, class Compare>
inline void introsort(RandomAccessIterator first, RandomAccessIterator last,
	  Compare comp) {
    __introsort_loop(first, last, value_type(first), __lg(last - first) * 2,
                     comp);
    __final_insertion_sort(first, last, comp);
}

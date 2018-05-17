/*

Defines class counter<T, ssize_t>, for use in measuring
the performance of certain STL generic algorithms.  Objects of this
class behave like those of type T with respect to assignments
and comparison operations, but the class also keeps counts of those
operations, using values of type ssize_t.

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

#include <iostream>

using std::endl;
using std::ostream;

template <class T>
class counter {
protected:
  T value;
public:
  static ssize_t assignments;
  static ssize_t comparisons;
  static ssize_t accesses;

  T base() const {++accesses; return value;}

  counter() : value(T()) { ++assignments; }

  explicit counter(const T& v) : value(v) { ++assignments; }

  counter(const counter<T>& x) : value(x.value) { ++assignments; }

  static ssize_t total() {
    return assignments + comparisons + accesses; }

  static void reset() {
    assignments = 0;
    comparisons = 0;
    accesses = 0;
  }

  static void report(ostream& o) {
    o << "Counter report:" << endl
      << "  Accesses:  "    << accesses << endl
      << "  Assignments:  " << assignments << endl
      << "  comparisons:   " << comparisons << endl;
  }

  friend bool operator<(const counter<T>& x,
                        const counter<T>& y)
  {
    ++counter<T>::comparisons;
    return x.value < y.value;
  }

  friend ostream& operator<<(ostream& o, const counter<T>& x) {
    return o << x.value;
  }

  counter<T>& operator=(const counter<T>& x) {
    ++assignments;
    value = x.value;
    return *this;
  }

  bool operator==(const counter<T>& x) const {
    ++comparisons;
    return value == x.value;
  }

  bool operator!=(const counter<T>& x) const {
    return !(value == x.value);
  }

  T operator* () const {
    return base();
  }
};

template <class T>
ssize_t counter<T>::assignments = 0;

template <class T>
ssize_t counter<T>::comparisons = 0;

template <class T>
ssize_t counter<T>::accesses = 0;

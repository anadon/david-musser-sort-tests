/*
Defines class iteration_counter<RandomAccessIterator, T, Reference,
Distance, DistanceBase>, for use in measuring the
performance of certain STL generic algorithms.  Objects of this class
behave like those of type RandomAccessIterator, but the class also
keeps counts of all iterator operations, using values of type
Counting.  Type T should be the value type of RandomAccessIterator,
and Reference should be the reference type of T.  Type Distance should
be a distance type for RandomAccessIterator, and Counting is the type
used for the counts.
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
#include <iterator>

using std::endl;
using std::iterator_traits;
using std::ostream;
using std::random_access_iterator_tag;

template <
  typename RandomAccessIterator,
  typename T,
  typename Reference,
  typename Distance>
class iteration_counter : public iterator_traits<RandomAccessIterator> {
  typedef iteration_counter<RandomAccessIterator, T, Reference, Distance> self;

  template <
    typename _RandomAccessIterator,
    typename _T,
    typename _Reference,
    typename _Distance>
  friend
  bool
  operator==(
    const iteration_counter<_RandomAccessIterator, _T, _Reference, _Distance>& x,
    const iteration_counter<_RandomAccessIterator, _T, _Reference, _Distance>& y);

  template <
    typename _RandomAccessIterator,
    typename _T,
    typename _Reference,
    typename _Distance>
  friend
  bool
  operator!=(
    const iteration_counter<_RandomAccessIterator, _T, _Reference, _Distance>& x,
    const iteration_counter<_RandomAccessIterator, _T, _Reference, _Distance>& y);

  template <
    typename _RandomAccessIterator,
    typename _T,
    typename _Reference,
    typename _Distance>
  friend
  bool
  operator<(
    const iteration_counter<_RandomAccessIterator, _T, _Reference, _Distance>& x,
    const iteration_counter<_RandomAccessIterator, _T, _Reference, _Distance>& y);

  template <
    typename _RandomAccessIterator,
    typename _T,
    typename _Reference,
    typename _Distance>
  friend
  self
  operator+(
    const iteration_counter<_RandomAccessIterator, _T, _Reference, _Distance>& x,
    const iteration_counter<_RandomAccessIterator, _T, _Reference, _Distance>& y);

  template <
    typename _RandomAccessIterator,
    typename _T,
    typename _Reference,
    typename _Distance>
  friend
  _Distance
  operator-(
    const iteration_counter<_RandomAccessIterator, _T, _Reference, _Distance>& x,
    const iteration_counter<_RandomAccessIterator, _T, _Reference, _Distance>& y);


protected:
  RandomAccessIterator current;
  ssize_t generation;
public:

  static ssize_t constructions;
  static ssize_t assignments;
  static ssize_t increments;
  static ssize_t dereferences;
  static ssize_t bigjumps;
  static ssize_t comparisons;
  static ssize_t max_generation;

  static
  void
  reset(
  ){
    constructions = 0;
    assignments = 0;
    increments = 0;
    dereferences = 0;
    bigjumps = 0;
    comparisons = 0;
    max_generation = 0;
  }

  static
  ssize_t
  total(
  ){
    return constructions + assignments + increments + dereferences + bigjumps +
           comparisons + max_generation;
  }

  static void report(ostream& o) {
    o << "Iterator stats: \n"
      << "  Constructions:  " << constructions << "\n"
      << "  Assignments:    " << assignments   << "\n"
      << "  Increments:     " << increments    << "\n"
      << "  Dereferences:   " << dereferences  << "\n"
      << "  Big jumps:      " << bigjumps      << "\n"
      << "  Differences     " << comparisons   << "\n"
      << "  TOTAL:          " << total() << endl;
    o << "  Maximum generation: " << max_generation << endl;
  }

  iteration_counter() : generation(0) { ++constructions; }


  iteration_counter(
    RandomAccessIterator x
  ){
    current = x;
    generation = 0;
    ++constructions;
  }

  iteration_counter(
    const self& c
  ){
    current = c.current;
    generation = c.generation + 1;
    ++constructions;
    if (generation > max_generation) {
      max_generation = generation;
    }
  }

  RandomAccessIterator
  base(
  ){
    return current;
  }

  Reference
  operator*(
  ) const {
    ++dereferences;
    return *current;
  }

  self&
  operator++(
  ){
      ++increments;
      ++current;
      return *this;
  }

  self&
  operator++(
    int
  ){
      self copy = *this;
      ++increments;
      ++current;
      return copy;
  }


  self&
  operator--(
  ){
    ++increments;
    --current;
    return *this;
  }


  self&
  operator--(
    int
  ){
    self copy = *this;
    ++increments;
    --current;
    return copy;
  }


  self
  operator+(
    const Distance& n
  ) const {
    self self_copy(*this);
    return self_copy += n;
  }


  self
  operator+(
    const ssize_t n
  ) const {
    self self_copy(*this);
    return self_copy += Distance(n);
  }


  self&
  operator+=(
    const ssize_t& n
  ) {
      return (*this) += Distance(n);
  }


  self&
  operator+=(
    const Distance& n
  ) {
      ++bigjumps;
      current += n;
      return *this;
  }


  self
  operator-(
    const Distance& n
  ) const {
    self self_copy(*this);
    return self_copy -= n;
  }


  self
  operator-(
    const ssize_t n
  ) const {
    self self_copy(*this);
    return self_copy -= Distance(n);
  }


  self&
  operator-=(
    const ssize_t n
  ) {
    return (*this) -= Distance(n);
  }


  self&
  operator-=(
    const Distance& n
  ) {
    ++bigjumps;
    current -= n;
    return *this;
  }


  Reference
  operator[](
    const ssize_t n
  ){
    return (*this)[Distance(n)];
  }


  Reference
  operator[](
    const Distance& n
  ){
    dereferences++;
    return *(*this + n);
  }

/*
  self&
  operator=(
    self& other
  ){
    other.current = current;
    other.generation = generation+1;
    return other;
  }
//*/

  friend
  ostream&
  operator << (
    ostream& o,
    const self& n
  ){
    return o << n.current;
  }
};

template <
  typename _RandomAccessIterator,
  typename _T,
  typename _Reference,
  typename _Distance>
bool
operator==(
  const iteration_counter<_RandomAccessIterator, _T, _Reference, _Distance>& x,
  const iteration_counter<_RandomAccessIterator, _T, _Reference, _Distance>& y
){
  ++iteration_counter<_RandomAccessIterator, _T, _Reference, _Distance>::comparisons;
  return x.current == y.current;
}

template <
  typename _RandomAccessIterator,
  typename _T,
  typename _Reference,
  typename _Distance>
bool
operator!=(
  const iteration_counter<_RandomAccessIterator, _T, _Reference, _Distance>& x,
  const iteration_counter<_RandomAccessIterator, _T, _Reference, _Distance>& y)
{
  return !(x == y);
}

template <
  typename _RandomAccessIterator,
  typename _T,
  typename _Reference,
  typename _Distance>
bool
operator<(
  const iteration_counter<_RandomAccessIterator, _T, _Reference, _Distance>& x,
  const iteration_counter<_RandomAccessIterator, _T, _Reference, _Distance>& y)
{
   ++iteration_counter<_RandomAccessIterator, _T, _Reference, _Distance>::comparisons;
   return x.current < y.current;
}

template <
  typename _RandomAccessIterator,
  typename _T,
  typename _Reference,
  typename _Distance>
bool
operator<=(
  const iteration_counter<_RandomAccessIterator, _T, _Reference, _Distance>& x,
  const iteration_counter<_RandomAccessIterator, _T, _Reference, _Distance>& y)
{
   ++iteration_counter<_RandomAccessIterator, _T, _Reference, _Distance>::comparisons;
   return x.current <= y.current;
}

template <
  typename _RandomAccessIterator,
  typename _T,
  typename _Reference,
  typename _Distance>
bool
operator>=(
  const iteration_counter<_RandomAccessIterator, _T, _Reference, _Distance>& x,
  const iteration_counter<_RandomAccessIterator, _T, _Reference, _Distance>& y)
{
   ++iteration_counter<_RandomAccessIterator, _T, _Reference, _Distance>::comparisons;
   return x.current >= y.current;
}

template <
  typename _RandomAccessIterator,
  typename _T,
  typename _Reference,
  typename _Distance>
bool
operator>(
  const iteration_counter<_RandomAccessIterator, _T, _Reference, _Distance>& x,
  const iteration_counter<_RandomAccessIterator, _T, _Reference, _Distance>& y)
{
   ++iteration_counter<_RandomAccessIterator, _T, _Reference, _Distance>::comparisons;
   return x.current > y.current;
}

template <
  typename _RandomAccessIterator,
  typename _T,
  typename _Reference,
  typename _Distance>
_Distance
operator-(
  const iteration_counter<_RandomAccessIterator, _T, _Reference, _Distance>& x,
  const iteration_counter<_RandomAccessIterator, _T, _Reference, _Distance>& y
){
  ++iteration_counter<_RandomAccessIterator, _T, _Reference, _Distance>::bigjumps;
  return _Distance(x.current - y.current);
}


template <
  typename _RandomAccessIterator,
  typename _T,
  typename _Reference,
  typename _Distance>
iteration_counter<_RandomAccessIterator, _T, _Reference, _Distance>
operator+(
  const iteration_counter<_RandomAccessIterator, _T, _Reference, _Distance>& n,
  const iteration_counter<_RandomAccessIterator, _T, _Reference, _Distance>& x
){
  ++iteration_counter<_RandomAccessIterator, _T, _Reference, _Distance>::bigjumps;
  return iteration_counter<_RandomAccessIterator, _T, _Reference, _Distance>(x.current + n.current);
}



template <
  typename RandomAccessIterator,
  typename T,
  typename Reference,
  typename Distance>
ssize_t iteration_counter<RandomAccessIterator, T, Reference, Distance>::constructions = 0;

template <
  typename RandomAccessIterator,
  typename T,
  typename Reference,
  typename Distance>
ssize_t iteration_counter<RandomAccessIterator, T, Reference, Distance>::assignments = 0;

template <
  typename RandomAccessIterator,
  typename T,
  typename Reference,
  typename Distance>
ssize_t iteration_counter<RandomAccessIterator, T, Reference, Distance>::increments = 0;

template <
  typename RandomAccessIterator,
  typename T,
  typename Reference,
  typename Distance>
ssize_t iteration_counter<RandomAccessIterator, T, Reference, Distance>::dereferences = 0;

template <
  typename RandomAccessIterator,
  typename T,
  typename Reference,
  typename Distance>
ssize_t iteration_counter<RandomAccessIterator, T, Reference, Distance>::bigjumps = 0;

template <
  typename RandomAccessIterator,
  typename T,
  typename Reference,
  typename Distance>
ssize_t iteration_counter<RandomAccessIterator, T, Reference, Distance>::comparisons = 0;

template <
  typename RandomAccessIterator,
  typename T,
  typename Reference,
  typename Distance>
ssize_t iteration_counter<RandomAccessIterator, T, Reference, Distance>::max_generation = 0;

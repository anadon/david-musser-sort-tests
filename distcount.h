/*

Defines class distance_counter<RandomAccessIterator, Distance,
ssize_t>, for use in measuring the performance of certain STL generic
algorithms.  Objects of this class behave like those of type Distance
(which should be a type capable of representing the difference between
iterators of type RandomAccessIterator) but the class also keeps
counts of all Distance operations, using values of type ssize_t.
Type RandomAccessIterator is used as the result type of certain
addition and subtraction operators, with the assumption that Distance
is its distance type.

*/

#pragma once

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

#include <iostream>
#include <utility>

using std::endl;
using std::ostream;
using std::pair;

template <class RandomAccessIterator, class Distance>
class distance_counter {


template <
  typename _RandomAccessIterator,
  typename _Distance>
friend
bool
operator==(
  const distance_counter<_RandomAccessIterator, _Distance>& x,
  const distance_counter<_RandomAccessIterator, _Distance>& y);


template <
  typename _RandomAccessIterator,
  typename _Distance>
friend
bool
operator<(
  const distance_counter<_RandomAccessIterator, _Distance>& x,
  const distance_counter<_RandomAccessIterator, _Distance>& y);


template <
  typename _RandomAccessIterator,
  typename _Distance>
friend
bool
operator<(
  const distance_counter<_RandomAccessIterator, _Distance>& x,
  const _Distance& y);


template <
  typename _RandomAccessIterator,
  typename _Distance>
friend
bool
operator<(
  const _Distance& x,
  const distance_counter<_RandomAccessIterator, _Distance>& y);


template <
  typename _RandomAccessIterator,
  typename _Distance>
friend
_RandomAccessIterator
operator+(
  _RandomAccessIterator i,
  const distance_counter<_RandomAccessIterator, _Distance>& x);


template <
  typename _RandomAccessIterator,
  typename _Distance>
friend
_RandomAccessIterator
operator+=(
  _RandomAccessIterator& i,
  const distance_counter<_RandomAccessIterator, _Distance>& x);


template <
  typename _RandomAccessIterator,
  typename _Distance>
friend
RandomAccessIterator
operator-(
  RandomAccessIterator i,
  const distance_counter<_RandomAccessIterator, _Distance>& x);


template <
  typename _RandomAccessIterator,
  typename _Distance>
friend
_RandomAccessIterator
operator-=(
  _RandomAccessIterator &i,
  const distance_counter<_RandomAccessIterator, _Distance>& x);


template <
  typename _RandomAccessIterator,
  typename _Distance>
friend
distance_counter<_RandomAccessIterator, _Distance>
operator-(
  const distance_counter<_RandomAccessIterator, _Distance>& x,
  const distance_counter<_RandomAccessIterator, _Distance>& y);


template <
  typename _RandomAccessIterator,
  typename _Distance>
friend
distance_counter<_RandomAccessIterator, _Distance>
operator+(
  const _Distance& n,
  const distance_counter<_RandomAccessIterator, _Distance>& x);


template <
  typename _RandomAccessIterator,
  typename _Distance>
friend
distance_counter<_RandomAccessIterator, _Distance>
operator*(
  const _Distance& n,
  const distance_counter<_RandomAccessIterator, _Distance>& x);

protected:
    Distance current;
    ssize_t generation;
public:
    static ssize_t constructions;
    static ssize_t copy_constructions;
    static ssize_t conversions;
    static ssize_t assignments;
    static ssize_t increments;
    static ssize_t additions;
    static ssize_t subtractions;
    static ssize_t multiplications;
    static ssize_t divisions;
    static ssize_t comparisons;
    static ssize_t max_generation;

    static void reset() {
      constructions = 0;
      copy_constructions = 0;
      conversions = 0;
      assignments = 0;
      increments = 0;
      additions = 0;
      subtractions = 0;
      multiplications = 0;
      divisions = 0;
      comparisons = 0;
      max_generation = 0;
    }

    static ssize_t total() {
      return constructions + copy_constructions + conversions
              + assignments + increments
              + additions + subtractions
              + multiplications + divisions
              + comparisons;
    }

    static void report(ostream& o) {
      o << "Distance stats: \n"
        << "  Constructions:   " << constructions << "\n"
        << "  Copies:          " << copy_constructions << "\n"
        << "  Conversions:     " << conversions   << "\n"
        << "  Assignments:     " << assignments   << "\n"
        << "  Increments:      " << increments    << "\n"
        << "  Additions:       " << additions     << "\n"
        << "  Subtractions:    " << subtractions  << "\n"
        << "  Multiplications: " << multiplications << "\n"
        << "  Divisions:       " << divisions     << "\n"
        << "  Equality comps:  " << comparisons << "\n"
        << "  TOTAL:           " << total() << "\n"
        << "  Maximum generation: " << max_generation << endl;
    }

    distance_counter() : generation(0) { ++constructions; }

    explicit
    distance_counter(
      const Distance& x
    ){
      current = x;
      generation = 0;
      ++conversions;
    }

    operator int() const { ++conversions; return current; }

    distance_counter(
      const distance_counter<RandomAccessIterator, Distance>& c
    ){
      current = c.current;
      generation = c.generation + 1;
      ++copy_constructions;
      if (generation > max_generation) {
        max_generation = generation;
      }
    }

    Distance base() const
    {
      return current;
    }

    distance_counter<RandomAccessIterator, Distance>&
    operator=(
      const distance_counter<RandomAccessIterator, Distance>& x
    ){
        ++assignments;
        current = x.current;
        return *this;
    }

    distance_counter<RandomAccessIterator, Distance>&
    operator++(){
        ++increments;
        ++current;
        return *this;
    }

    distance_counter<RandomAccessIterator, Distance>
    operator++(
      int
    ){
        distance_counter<RandomAccessIterator, Distance> tmp = *this;
        ++increments;
        ++current;
        return tmp;
    }

    distance_counter<RandomAccessIterator, Distance>&
    operator--(){
        ++increments;
        --current;
        return *this;
    }

    distance_counter<RandomAccessIterator, Distance>
    operator--(
      int
    ){
        distance_counter<RandomAccessIterator, Distance> tmp = *this;
        ++increments;
        --current;
        return tmp;
    }

    distance_counter<RandomAccessIterator, Distance>
    operator+(
      const distance_counter<RandomAccessIterator, Distance>& n
    ) const {
        distance_counter<RandomAccessIterator, Distance> tmp = *this;
        return tmp += n;
    }
//*
    distance_counter<RandomAccessIterator, Distance>
    operator+(
      const Distance& n
    ) const {
        distance_counter<RandomAccessIterator, Distance> tmp = *this;
        return tmp += n;
    }
//*/
    distance_counter<RandomAccessIterator, Distance>&
    operator+=(
      const distance_counter<RandomAccessIterator, Distance>& n
    ){
        ++additions;
        current += n.current;
        return *this;
    }
//*
    distance_counter<RandomAccessIterator, Distance>&
    operator+=(
      const Distance& n
    ){
        ++additions;
        current += n;
        return *this;
    }
//*/
    distance_counter<RandomAccessIterator, Distance>
    operator-(
      const distance_counter<RandomAccessIterator, Distance>& n
    ) const {
        distance_counter<RandomAccessIterator, Distance> tmp = *this;
        return tmp -= n;
    }
//*
    distance_counter<RandomAccessIterator, Distance>
    operator-(
      const Distance& n
    ) const {
        distance_counter<RandomAccessIterator, Distance> tmp = *this;
        return tmp -= n;
    }
//*/
    distance_counter<RandomAccessIterator, Distance>&
    operator-=(
      const distance_counter<RandomAccessIterator, Distance>& n
    ){
        ++subtractions;
        current -= n.current;
        return *this;
    }
//*
    distance_counter<RandomAccessIterator, Distance>&
    operator-=(
      const Distance& n
    ){
        ++subtractions;
        current -= n;
        return *this;
    }
//*/
    distance_counter<RandomAccessIterator, Distance>
    operator*(
      const distance_counter<RandomAccessIterator, Distance>& n
    ) const {
        distance_counter<RandomAccessIterator, Distance> tmp = *this;
        return tmp *= n;
    }
//*
    distance_counter<RandomAccessIterator, Distance>
    operator*(
      const Distance& n
    ) const {
        distance_counter<RandomAccessIterator, Distance> tmp = *this;
        return tmp *= n;
    }
//*/
    distance_counter<RandomAccessIterator, Distance>&
    operator*=(
      const distance_counter<RandomAccessIterator, Distance>& n
    ){
        ++multiplications;
        current *= n.current;
        return *this;
    }
//*
    distance_counter<RandomAccessIterator, Distance>&
    operator*=(
      const Distance& n
    ){
        ++multiplications;
        current *= n;
        return *this;
    }
//*/
    distance_counter<RandomAccessIterator, Distance>
    operator/(
      const distance_counter<RandomAccessIterator, Distance>& n
    ) const {
        distance_counter<RandomAccessIterator, Distance> tmp = *this;
        return tmp /= n;
    }
/*
    distance_counter<RandomAccessIterator, Distance>
    operator/(
      const Distance& n
    ) const {
        distance_counter<RandomAccessIterator, Distance> tmp = *this;
        return tmp /= n;
    }
//*/
    distance_counter<RandomAccessIterator, Distance>&
    operator/=(
      const distance_counter<RandomAccessIterator, Distance>& n)
    {
        ++divisions;
        current /= n.current;
        return *this;
    }
//*
    distance_counter<RandomAccessIterator, Distance>& operator/=(
      const Distance& n
    ){
        ++divisions;
        current /= n;
        return *this;
    }
//*/
};

template <
  typename _RandomAccessIterator,
  typename _Distance>
bool
operator==(
  const distance_counter<_RandomAccessIterator, _Distance>& x,
  const distance_counter<_RandomAccessIterator, _Distance>& y)
{
  ++distance_counter<_RandomAccessIterator, _Distance>::comparisons;
  return x.current == y.current;
}


template <
  typename _RandomAccessIterator,
  typename _Distance>
bool
operator<(
  const distance_counter<_RandomAccessIterator, _Distance>& x,
  const distance_counter<_RandomAccessIterator, _Distance>& y)
{
  ++distance_counter<_RandomAccessIterator, _Distance>::comparisons;
  return x.current < y.current;
}


template <
  typename _RandomAccessIterator,
  typename _Distance>
bool
operator<(
  const distance_counter<_RandomAccessIterator, _Distance>& x,
  const _Distance& y)
{
  ++distance_counter<_RandomAccessIterator, _Distance>::comparisons;
    return x.current < y;
}


template <
  typename _RandomAccessIterator,
  typename _Distance>
bool
operator<(
  const _Distance& x,
  const distance_counter<_RandomAccessIterator, _Distance>& y)
{
  ++distance_counter<_RandomAccessIterator, _Distance>::comparisons;
  return x < y.current;
}

template <
  typename _RandomAccessIterator,
  typename _Distance>
_RandomAccessIterator
operator+(
  _RandomAccessIterator i,
  const distance_counter<_RandomAccessIterator, _Distance>& x)
{
  return i + x.current;
}


template <
  typename _RandomAccessIterator,
  typename _Distance>
_RandomAccessIterator
operator+=(
  _RandomAccessIterator& i,
  const distance_counter<_RandomAccessIterator, _Distance>& x)
{
  return i += x.current;
}


template <
  typename _RandomAccessIterator,
  typename _Distance>
_RandomAccessIterator
operator-(
  _RandomAccessIterator i,
  const distance_counter<_RandomAccessIterator, _Distance>& x)
{
  return i - x.current;
}


template <
  typename _RandomAccessIterator,
  typename _Distance>
_RandomAccessIterator
operator-=(
  _RandomAccessIterator &i,
  const distance_counter<_RandomAccessIterator, _Distance>& x)
{
  return i -= x.current;
}


template <
  typename _RandomAccessIterator,
  typename _Distance>
distance_counter<_RandomAccessIterator, _Distance>
operator-(
  const distance_counter<_RandomAccessIterator, _Distance>& x,
  const distance_counter<_RandomAccessIterator, _Distance>& y)
{
  ++distance_counter<_RandomAccessIterator, _Distance>::subtractions;
  return distance_counter<_RandomAccessIterator, _Distance>(x.current - y.current);
}


template <
  typename _RandomAccessIterator,
  typename _Distance>
distance_counter<_RandomAccessIterator, _Distance>
operator+(
  const _Distance& n,
  const distance_counter<_RandomAccessIterator, _Distance>& x)
{
  return x + n;
}

template <
  typename _RandomAccessIterator,
  typename _Distance>
distance_counter<_RandomAccessIterator, _Distance>
operator*(
  const _Distance& n,
  const distance_counter<_RandomAccessIterator, _Distance>& x)
{
  return x * n;
}


template <
  typename RandomAccessIterator,
  typename Distance>
ssize_t distance_counter<RandomAccessIterator, Distance>::constructions = 0;
template <
  typename RandomAccessIterator,
  typename Distance>
ssize_t distance_counter<RandomAccessIterator, Distance>::copy_constructions = 0;
template <
  typename RandomAccessIterator,
  typename Distance>
ssize_t distance_counter<RandomAccessIterator, Distance>::conversions = 0;
template <
  typename RandomAccessIterator,
  typename Distance>
ssize_t distance_counter<RandomAccessIterator, Distance>::assignments = 0;
template <
  typename RandomAccessIterator,
  typename Distance>
ssize_t distance_counter<RandomAccessIterator, Distance>::increments = 0;
template <
  typename RandomAccessIterator,
  typename Distance>
ssize_t distance_counter<RandomAccessIterator, Distance>::additions = 0;
template <
  typename RandomAccessIterator,
  typename Distance>
ssize_t distance_counter<RandomAccessIterator, Distance>::subtractions = 0;
template <
  typename RandomAccessIterator,
  typename Distance>
ssize_t distance_counter<RandomAccessIterator, Distance>::multiplications = 0;
template <
  typename RandomAccessIterator,
  typename Distance>
ssize_t distance_counter<RandomAccessIterator, Distance>::divisions = 0;
template <
  typename RandomAccessIterator,
  typename Distance>
ssize_t distance_counter<RandomAccessIterator, Distance>::comparisons = 0;
template <
  typename RandomAccessIterator,
  typename Distance>
ssize_t distance_counter<RandomAccessIterator, Distance>::max_generation = 0;

/* The purpose of the following version of get_temporarary_buffer is to
   enable the STL stable_sort generic algorithms to work with
   distance_counter objects. */

/*
template <class T, class RandomAccessIterator, class Distance>
pair<T*,distance_counter<RandomAccessIterator, Distance> >
  get_temporary_buffer(distance_counter<RandomAccessIterator, Distance> len, T* p) {
    pair<T*, int> tmp = get_temporary_buffer((int)len, p);
    return pair<T*, distance_counter<RandomAccessIterator, Distance> >(tmp.first,
                    distance_counter<RandomAccessIterator, Distance>(tmp.second));
}
//*/

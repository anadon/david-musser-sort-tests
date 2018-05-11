/*

Defines class recorder<DataCounter, IterationCounter, DistanceCounter,
Timer, Counting> for recording operation counts as measured by objects
of types DataCounter, IterationCounter, and DistanceCounter; and
computing times as measured by objects of class Timer.  See also
recorder0.h, which defines a simpler recorder class capable only of
recording computing times.

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

#ifndef RECORDER_H
#define RECORDER_H

#include <vector.h>

template <class Container>
Container::value_type median(Container& c)
{
  Container::iterator midpoint = c.begin() + (c.end() - c.begin())/2;
  nth_element(c.begin(), midpoint, c.end());
  return *midpoint;
}

template <class DataCounter, class IterationCounter,
          class DistanceCounter, class Timer, class Counting>
class recorder
{
  vector<Counting> less_counts;
  vector<Counting> assign_counts;
  vector<Counting> iteration_counts;
  vector<Counting> distance_counts;
  vector<double> times;
public:
    void record(const Timer& t) {
    less_counts.push_back(DataCounter::less_comparisons);
    assign_counts.push_back(DataCounter::assignments);
    iteration_counts.push_back(IterationCounter::total());
    distance_counts.push_back(DistanceCounter::total());
    times.push_back(t.time());
    DataCounter::reset();
    IterationCounter::reset();
    DistanceCounter::reset();
  }
  void report(ostream& o, int repeat_factor)
  {
    double lesses = median(less_counts)/repeat_factor/1000.0;
    double assigns = median(assign_counts)/repeat_factor/1000.0;
    double iters = median(iteration_counts)/repeat_factor/1000.0;
    double dists = median(distance_counts)/repeat_factor/1000.0;
    o << setiosflags(ios::fixed) << setprecision(3) << setw(7)
      << median(times)/repeat_factor
      << setprecision(1) << setw(9) << lesses
      << setw(9) << assigns
      << setw(10) << iters
      << setw(10) << dists
      << setw(11) << lesses + assigns + iters + dists
      << "  ";
  }
  void reset() {
    less_counts.erase(less_counts.begin(), less_counts.end());
    assign_counts.erase(assign_counts.begin(), assign_counts.end());
    iteration_counts.erase(iteration_counts.begin(), iteration_counts.end());
    distance_counts.erase(distance_counts.begin(), distance_counts.end());
    times.erase(times.begin(), times.end());
  }
};

#endif

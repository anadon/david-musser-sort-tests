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

#pragma once

#include <iomanip>
#include <iostream>
#include <vector>

#include "counting.h"

using std::cout;
using std::ios;
using std::ostream;
using std::ofstream;
using std::setw;
using std::setprecision;
using std::vector;

template <
  typename value_type,
  template <typename, typename...> class Container>
value_type
median(
  Container<value_type>& c
){
  auto midpoint = c.begin() + (c.end() - c.begin())/2;
  nth_element(c.begin(), midpoint, c.end());
  return *midpoint;
}

template <
  typename DataCounter,
  typename IterationCounter,
  typename DistanceCounter>
class recorder
{

  vector<ssize_t> c_assignments;
  vector<ssize_t> c_comparisons;
  vector<ssize_t> c_accesses;

  vector<ssize_t> dc_constructions;
  vector<ssize_t> dc_copy_constructions;
  vector<ssize_t> dc_conversions;
  vector<ssize_t> dc_assignments;
  vector<ssize_t> dc_increments;
  vector<ssize_t> dc_additions;
  vector<ssize_t> dc_subtractions;
  vector<ssize_t> dc_multiplications;
  vector<ssize_t> dc_divisions;
  vector<ssize_t> dc_comparisons;
  vector<ssize_t> dc_max_generation;

  vector<ssize_t> ic_constructions;
  vector<ssize_t> ic_assignments;
  vector<ssize_t> ic_increments;
  vector<ssize_t> ic_dereferences;
  vector<ssize_t> ic_bigjumps;
  vector<ssize_t> ic_comparisons;
  vector<ssize_t> ic_max_generation;

  vector<double> times;
public:

  void
  record(
    const double time_taken
  ){

    c_assignments.push_back(DataCounter::assignments);
    c_comparisons.push_back(DataCounter::comparisons);
    c_accesses.push_back(DataCounter::accesses);

    dc_constructions.push_back(DistanceCounter::constructions);
    dc_copy_constructions.push_back(DistanceCounter::copy_constructions);
    dc_conversions.push_back(DistanceCounter::conversions);
    dc_assignments.push_back(DistanceCounter::assignments);
    dc_increments.push_back(DistanceCounter::increments);
    dc_additions.push_back(DistanceCounter::additions);
    dc_subtractions.push_back(DistanceCounter::subtractions);
    dc_multiplications.push_back(DistanceCounter::multiplications);
    dc_divisions.push_back(DistanceCounter::divisions);
    dc_comparisons.push_back(DistanceCounter::comparisons);
    dc_max_generation.push_back(DistanceCounter::max_generation);

    ic_constructions.push_back(IterationCounter::constructions);
    ic_assignments.push_back(IterationCounter::assignments);
    ic_increments.push_back(IterationCounter::increments);
    ic_dereferences.push_back(IterationCounter::dereferences);
    ic_bigjumps.push_back(IterationCounter::bigjumps);
    ic_comparisons.push_back(IterationCounter::comparisons);
    ic_max_generation.push_back(IterationCounter::max_generation);

    times.push_back(time_taken);

    DataCounter::reset();
    IterationCounter::reset();
    DistanceCounter::reset();
  }

  void
  report(
    std::ostream& o,
    int repeat_factor
  ){


    ssize_t data_assignments = median(c_assignments) / repeat_factor;
    ssize_t data_comparisons = median(c_comparisons) / repeat_factor;
    ssize_t data_accesses = median(c_accesses) / repeat_factor;

    ssize_t distance_constructions = median(dc_constructions) / repeat_factor;
    ssize_t distance_copy_constructions = median(dc_copy_constructions) / repeat_factor;
    ssize_t distance_conversions = median(dc_conversions) / repeat_factor;
    ssize_t distance_assignments = median(dc_assignments) / repeat_factor;
    ssize_t distance_increments = median(dc_increments) / repeat_factor;
    ssize_t distance_additions = median(dc_additions) / repeat_factor;
    ssize_t distance_subtractions = median(dc_subtractions) / repeat_factor;
    ssize_t distance_multiplications = median(dc_multiplications) / repeat_factor;
    ssize_t distance_divisions = median(dc_divisions) / repeat_factor;
    ssize_t distance_comparisons = median(dc_comparisons) / repeat_factor;
    ssize_t distance_max_generation = median(dc_max_generation) / repeat_factor;

    ssize_t iterator_constructions = median(ic_constructions) / repeat_factor;
    ssize_t iterator_assignments = median(ic_assignments) / repeat_factor;
    ssize_t iterator_increments = median(ic_increments) / repeat_factor;
    ssize_t iterator_dereferences = median(ic_dereferences) / repeat_factor;
    ssize_t iterator_bigjumps = median(ic_bigjumps) / repeat_factor;
    ssize_t iterator_comparisons = median(ic_comparisons) / repeat_factor;
    ssize_t iterator_max_generation = median(ic_max_generation) / repeat_factor;

    ssize_t total =
        data_assignments
      + data_comparisons
      + data_accesses
      + distance_constructions
      + distance_copy_constructions
      + distance_conversions
      + distance_assignments
      + distance_increments
      + distance_additions
      + distance_subtractions
      + distance_multiplications
      + distance_divisions
      + distance_comparisons
      + distance_max_generation
      + iterator_constructions
      + iterator_assignments
      + iterator_increments
      + iterator_dereferences
      + iterator_bigjumps
      + iterator_comparisons
      + iterator_max_generation;

    int width = 30;

    o << setiosflags(ios::fixed) << setprecision(3)
      << setw(width) << median(times)/repeat_factor
      << setw(width) << data_assignments
      << setw(width) << data_comparisons
      << setw(width) << data_accesses
      << setw(width) << distance_constructions
      << setw(width) << distance_copy_constructions
      << setw(width) << distance_conversions
      << setw(width) << distance_assignments
      << setw(width) << distance_increments
      << setw(width) << distance_additions
      << setw(width) << distance_subtractions
      << setw(width) << distance_multiplications
      << setw(width) << distance_divisions
      << setw(width) << distance_comparisons
      << setw(width) << distance_max_generation
      << setw(width) << iterator_constructions
      << setw(width) << iterator_assignments
      << setw(width) << iterator_increments
      << setw(width) << iterator_dereferences
      << setw(width) << iterator_bigjumps
      << setw(width) << iterator_comparisons
      << setw(width) << iterator_max_generation
      << setw(width) << total
      << endl;
  }

  void
  reset(
  ){
    c_assignments.clear();
    c_comparisons.clear();
    c_accesses.clear();
    dc_constructions.clear();
    dc_copy_constructions.clear();
    dc_conversions.clear();
    dc_assignments.clear();
    dc_increments.clear();
    dc_additions.clear();
    dc_subtractions.clear();
    dc_multiplications.clear();
    dc_divisions.clear();
    dc_comparisons.clear();
    dc_max_generation.clear();
    ic_constructions.clear();
    ic_assignments.clear();
    ic_increments.clear();
    ic_dereferences.clear();
    ic_bigjumps.clear();
    ic_comparisons.clear();
    ic_max_generation.clear();
    times.clear();
  }
};

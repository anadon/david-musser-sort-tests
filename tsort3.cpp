/* 

Example program for measuring the computing time of algorithms.
This program both measures times and counts operations; for
a simpler example of only measuring times, see tsort1.cpp.

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

#include <assert.h>
#include <algo.h>
#include <vector.h>
#include <deque.h>
#include <random.cpp>
#include <iostream.h>
#include <iomanip.h>
#include <fstream.h>
#include "intsort.h"
#include "timer.h"
#include "recorder.h"
#include "counter.h"
#include "itercount.h"
#include "distcount.h"

const int number_of_algorithms = 3;
const int number_of_trials = 7;

template <class Container, class Counting>
class counting {
public:
  typedef distance_counter<Container::iterator,
                           Container::difference_type, Counting>
          distance;

  typedef iteration_counter<Container::iterator, Container::value_type,
                            Container::value_type&, distance,
                            Container::difference_type, Counting>
          iterator;

  static void permute(Container& x)
  {
    random_shuffle(x.begin(), x.end());
  }

  static void algorithm(int k, Container& x)
  {
    switch (k) {
    case 0: introsort(iterator(x.begin()), 
                      iterator(x.end()));
      break;
    case 1: sort(iterator(x.begin()), 
                 iterator(x.end()));
      break;
    case 2: partial_sort(iterator(x.begin()), 
                         iterator(x.end()), 
                         iterator(x.end()));
    break;
    }
  }
  static const char* headings[number_of_algorithms];
};

template <class Container, class Counting>
const char* counting<Container, Counting>::headings[number_of_algorithms] =
  {" Introsort        ",
   " Quicksort        ",
   " Heapsort         "};

#include "experiment.h"

int main()
{
  experiment<vector<counter<int, double> >, double>::run();
}



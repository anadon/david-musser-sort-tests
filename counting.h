#pragma once

#include <algorithm>
#include <random>
#include <string>
#include <vector>

#include "distcount.h"
#include "itercount.h"
#include "intsort.h"

const int number_of_trials = 7;

static std::vector<std::string> headings =
  {" Introsort",
   " Heapsort"};

template <class Container>
class counting {
public:

  typedef distance_counter<
    typename Container::iterator,
    typename Container::difference_type> distance;

  typedef iteration_counter<
    typename Container::iterator,
    typename Container::value_type,
    typename Container::value_type&,
    distance> iterator;

  static void algorithm(int k, Container& x)
  {
    switch (k) {
    case 1: std::partial_sort(iterator(x.begin()),
                         iterator(x.end()),
                         iterator(x.end()));
    break;//*
    case 0: introsort(iterator(x.begin()),
                      iterator(x.end()));
      break;//*/
    /*case 0: std::sort(iterator(x.begin()),
                      iterator(x.end()));
      break;//*/
    }
  }

};

/*

Defines class experiment<Container, Counting> for carrying out an
experiment to measure the computing times and operation counts of
generic algorithms.  The user should already have defined a class
counting<Container, Counting> that defines appropriate specializations
of the distance_counter and iteration_counter types, and has member
functions permute, to be used to generate the input sequence for the
algorithms, and algorithm, which selects one of several algorithms for
measurement.  See tsort3.cpp for an example definition of the counting
class.

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

#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>

#include "counting.h"
#include "counter.h"
#include "itercount.h"
#include "recorder.h"
#include "timer.h"

using std::cin;
using std::cout;
using std::endl;
using std::flush;
using std::max;
using std::ofstream;
using std::ostream;
using std::setw;
using std::vector;

template <typename I, typename D, template <typename> class T, template<typename, typename...> class Container>
class experiment {
  typedef T<I> value_type;
  typedef typename counting<Container<value_type > >::iterator iterator;
  typedef typename counting<Container<value_type > >::distance distance;
public:

  static
  void
  run(
  ){

    const int factor = 1000;

    cout << "All sequence sizes are in multiples of " << factor << ".\n";
    cout << "Input the smallest sequence size: " << flush;
    int N1;
    cin >> N1;
    cout << "Input the largest sequence sizes: " << flush;
    int N2;
    cin >> N2;
/*
    cout << "Input random seed control (a positive integer): ";

    cin >> S;

    std::mt19937 generator (S);
    //*/

    ofstream ofs1("read.dat");
    ofstream ofs2("graph.dat");

    vector<recorder<value_type, iterator, distance> > stats(2);

    int repetitions = max(32/N1, 1);

    cout << std::endl;
    ofs1 << std::endl;

    for (int N0 = N1; N0 <= N2; N0 *= 2) {

      int N = N0 * factor;

      cout << "Size: " << setw(4) << N0 << "   Trials: " << flush;
      ofs1 << "Size: " << setw(4) << N0 << flush;
      ofs2 << setw(4) << N0 << flush;

      Container<value_type> x;
      for (int i = 0; i < N; ++i)
        x.push_back(T(i));

      int p, q;

      for (auto n = stats.begin(); n != stats.end(); ++n)
        n->reset();

      for (p = 0; p < number_of_trials; ++p) {
        std::random_shuffle(x.begin(), x.end());
        Container<value_type> y(x);
        Container<value_type>::value_type::assignments = 0;

        cout << p+1 << ":" << flush;

        for (size_t n = 0; n < stats.size(); ++n) {
          timer stop_watch = timer();
          stop_watch.start();
          for (q = 0; q < repetitions; ++q) {
            x = y;
            Container<value_type>::value_type::assignments -= N;
            counting<Container<value_type> >::algorithm(n, x);
          }
          stop_watch.stop();
          stats[n].record(stop_watch.lap_time());

          for (int z = 0; z < N; ++z)
            assert(x[z] == T(z));

          if (p == -1) {
            distance::report(cout);
            distance::report(ofs1);
          }
          cout << n+1 << flush;
        }
        cout << ", " << flush;
      }

      int width = 30;

      cout << endl
        << setw(width) << "Algorithm"
        << setw(width) << "Time"
        << setw(width) << "data assignments"
        << setw(width) << "data comparisons"
        << setw(width) << "data accesses"
        << setw(width) << "distance constructions"
        << setw(width) << "distance copy constructions"
        << setw(width) << "distance conversions"
        << setw(width) << "distance assignments"
        << setw(width) << "distance increments"
        << setw(width) << "distance additions"
        << setw(width) << "distance subtractions"
        << setw(width) << "distance multiplications"
        << setw(width) << "distance divisions"
        << setw(width) << "distance comparisons"
        << setw(width) << "distance max generation"
        << setw(width) << "iterater constructions"
        << setw(width) << "iterater assignments"
        << setw(width) << "iterater increments"
        << setw(width) << "iterater dereferences"
        << setw(width) << "iterater bigjumps"
        << setw(width) << "iterater comparisons"
        << setw(width) << "iterater max generation"
        << setw(width) << "total"
        << endl;

      ofs1 << endl
        << setw(width) << "Algorithm"
        << setw(width) << "Time"
        << setw(width) << "data assignments"
        << setw(width) << "data comparisons"
        << setw(width) << "data accesses"
        << setw(width) << "distance constructions"
        << setw(width) << "distance copy constructions"
        << setw(width) << "distance conversions"
        << setw(width) << "distance assignments"
        << setw(width) << "distance increments"
        << setw(width) << "distance additions"
        << setw(width) << "distance subtractions"
        << setw(width) << "distance multiplications"
        << setw(width) << "distance divisions"
        << setw(width) << "distance comparisons"
        << setw(width) << "distance max generation"
        << setw(width) << "iterater constructions"
        << setw(width) << "iterater assignments"
        << setw(width) << "iterater intrements"
        << setw(width) << "iterater dereferences"
        << setw(width) << "iterater bigjumps"
        << setw(width) << "iterater comparisons"
        << setw(width) << "iterater max generation"
        << setw(width) << "total"
        << endl;



      for (size_t n = 0; n < stats.size(); ++n) {
        cout << setw(width) << headings[n];
        stats[n].report(cout, repetitions);
        ofs1 << setw(width) << headings[n];
        stats[n].report(ofs1, repetitions);
        stats[n].report(ofs2, repetitions);
      }

      cout << endl;
      ofs1 << endl;
      ofs2 << endl;

      x.clear();

      if (repetitions > 1)
        repetitions /= 2;
    }
  }
};

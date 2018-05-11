/*

Defines class timer for measuring computing times. Implemented
using the standard clock function from time.h.


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

#include <chrono>
#include <vector>

using std::vector;

class timer {
protected:
  double start, finish;
public:
  vector<double> times;
  void record() {
    times.push_back(time());
  }
  void reset_vectors() {
    times.clear();
  }
  void restart() { start = clock(); }
  void stop() { finish = clock(); }
  double time() const { return ((double)(finish - start))/CLOCKS_PER_SEC; }
};

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

#include <vector>

#include "counter.h"
#include "experiment.h"


int main(){
  experiment<int, double, counter, vector >::run();
}

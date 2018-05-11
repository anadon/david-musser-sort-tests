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

#ifndef EXPERIMENT_H
#define EXPERIMENT_H

template <class Container, class Counting>
class experiment {
  typedef Container::value_type value_type;
  typedef counting<Container, Counting>::iterator iterator;
  typedef counting<Container, Counting>::distance distance;
public:
  static void run() 
  {
    int N0, N1, N2, N, S;

    const int factor = 1000;

    cout << "All sequence sizes are in multiples of " << factor << ".\n";
    cout << "Input the smallest and largest sequence sizes: " << flush;
    
    cin >> N1 >> N2;
    
    cout << "Input random seed control (a positive integer): ";
    
    cin >> S;
    
    while (S--)
      __long_random(10);

    ofstream ofs1("read.dat");
    ofstream ofs2("graph.dat");
    
    vector<recorder<value_type, iterator, distance, timer, Counting> >
      stats(number_of_algorithms);
    
    Container x, y;
    
    timer timer1;

    int repetitions = max(32/N1, 1);
    
    int n;
    
    cout << endl;
    ofs1 << endl;
    
    for (N0 = N1; N0 <= N2; N0 *= 2) {
      
      N = N0 * factor;
      
      cout << "Size: " << setw(4) << N0 << "   Trials: " << flush;
      ofs1 << "Size: " << setw(4) << N0 << flush;
      ofs2 << setw(4) << N0 << flush;
      
      for (int i = 0; i < N; ++i)
	x.push_back(i);
      
      int p, q;
      
      for (n = 0; n < number_of_algorithms; ++n)
	stats[n].reset();
      
      for (p = 0; p < number_of_trials; ++p) {
	
	counting<Container, Counting>::permute(x);
	y = x;
	value_type::assignments = 0;
	
	cout << p+1 << ":" << flush;
	
	for (n = 0; n < number_of_algorithms; ++n) {
	  timer1.restart();
	  for (q = 0; q < repetitions; ++q) {
	    x = y;
	    value_type::assignments -= N;
	    counting<Container, Counting>::algorithm(n, x);
	  }
	  timer1.stop();
	  
	  for (int z = 0; z < N; ++z)
	    assert(x[z] == z);
	  
	  if (p == -1) {
	    distance::report(cout);
	    distance::report(ofs1);
	  }
	  cout << n+1 << flush;
	  stats[n].record(timer1);
	}
	cout << ", " << flush;
      }

      cout << endl <<
	" Algorithm           Time    Comps   Assmts     Iters     Dists      Total  ";
      cout << endl;
      ofs1 << endl <<
	" Algorithm           Time    Comps   Assmts     Iters     Dists      Total  ";
      ofs1 << endl;
      
      for (n = 0; n < number_of_algorithms; ++n) {
	cout << counting<Container, Counting>::headings[n];
	stats[n].report(cout, repetitions);
	cout << endl;
	ofs1 << counting<Container, Counting>::headings[n];
	stats[n].report(ofs1, repetitions);
	ofs1 << endl;
	stats[n].report(ofs2, repetitions);
      }
      
      cout << endl;
      ofs1 << endl;
      ofs2 << endl;
      
      x.erase(x.begin(), x.end());
      
      if (repetitions > 1)
	repetitions /= 2;
    }
  }
};

#endif

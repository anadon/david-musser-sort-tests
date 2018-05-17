all: *.h *.cpp
	g++ -O3 --std=c++17 *.cpp
	#clang++ -g -Wall -Wextra -Wpedantic --std=c++17 *.cpp

clean:
	rm -f a.out *.dat

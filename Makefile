all: *.h *.cpp
	g++ -Wall -Wextra -Wpedantic --std=c++17 *.cpp

clean:
	rm -f a.out

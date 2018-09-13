.PHONY: all
all: doomedbags

doomedbags: doomedbags.o
	gcc -O2 -o doomedbags doomedbags.o

doomedbags.o: doomedbags.cpp
	gcc -c doomedbags.cpp -lstdc++

clean:
	rm doomedbags


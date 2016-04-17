.PHONY:run clean hw3

hw3:hw3.o
	g++ -std=c++11 -O3 hw3.o
hw3.o:hw3.cpp
	g++ -std=c++11 -O3 hw3.cpp -c 
run:
	./a.out
clean:
	rm -f hw3.o a.out

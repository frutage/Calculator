edit : main.o 
	g++ -o edit main.o
main.o : main.cpp struct.h calculate.h analyze.h
	g++ -c main.cpp
clean :
	-rm edit main.o

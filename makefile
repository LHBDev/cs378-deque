clean:
	rm TestDeque
TestDeque:
	g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall TestDeque.c++ -o TestDeque -lgtest -lgtest_main -lpthread
run:TestDeque
	./TestDeque
valgrind:TestDeque
	valgrind ./TestDeque
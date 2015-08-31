a.out: main.cpp perceptron.cpp sample.cpp
	${CXX} main.cpp perceptron.cpp sample.cpp -o a.out -std=c++11

run: a.out
	./a.out

a.out: main.cpp perceptron.cpp
	${CXX} main.cpp perceptron.cpp -o a.out -std=c++11

run: a.out
	./a.out

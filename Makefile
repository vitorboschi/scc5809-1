a.out: main.cpp perceptron.cpp sample.cpp ui.cpp
	${CXX} main.cpp perceptron.cpp ui.cpp sample.cpp -o a.out -std=c++11 `pkg-config --libs --cflags opencv`

run: a.out
	./a.out

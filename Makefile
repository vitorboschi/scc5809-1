a.out: main.cpp perceptron.cpp sample.cpp ui.cpp
	${CXX} main.cpp perceptron.cpp ui.cpp sample.cpp -o a.out -std=c++11 -DBUILD_UI `pkg-config --libs --cflags opencv`

no-opencv: main.cpp perceptron.cpp sample.cpp
	${CXX} main.cpp perceptron.cpp sample.cpp -o a.out -std=c++11

run: a.out
	./a.out

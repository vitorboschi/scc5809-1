#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include "sample.h"

class Perceptron {
	public:
	Perceptron(unsigned int inputSize);

	int train(const Sample& s, float delta, int expectedOutput);
	int evaluateData(const Sample& s);
	void resetWeights();

	private:
	int transferFunction(float input);
	float *m_weights;
	unsigned int m_inputSize;

};

#endif

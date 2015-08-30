#include "perceptron.h"
#include <cstring>

Perceptron::Perceptron(unsigned int inputSize) {
	m_weights = new float(inputSize+1); //account for bias weight
	m_inputSize = inputSize;
	resetWeights();
}

int Perceptron::train(const Sample& s, float delta, int expectedOutput) {
	int output = evaluateData(s);
	int error = expectedOutput - output;
	
	if (error == 0) {
		return 0;
	}

	//else, we've got the wrong answer, so we need to adjust weights
	for (int i=0;i<m_inputSize;i++) {
		m_weights[i] += error * s.data[i] * delta;
	}

	return error;
}

int Perceptron::evaluateData(const Sample& s) {
	float sum = 0.0f;

	for (int i=0;i<m_inputSize;i++) {
		sum += m_weights[i] * s.data[i];
	};
	
	//bias weight is the last element of the vector
	sum += m_weights[m_inputSize] * 1.0;
	
	return transferFunction(sum);
}

void Perceptron::resetWeights() {
	memset(m_weights, 0.0f, sizeof(float) * (m_inputSize+1));
}

int Perceptron::transferFunction(float input) {
	return (input > 0.0 ? 1 : -1);
}

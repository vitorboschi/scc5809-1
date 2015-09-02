#include "perceptron.h"
#include <cstring>

Perceptron::Perceptron(unsigned int inputSize) {
	m_weights = new float[inputSize+1]; // account for bias weight.
	m_inputSize = inputSize;

	// Start perceptron with all weights set to 0.
	resetWeights();
}

int Perceptron::train(const int input[], float delta, int expectedOutput) {
	int output = evaluateData(input);
	int error = expectedOutput - output;
	
	if (error == 0) {
		// Return 0 to indicate that there was no error.
		return 0;
	}

	// Else, we've got the wrong answer, so we need to adjust weights.
	for (int i=0;i<m_inputSize;i++) {
		m_weights[i] += error * input[i] * delta;
	}

	// Also adjust bias weight (which is the last element of the vector).
	m_weights[m_inputSize] += error * 1.0 * delta;

	// Return the error.
	return error;
}

int Perceptron::evaluateData(const int input[]) {
	float sum = 0.0f;

	// Add the inputs together, multiplied by their weight.
	for (int i=0;i<m_inputSize;i++) {
		sum += m_weights[i] * input[i];
	};
	
	// Also add the bias weight.
	sum += m_weights[m_inputSize] * 1.0;
	
	// Now we have the function parameter. Apply the transfer function.
	return transferFunction(sum);
}

void Perceptron::resetWeights() {
	memset(m_weights, 0.0f, sizeof(float) * (m_inputSize+1));
}

int Perceptron::transferFunction(float input) {
	// Step function:
	//
	//          |
	//        1 o---------
	// _________|___________
	//          |
	// ---------- -1
	//          |
	//

	return (input > 0.0 ? 1 : -1);
}

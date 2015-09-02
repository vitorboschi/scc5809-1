#ifndef PERCEPTRON_H
#define PERCEPTRON_H

class Perceptron {
	public:
	// Constructor.
	Perceptron(unsigned int inputSize);

	// Function to train the perceptron for a given input.
	int train(const int input[], float delta, int expectedOutput);

	// Evaluate the perceptron on a given input, with the current weights.
	int evaluateData(const int input[]);

	private:
	// Set all weights to 0.
	void resetWeights();

	// The transfer function.
	int transferFunction(float input);

	float *m_weights;
	unsigned int m_inputSize;
};

#endif

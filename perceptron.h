#ifndef PERCEPTRON_H
#define PERCEPTRON_H

class Perceptron {
	public:
	Perceptron(unsigned int inputSize);

	int train(const int input[], float delta, int expectedOutput);
	int evaluateData(const int input[]);
	void resetWeights();

	private:
	int transferFunction(float input);
	float *m_weights;
	unsigned int m_inputSize;

};

#endif

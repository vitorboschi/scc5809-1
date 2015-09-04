#include <iostream>
#include "sample.h"
#include "perceptron.h"
#ifdef BUILD_UI
#include "ui.h"
#endif

const int maxTrainingCycles = 100;
const float delta = 0.01;
const int maxSamples = 100;

Perceptron p(WIDTH * HEIGHT);

void trainPerceptron() {
	int currentCycle = 0;
	int cycleError = 100;

	Sample trainingData[maxSamples];

	// Read the samples from the training file.
	int nSamples = readSamples("trainingset.txt", trainingData, maxSamples);
	
	// Train the perceptron while there were errors in the previous cycle.
	while (cycleError > 0 && currentCycle < maxTrainingCycles) {
		std::cout << "Starting training cycle " << currentCycle << std::endl;
		currentCycle++;
		cycleError = 0;

		for (int i = 0; i < nSamples; i++) {
			// If the error returned from this Perceptron::train call is different
			// than 0, let's mark that there was an error in the cycle.
			if (p.train(trainingData[i].data, delta, trainingData[i].result)) {
				cycleError++;
			}
		}

		std::cout << "\tNumber of errors in cycle: " << cycleError << std::endl;
	}
	
	// No more errors happened during the last cycle, so the training was concluded.
	std::cout << std::endl << "Traning concluded with " << currentCycle << " cycles" << std::endl;	
}

void testPerceptron() {
	Sample testData[maxSamples];

	// Read samples from the test file.
	int nSamples = readSamples("testset.txt", testData, maxSamples);

	std::cout << std::endl << "Starting classification test" << std::endl;

	int errors = 0;
	for (int i = 0; i < nSamples; i++) {
		// Evaluate perceptron on this testcase.
		int value = p.evaluateData(testData[i].data);

		// Check if the value returned is the same as the expected one.
		if (value == testData[i].result) {
			// Expected Value
			std::cout << "Testcase #" << (i + 1) << " OK - correctly clasified" << std::endl;
		} else {
			std::cout << "Testcase #" << (i + 1) << " Error - incorrectly clasified" << std::endl;
			errors++;
		}
	}

	std::cout << std::endl;
	std::cout << "Correctly classifield " << (nSamples - errors) << "/" << nSamples << " test samples." << std::endl;
}

int main(int argc, char** argv) {
	// First train the perceptron using the training data supplied in trainingset.txt file.
	trainPerceptron();

	// Now run the trained perceptron on the testcases from the testset.txt file.
	testPerceptron();


#ifdef BUILD_UI
	// Start the user interface that allows users to draw a figure on a canvas to be classified by the perceptron.
	startUI();
#endif

	return 0;
}



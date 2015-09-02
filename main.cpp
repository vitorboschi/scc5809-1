#include <iostream>
#include "sample.h"
#include "perceptron.h"
#include "ui.h"


const int maxTrainingCycles = 100;
const float delta = 0.01;
const int maxSamples = 100;

Perceptron p(WIDTH * HEIGHT);

void trainPerceptron() {
//	Perceptron p(WIDTH * HEIGHT);
	int currentCycle = 0;
	int cycleError = 100;

	Sample trainingData[maxSamples];
	int nSamples = readSamples("trainingset.txt", trainingData, maxSamples);
	
	while (cycleError > 0 && currentCycle < maxTrainingCycles) {
		std::cout << "Starting training cycle " << currentCycle << std::endl;
		currentCycle++;
		cycleError = 0;
		for (int i=0;i<nSamples;i++) {
			if (p.train(trainingData[i].data, delta, trainingData[i].result)) {
				cycleError++;
			}
		}
		std::cout << "\tNumber of errors in cycle: " << cycleError << std::endl;
	}
	
	std::cout << std::endl << "Traning concluded with " << currentCycle << " cycles" << std::endl;	
}

void testPerceptron() {
	//Perceptron p(WIDTH * HEIGHT);
	Sample testData[maxSamples];
	int nSamples = readSamples("testset.txt", testData, maxSamples);

	std::cout << std::endl << "Starting classification test" << std::endl;

	int errors = 0;
	for (int i = 0; i < nSamples; i++) {
		int value = p.evaluateData(testData[i].data);

		if (value == testData[i].result) {
			// Expected Value
			std::cout << "Test #" << (i + 1) << " correctly clasified" << std::endl;
		} else {
			std::cout << "Test #" << (i + 1) << " incorrectly clasified" << std::endl;
			errors++;
		}
	}

	std::cout << "Correctly classifield " << (nSamples - errors) << "/" << nSamples << " test samples." << std::endl;
}

int main(int argc, char** argv) {
	trainPerceptron();
	testPerceptron();
	startUI();
	return 0;
}



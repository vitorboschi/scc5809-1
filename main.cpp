#include <iostream>
#include "trainingData.h"
#include "perceptron.h"

const int maxTrainingCycles = 100;
const float delta = 0.01;

int main(int argc, char** argv) {
	Perceptron p(64);
	int currentCycle = 0;
	int cycleError = 100;

	while (cycleError > 0 && currentCycle < maxTrainingCycles) {
		std::cout << "Starting training cycle " << currentCycle << std::endl;
		currentCycle++;
		cycleError = 0;
		for (int i=0;i<nSamples;i++) {
			if (p.train(trainingData[i].input, delta, trainingData[i].result)) {
				cycleError++;
			}
		}
		std::cout << "\tNumber of errors in cycle: " << cycleError << std::endl;
	}
	
	std::cout << std::endl << "Traning concluded with " << currentCycle << " cycles" << std::endl;
	return 0;
}

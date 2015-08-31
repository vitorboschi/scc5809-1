#include <iostream>
#include "sample.h"
#include "perceptron.h"

const int maxTrainingCycles = 100;
const float delta = 0.01;
const int maxSamples = 100;

int main(int argc, char** argv) {
	Perceptron p(WIDTH * HEIGHT);
	
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
	return 0;
}



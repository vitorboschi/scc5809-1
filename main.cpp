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
			cycleError += p.train(trainingData[i].input, delta, trainingData[i].result);
		}
		std::cout << "\tCycle error: " << cycleError << std::endl;
	}
	
	std::cout << "Traning concluded" << std::endl;
	return 0;
}

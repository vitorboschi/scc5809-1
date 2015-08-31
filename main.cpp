#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

#include "trainingData.h"
#include "perceptron.h"

const int maxTrainingCycles = 100;
const float delta = 0.01;

#define WIDTH 8
#define HEIGHT 8

int readSamples(const char * fileName, TrainingSample* samples, int maxSamples) {
	int nSamples = 0;
	std::ifstream file(fileName);

	std::string line;
	int result;

	while (nSamples < maxSamples) {
		if (!std::getline(file, line)) {
			break;
		}

		if (line.compare("") == 0) {
			// empty line
			continue;
		}

		result = stoi(line);
		printf("result is %d\n", result);

		for (int i = 0; i < HEIGHT; i++) {
			if (!std::getline(file, line) ||
				line.size() < WIDTH) {
				std::cout << "Input #" << (nSamples + 1) << " is malformed on line " << (i + 1) << "." << std::endl;
				exit(0);
			}
			
			for (int j = 0; j < WIDTH; j++) {
				samples[nSamples].input[i * WIDTH + j] = 
				  line[j] == '*' ? 1 : 0;
			}
		}

		nSamples++;
	}

	return nSamples;
}




int main(int argc, char** argv) {
	Perceptron p(64);
	int currentCycle = 0;
	int cycleError = 100;

	TrainingSample k[100];

	printf("\n\nnum Samples: %d\n\n", readSamples("trainingset.txt", k, 10));

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



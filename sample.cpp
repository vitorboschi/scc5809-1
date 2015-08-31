#include <iostream>
#include <fstream>
#include <string>
#include "sample.h"

int readSamples(const char * fileName, Sample* samples, int maxSamples) {
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

		// The expected result, +1 for A, or -1 for V
		samples[nSamples].result = stoi(line);

		for (int i = 0; i < HEIGHT; i++) {
			if (!std::getline(file, line) ||
				line.size() < WIDTH) {
				std::cout << "Input #" << (nSamples + 1) << " is malformed on line " << (i + 1) << "." << std::endl;
				exit(0);
			}
			
			for (int j = 0; j < WIDTH; j++) {
				samples[nSamples].data[i * WIDTH + j] = 
				  line[j] == '*' ? 1 : 0;
			}
		}

		nSamples++;
	}

	return nSamples;
}

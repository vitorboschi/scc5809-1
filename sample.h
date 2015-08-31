#ifndef TRAINING_SAMPLE_H
#define TRAINING_SAMPLE_H

const int WIDTH = 8;
const int HEIGHT = 8;


class Sample {                                                                        
public:
	int result;                                                               
	int data[WIDTH * HEIGHT];

	void display();
};

int readSamples(const char * fileName, Sample* samples, int maxSamples);

#endif

#ifndef TRAINING_SAMPLE_H
#define TRAINING_SAMPLE_H

const int WIDTH = 8;
const int HEIGHT = 8;

typedef struct {
	int result;
	int data[WIDTH * HEIGHT];
} Sample;

int readSamples(const char * fileName, Sample* samples, int maxSamples);

#endif

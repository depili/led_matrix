#include <Arduino.h>
#include <led_matrix.h>

#define CS_PIN 10
#define MODULES 8

static LedMatrix *matrix;

void setup(void) {
	matrix = new LedMatrix(CS_PIN, MODULES);
	matrix->write();
}

void loop(void) {
	matrix->fontTest();
}

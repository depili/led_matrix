#ifndef led_matrix_h
#define led_matrix_h

#include <Arduino.h>
#include <SPI.h>

#define SPI_SPEED 1000000

// The opcodes for the MAX7221 and MAX7219
#define OP_NOOP         0
#define OP_DIGIT0       1
#define OP_DIGIT1       2
#define OP_DIGIT2       3
#define OP_DIGIT3       4
#define OP_DIGIT4       5
#define OP_DIGIT5       6
#define OP_DIGIT6       7
#define OP_DIGIT7       8
#define OP_DECODEMODE   9
#define OP_INTENSITY   10
#define OP_SCANLIMIT   11
#define OP_SHUTDOWN    12
#define OP_DISPLAYTEST 15

extern const uint8_t ss8_font[96][5] PROGMEM;
extern const uint8_t charlist[96][2] PROGMEM;

class LedMatrix {
	public:
		LedMatrix(byte cspin, byte displays);
		void sendOpcode(byte opcode, byte data=0);
		void write(void);
		void fill(void);
		void fontTest(void);
	private:
		byte cspin;
		byte displays;
		byte *bitmap;
};

#endif

#include <Arduino.h>
#include <SPI.h>
#include <avr/pgmspace.h>
#include <led_matrix.h>

LedMatrix::LedMatrix(byte cspin, byte displays) {
	LedMatrix::displays = displays;
	LedMatrix::cspin = cspin;
	SPI.begin();
	SPI.beginTransaction(SPISettings(SPI_SPEED, MSBFIRST, SPI_MODE0));
	pinMode(cspin, OUTPUT);

	// Initialize the display modules
	sendOpcode(OP_DISPLAYTEST,0);
	sendOpcode(OP_SCANLIMIT, 7);
	sendOpcode(OP_DECODEMODE, 0);
	sendOpcode(OP_SHUTDOWN, 1);
	sendOpcode(OP_INTENSITY, 4);

	LedMatrix::bitmap = (byte*) malloc(displays*8);
	for (byte display = 0; display < displays * 8; display++) {
		bitmap[display] = 0;
	}
}

void LedMatrix::sendOpcode(byte opcode, byte data) {
	digitalWrite(cspin, LOW);
	
	for (byte i = 0; i < displays; i++) {
		SPI.transfer(opcode);
		SPI.transfer(data);
	};
	//delayMicroseconds(1);
	digitalWrite(cspin, HIGH);
}

void LedMatrix::write(void) {
	for ( byte row = OP_DIGIT0; row <= OP_DIGIT7; row++ ) {
		digitalWrite(cspin,LOW);
		for (byte i = 0; i < displays; i++) {
			SPI.transfer(row);
			SPI.transfer(bitmap[(i*8) + (8-row) ]);
		}
		digitalWrite(cspin,HIGH);
	}
}

void LedMatrix::fill(void) {
	for (byte i = 0; i < displays * 8; i++) {
		bitmap[i] = 1;
		write();
		delay(50);
	}
	for (byte i = 0; i < displays * 8; i++) {
		bitmap[i] = 0;
		write();
		delay(50);
	}
}

void LedMatrix::fontTest(void) {
	for (uint16_t i = 0; i < sizeof(ss8_font) - (displays*8); i++) {
		for (uint8_t j = 0; j < displays * 8; j++) {
			bitmap[j] = pgm_read_byte(&ss8_font[(i+j)/5][(i+j)%5] );
		}
		write();
		delay(50);
	}
	delay(500);
}

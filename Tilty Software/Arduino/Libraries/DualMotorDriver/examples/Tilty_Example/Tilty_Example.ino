#include "DualMotorDriver.h"
#include "i2c_t3.h"

void setup() {
	Wire.begin(I2C_MASTER, 0, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_400);
	pinMode(13, OUTPUT);
	
	setup1819();
}

void loop() {
	/*
	scanAll();
	delay(1000);
	*/
	setup1819();
	Serial.println("Setup for 3v3 bus (18 & 19)");
	Serial.print("16 Config: ");
	Serial.println(CORE_PIN16_CONFIG);
	Serial.print("17 Config: ");
	Serial.println(CORE_PIN17_CONFIG);
	Serial.print("18 Config: ");
	Serial.println(CORE_PIN18_CONFIG);
	Serial.print("19 Config: ");
	Serial.println(CORE_PIN19_CONFIG);
	Serial.println();
	
	setup1617();
	Serial.println("Setup for 5v bus (16 & 17)");
	Serial.print("16 Config: ");
	Serial.println(CORE_PIN16_CONFIG);
	Serial.print("17 Config: ");
	Serial.println(CORE_PIN17_CONFIG);
	Serial.print("18 Config: ");
	Serial.println(CORE_PIN18_CONFIG);
	Serial.print("19 Config: ");
	Serial.println(CORE_PIN19_CONFIG);
	Serial.println();
	Serial.println();
	
	delay(1000);
}

void setup1617() {
    CORE_PIN16_CONFIG = (PORT_PCR_MUX(2)|PORT_PCR_ODE|PORT_PCR_SRE|PORT_PCR_DSE);
    CORE_PIN17_CONFIG = (PORT_PCR_MUX(2)|PORT_PCR_ODE|PORT_PCR_SRE|PORT_PCR_DSE);
    *portModeRegister(18) = 0; // input
    CORE_PIN18_CONFIG = PORT_PCR_MUX(1);
    *portModeRegister(19) = 0; // input
    CORE_PIN19_CONFIG = PORT_PCR_MUX(1);
}

void setup1819() {
    CORE_PIN18_CONFIG = (PORT_PCR_MUX(2)|PORT_PCR_ODE|PORT_PCR_SRE|PORT_PCR_DSE);
    CORE_PIN19_CONFIG = (PORT_PCR_MUX(2)|PORT_PCR_ODE|PORT_PCR_SRE|PORT_PCR_DSE);
    *portModeRegister(16) = 0; // input
    CORE_PIN16_CONFIG = PORT_PCR_MUX(1);
    *portModeRegister(17) = 0; // input
    CORE_PIN17_CONFIG = PORT_PCR_MUX(1);
}

void setupBoth() {
    CORE_PIN18_CONFIG = (PORT_PCR_MUX(2)|PORT_PCR_ODE|PORT_PCR_SRE|PORT_PCR_DSE);
    CORE_PIN19_CONFIG = (PORT_PCR_MUX(2)|PORT_PCR_ODE|PORT_PCR_SRE|PORT_PCR_DSE);
	
    CORE_PIN16_CONFIG = (PORT_PCR_MUX(2)|PORT_PCR_ODE|PORT_PCR_SRE|PORT_PCR_DSE);
    CORE_PIN17_CONFIG = (PORT_PCR_MUX(2)|PORT_PCR_ODE|PORT_PCR_SRE|PORT_PCR_DSE);
}

void scanAll() {
	setup1617();
	Serial.println("I2C Devices on 5v Line:");
	for (int i = 1; i < 128; i++) {
		Wire.beginTransmission(i);
		if (!Wire.endTransmission()) {
			Serial.print(i < 16 ? "I2C Device found at: 0x0" : "I2C Device found at: 0x");
			Serial.println(i, HEX);
		}
	}	
	Serial.println();

	Serial.println("I2C Devices on 3v3 line:");
	setup1819();
	for (int i = 1; i < 128; i++) {
		Wire.beginTransmission(i);
		if (!Wire.endTransmission()) {
			Serial.print(i < 16 ? "I2C Device found at: 0x0" : "I2C Device found at: 0x");
			Serial.println(i, HEX);
		}
	}
	Serial.println();
	
	Serial.println("I2C Devices on both lines:");
	setupBoth();
	for (int i = 1; i < 128; i++) {
		Wire.beginTransmission(i);
		if (!Wire.endTransmission()) {
			Serial.print(i < 16 ? "I2C Device found at: 0x0" : "I2C Device found at: 0x");
			Serial.println(i, HEX);
		}
	}
	Serial.println("\n");
}
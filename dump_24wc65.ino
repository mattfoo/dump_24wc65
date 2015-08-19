/*
* I2C EEPROM sketch
* this version for 24LC128
*/

#include <Wire.h>

const byte EEPROM_ID = 0x50;
const int  MAX_BYTES = 8192;

void setup() {
    int       theValue;
    int       lineCount = 0;
    char      textString[16];
    char      asciiDump[24];

    Serial.begin(57600);
    Wire.begin();

    Serial.print("Reading "); Serial.print(MAX_BYTES); Serial.println(" from EEPROM...");

    for (unsigned long  i=0; i < MAX_BYTES; i++) {

        int theValue = I2CEEPROM_Read(i);

        if ( lineCount == 0 ) {
            sprintf(textString, "%04X - ", i);
            Serial.print(textString);
        }

        if ( lineCount < 16 ) {
            sprintf(textString, "%02X ", theValue);
            Serial.print(textString);
            if ((theValue >= 0x20) && (theValue < 0x7f)) {
                asciiDump[lineCount]  = theValue;
            } else {
                asciiDump[lineCount]  = '.';
            }
        }

        lineCount++;

        if ( lineCount >= 16 ) {
            lineCount     = 0;
            // asciiDump[16] = 0;
            Serial.print(textString);
            Serial.println(asciiDump);
        }

    }

    Serial.print("Finish reading "); Serial.print(MAX_BYTES); Serial.println(" bytes from EEPROM...");

}

void loop() { }

// This function is similar to EEPROM.read()
byte I2CEEPROM_Read(unsigned long address ) {
    byte data;
    Wire.beginTransmission(EEPROM_ID);
    Wire.write((int)highByte(address) );
    Wire.write((int)lowByte(address) );
    Wire.endTransmission();
    Wire.requestFrom(EEPROM_ID,(byte)1);
    
    // while(Wire.available() == 0) // wait for data;
    data = Wire.read();
    return data;
}

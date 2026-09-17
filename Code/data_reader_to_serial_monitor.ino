#include <SPI.h>
#include <SD.h>

const int chipSelect = 10;
File myFile;

// select the filename you want to read from the sd card
const char filename[] = "data001.csv";


// this code print the whole content of the datafile in the *serial monitor* in the Arduino IDE
void setup() {
  Serial.begin(9600);
  while (!Serial) { ; }

  SD.begin(chipSelect);
  myFile = SD.open(filename);
  if (myFile) {
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    myFile.close();
  }
}

void loop() {}
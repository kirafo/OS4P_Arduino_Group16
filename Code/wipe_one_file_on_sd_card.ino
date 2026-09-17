#include <SPI.h>
#include <SD.h>

const int chipSelect = 10;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect (needed for native USB boards)
  }

  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println(" failed!");
    while (1); // Halt execution if initialization fails
  }
  Serial.println(" done.");


// CHANGE THE NAME of the file you want to delete HERE: 
  if (SD.exists("data001.csv")) {
    Serial.print("Deleting data.csv... ");
    SD.remove("data.csv");
    Serial.println("DELETED SUCCESSFULLY!");
  } else {
    Serial.println("No data.csv file found on the card. It is already clean!");
  }
}

void loop() {
  // Nothing to do in the main loop
}
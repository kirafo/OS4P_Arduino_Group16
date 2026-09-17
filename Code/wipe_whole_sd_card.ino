#include <SPI.h>
#include <SD.h>

const int chipSelect = 10;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect (only needed on some boards)
  }

  Serial.println("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("SD init failed!");
    while (1); // Halt if SD fails
  }
  Serial.println("SD init done.");

  // Open root directory
  File root = SD.open("/");
  if (!root) {
    Serial.println("Failed to open root directory!");
    while (1);
  }

  Serial.println("Deleting all files in root directory...");

  // Iterate over all entries in root
  File entry = root.openNextFile();
  while (entry) {
    const char *name = entry.name();

    if (!entry.isDirectory()) {
      Serial.print("Deleting file: ");
      Serial.print(name);
      if (SD.remove(name)) {
        Serial.println("  -> OK");
      } else {
        Serial.println("  -> FAILED");
      }
    } else {
      Serial.print("Directory found (not deleted): ");
      Serial.println(name);
      // Standard SD library does not easily delete directories;
      // You can wipe their contents similarly if needed.
    }

    entry.close();
    entry = root.openNextFile();
  }

  Serial.println("Done deleting files in root.");
}

void loop() {
  // Nothing here
}
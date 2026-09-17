#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>
#include <Adafruit_BME280.h>

// 5-digit run ID (change this before each run if you want a new file)
// Examples: 00001, 00002, 01234, etc.
int runId = 1;                  // <-- CHANGE THIS INTEGER for different runs
char filename[16];              // Enough for "data000.csv" + null terminator



// ---------- PIN & SYSTEM SETTINGS ----------
const int chipSelect = 10;      // SD card CS pin (usually 10 on Arduino Uno)
const int statusLed  = 13;      // On-board LED
const int time_step  = 10000;   // 10 seconds in milliseconds

// ---------- CO₂ SENSOR (MH-Z19) SETTINGS ----------
// IMPORTANT: match these to your wiring
// Arduino pin 2 = RX (connect sensor TX here)
// Arduino pin 3 = TX (connect sensor RX here)
#define MH_Z19_RX 2
#define MH_Z19_TX 3

SoftwareSerial co2Serial(MH_Z19_RX, MH_Z19_TX);

// Command to request CO₂ from MH-Z19
byte cmd[] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
unsigned char response[9];

// ---------- BME280 (P/T/RH) SENSOR ----------
Adafruit_BME280 bme;
float lastT, lastP, lastH;

// ---------- SD FILE / RUN ID ----------
File myFile;



// ---------- LOGGING CONTROL ----------
unsigned long lastLogTime = 0;
int lineCounter = 1;


// ---------- HELPER: CREATE FILENAME FROM RUN ID ----------
void buildFilename() {
  // Creates something like "data00001.csv"
  snprintf(filename, sizeof(filename), "data%03d.csv", runId);
}


// ---------- SETUP ----------
void setup() {
  Serial.begin(9600);
  pinMode(statusLed, OUTPUT);

  Serial.println(F("--- SYSTEM STARTUP ---"));

  // 1. Build filename based on runId
  buildFilename();
  Serial.print(F("Using filename: "));
  Serial.println(filename);

  // 2. Initialize SD card
  Serial.print(F("Initializing SD card... "));
  if (!SD.begin(chipSelect)) {
    Serial.println(F("FAILED!"));
    while (1);  // freeze here if SD fails
  }
  Serial.println(F("SUCCESS!"));

  // 3. Create file with header if it doesn't exist
  if (!SD.exists(filename)) {
    Serial.print(F("Creating new file: "));
    Serial.println(filename);
    myFile = SD.open(filename, FILE_WRITE);
    if (myFile) {
      myFile.println(F("Time (seconds),CO2 (ppm),Temperature (C),Pressure (Pa),Humidity (%)"));
      myFile.close();
      Serial.println(F("Header written."));
    } else {
      Serial.println(F("ERROR: Could not create data file!"));
    }
  } else {
    Serial.print(F("Found existing file: "));
    Serial.println(filename);
    Serial.println(F("New data will be appended."));
  }

  // 4. Initialize CO₂ sensor serial
  Serial.print(F("Initializing CO2 sensor serial... "));
  co2Serial.begin(9600);
  Serial.println(F("DONE."));

  // 5. Initialize BME280 sensor
  Serial.print(F("Initializing BME280 sensor... "));
  int status = bme.begin(0x76);   // Typical I2C address for BME280
  if (!status) {
    Serial.println(F("FAILED! Check wiring. Freezing system."));
    while (1);   // freeze here if BME280 fails
  }
  Serial.println(F("SUCCESS!"));

  Serial.println(F("Ready! Starting loop...\n"));
}


// ---------- MAIN LOOP ----------
void loop() {
  // Run every time_step milliseconds (10 seconds)
  if (millis() - lastLogTime >= time_step) {
    lastLogTime = millis();

    Serial.println(F("[Loop] Reading sensors and writing to SD..."));

    // --------- 1. READ CO₂ SENSOR ---------
    int co2ppm = -1;  // default invalid value

    // Clear any old data from the CO2 serial buffer
    while (co2Serial.available()) { co2Serial.read(); }

    // Send command to MH-Z19
    co2Serial.write(cmd, 9);
    delay(150);   // wait for sensor to reply

    int availableBytes = co2Serial.available();
    Serial.print(F("CO2 bytes received: "));
    Serial.print(availableBytes);
    Serial.print(F(" / 9. "));

    if (availableBytes >= 9) {
      for (int i = 0; i < 9; i++) {
        response[i] = co2Serial.read();
      }
      // Check packet header
      if (response[0] == 0xFF && response[1] == 0x86) {
        co2ppm = (response[2] << 8) + response[3];
        Serial.print(F("CO2: "));
        Serial.print(co2ppm);
        Serial.print(F(" ppm. "));
      } else {
        Serial.println(F("ERROR: Bad CO2 data packet headers!"));
      }
    } else {
      Serial.println(F("TIMEOUT: CO2 sensor didn't reply in time."));
    }

    // --------- 2. READ BME280 (T, P, RH) ---------
    lastT = bme.readTemperature();
    lastP = bme.readPressure();
    lastH = bme.readHumidity();

    Serial.print(F("T: ")); Serial.print(lastT); Serial.print(F(" C | "));
    Serial.print(F("P: ")); Serial.print(lastP); Serial.print(F(" Pa | "));
    Serial.print(F("H: ")); Serial.print(lastH); Serial.print(F(" % | "));

    // --------- 3. WRITE ONE LINE TO CSV ---------
    int secondsPassed = lineCounter * (time_step / 1000);

    myFile = SD.open(filename, FILE_WRITE);
    if (myFile) {
      // Time
      myFile.print(secondsPassed);
      myFile.print(",");

      // CO2 (if reading failed, co2ppm will be -1)
      myFile.print(co2ppm);
      myFile.print(",");

      // Temperature, Pressure, Humidity
      myFile.print(lastT);
      myFile.print(",");
      myFile.print(lastP);
      myFile.print(",");
      myFile.println(lastH);

      myFile.close();
      lineCounter++;

      Serial.println(F("Data written to SD."));
      // Blink status LED
      digitalWrite(statusLed, HIGH);
      delay(150);
      digitalWrite(statusLed, LOW);
    } else {
      Serial.println(F("SD WRITE ERROR! Could not open file."));
    }

    Serial.println(); // blank line for readability
  }

  // Nothing else in loop; everything happens on the 10 s interval
}
#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>
#include <Adafruit_BME280.h>

// ---------- RUN ID SETTINGS ----------
// The Arduino starts searching at this number and increments
// until it finds an unused filename.
int runId = 0;

char filename[16];  // Enough for "data000.csv" + null terminator


// ---------- PIN & SYSTEM SETTINGS ----------
const int chipSelect = 10;
const int statusLed = 13;
const unsigned long time_step = 10000UL;  // 10 seconds


// ---------- CO2 SENSOR SETTINGS ----------
// Arduino pin 2 = RX: connect MH-Z19 TX here
// Arduino pin 3 = TX: connect MH-Z19 RX here
#define MH_Z19_RX 2
#define MH_Z19_TX 3

SoftwareSerial co2Serial(MH_Z19_RX, MH_Z19_TX);

// Command to request CO2 from MH-Z19
byte cmd[] = {
  0xFF, 0x01, 0x86, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x79
};

unsigned char response[9];


// ---------- BME280 SENSOR ----------
Adafruit_BME280 bme;

float lastT;
float lastP;
float lastH;


// ---------- SD FILE ----------
File myFile;


// ---------- LOGGING CONTROL ----------
unsigned long lastLogTime = 0;
int lineCounter = 1;


// ---------- CREATE FILENAME ----------
void buildFilename() {
  // Creates filenames such as:
  // data000.csv
  // data001.csv
  // data999.csv

  snprintf(filename, sizeof(filename), "data%03d.csv", runId);
}


// ---------- FIND UNUSED RUN ID ----------
bool findUnusedRunId() {
  while (runId <= 999) {
    buildFilename();

    if (!SD.exists(filename)) {
      return true;
    }

    Serial.print(F("File already exists: "));
    Serial.println(filename);

    runId++;
  }

  return false;
}


// ---------- SETUP ----------
void setup() {
  Serial.begin(9600);
  pinMode(statusLed, OUTPUT);

  Serial.println(F("--- SYSTEM STARTUP ---"));

  // 1. Initialize SD card
  Serial.print(F("Initializing SD card... "));

  if (!SD.begin(chipSelect)) {
    Serial.println(F("FAILED!"));
    while (1);
  }

  Serial.println(F("SUCCESS!"));

  // 2. Find an unused filename
  if (!findUnusedRunId()) {
    Serial.println(F("ERROR: All filenames from data000.csv to data999.csv exist."));
    Serial.println(F("Please delete some old files from the SD card."));
    while (1);
  }

  Serial.print(F("Using new filename: "));
  Serial.println(filename);

  // 3. Create the new file and write its header
  Serial.print(F("Creating new file: "));
  Serial.println(filename);

  myFile = SD.open(filename, FILE_WRITE);

  if (myFile) {
    myFile.println(
      F("Time (seconds),CO2 (ppm),Temperature (C),Pressure (Pa),Humidity (%)")
    );

    myFile.close();
    Serial.println(F("Header written."));
  } else {
    Serial.println(F("ERROR: Could not create data file!"));
    while (1);
  }

  // 4. Initialize CO2 sensor serial
  Serial.print(F("Initializing CO2 sensor serial... "));

  co2Serial.begin(9600);

  Serial.println(F("DONE."));

  // 5. Initialize BME280 sensor
  Serial.print(F("Initializing BME280 sensor... "));

  int status = bme.begin(0x76);

  if (!status) {
    Serial.println(F("FAILED! Check wiring."));
    while (1);
  }

  Serial.println(F("SUCCESS!"));

  Serial.println(F("Ready! Starting loop...\n"));

  // Start timing from this point
  lastLogTime = millis();
}


// ---------- MAIN LOOP ----------
void loop() {
  // Log every 10 seconds
  if (millis() - lastLogTime >= time_step) {
    lastLogTime = millis();

    Serial.println(F("[Loop] Reading sensors and writing to SD..."));

    // --------- 1. READ CO2 SENSOR ---------
    int co2ppm = -1;

    // Clear old data from the CO2 serial buffer
    while (co2Serial.available()) {
      co2Serial.read();
    }

    // Send measurement command
    co2Serial.write(cmd, 9);

    // Wait for the sensor response
    delay(150);

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
        Serial.println(F("ERROR: Bad CO2 packet header."));
      }
    } else {
      Serial.println(F("TIMEOUT: CO2 sensor did not reply."));
    }


    // --------- 2. READ BME280 ---------
    lastT = bme.readTemperature();
    lastP = bme.readPressure();
    lastH = bme.readHumidity();

    Serial.print(F("T: "));
    Serial.print(lastT);
    Serial.print(F(" C | "));

    Serial.print(F("P: "));
    Serial.print(lastP);
    Serial.print(F(" Pa | "));

    Serial.print(F("H: "));
    Serial.print(lastH);
    Serial.print(F(" % | "));


    // --------- 3. WRITE DATA TO CSV ---------
    int secondsPassed = lineCounter * (time_step / 1000UL);

    myFile = SD.open(filename, FILE_WRITE);

    if (myFile) {
      myFile.print(secondsPassed);
      myFile.print(",");

      // CO2 is -1 if the measurement failed
      myFile.print(co2ppm);
      myFile.print(",");

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

    Serial.println();
  }
}
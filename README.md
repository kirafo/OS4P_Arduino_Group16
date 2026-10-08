# Introduction
For this project we connected a CO2 sensor and a P/T/RH sensor (pressure, temperature, relative humidity) to an Arduino UNO to take environmental data, we included a short python script to plot the data.
The instructions can be found in [Instructions.md](/Instructions.md), all necessary code for the Arduino and the data analysis can be found in the folder "Code". The expected output from the data analysis can be found in the folder [data](/Code/data).

Below we list the prerequisites to reproduce our project, have fun!

## Prerequisites
For this project you need the Arduino IDE installed on your computer. We used version 1.8.19 and version 2.3.10, other versions might also work.

Download the Arduino IDE from the official website for your specific operating system and follow the installation instructions:
https://www.Arduino.cc/en/software/

Here is the official Arduino documentation for more information: https://docs.Arduino.cc/software/ide/

For this project you need:
The hardware was provided to us by the Utrecht University but we included links on where the hardware could be purchased. We are not affiliated with the linked vendors, nor doe we have experience with it.

- 16 cables
- 1 USB-B 2.0 to USB-C [available here](https://www.tinytronics.nl/en/cables-and-connectors/cables-and-adapters/usb/usb-b/goobay-67985-usb-c-usb-b-2.0-cable-1m)
- 1 CO2 sensor (MH-Z19C, 400-2000PPM, 202 101 15) [available here](https://www.tinytronics.nl/en/sensors/air/gas/winsen-mh-z19c-co2-sensor-with-cable)
- 1 P/T/RH sensor (BME/BMP280) [available here](https://www.tinytronics.nl/nl/sensoren/lucht/druk/bme280-digitale-barometer-druk-en-vochtigheid-sensor-module-met-level-converter)
- 1 micro SD card (32 GB, other sizes might also work) [available here](https://www.amazon.nl/-/en/SanDisk-Android-MicroSDXC-Adapter-Smartphones/dp/B08GY9NYRM?th=1)
- 1 micro SD card reader [available here](https://www.otronic.nl/nl/micro-sd-kaartlezer-voor-arduino)
- 1 Arduino Uno
- 1 Breadboard [available here](https://www.tinytronics.nl/en/tools-and-mounting/prototyping-supplies/breadboards/breadboard-400-points)
- 1 thin stick/pen to press the reset button
 
This is a photo of the parts we used, note that not all cables are shown in the photo.
<img width="1200" height="1600" alt="Untitled design" src="https://github.com/user-attachments/assets/f52b134b-e6e1-4483-adda-6f340c5cf095" />

# Copyright 2026 OS4P Group 16

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

# Instructions
Below we list the instructions to reproduce our project, have fun!

## Prerequisites
For this project you need the Arduino IDE installed on your computer. We used version 1.8.19, other versions might also work.

Download the Arduino IDE from the official website for your specific operating system and follow the installation instructions:
https://www.arduino.cc/en/software/

Here is the official Arduino documentation for more information: https://docs.arduino.cc/software/ide/

For this project you need:

- 16 cables
- 1 USB-B 2.0 to USB-C
- 1 CO2 sensor (MH-Z19C, 400-2000PPM, 202 101 15)
- 1 P/T/RH sensor (BME/BMP280))
- 1 SD card
- 1 SD card reader
- 1 Arduino Uno
- 1 Breadboard
- 1 thin stick/pen to press the reset button
 
This is a photo of the parts we used, note that not all cables are shown in the photo.
<img width="1200" height="1600" alt="Untitled design" src="https://github.com/user-attachments/assets/f52b134b-e6e1-4483-adda-6f340c5cf095" />

### Initial test of Arduino Uno
This step is recommended but not strictly necessary for this project.

There is always a possibility that the Arduino Uno itself is faulty, thus it is recommended to perform a simple test to rule this out.
For this, the Arduino Uno, the USB-B 2.0 to USB-C cable, and a computer (with the Arduino IDE installed) is needed. Connect the Arduino Uno to the computer with the USB cable and open the Arduino IDE. Then open the "Blink" script under "File -> Examples -> 01.Basics -> Blink", this is a very basic code that makes the on-board LED blink. To run the script, verify it by pressing the check mark at the top left, afterwards upload it by pressing the arrow on the right of it and select the Arduino. If everything worked correctly, the on-board LED should now be blinking and this step is done. If not, then there might be an issue with the Arduino Uno.

## The code
The code for the Arduino can be found in the folder [Code](/Code). The .ino files are files with code for the Arduino.


## Troubleshooting

- The right device needs to be selected when uploading the code to the Arduino. It should include "arduino" in the name.

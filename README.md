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
For more information about this step can be found in the official Arduino documentation: https://docs.arduino.cc/built-in-examples/basics/Blink/

## brief introduction to the arduino ide software? 
tell them for instance how to open the serial monitor etc


## Connecting the Arduino and sensors
tell them how to connect the arduino with the sensors via the breadboard and give them a nice schematic so that is clear how to put the wires, also explain a bit how the IDE software works and how to upload code to arduino etc

>[!IMPORTANT]
>Make sure all wires are properly connected, a single loose/disconnected wire may cause unexpected issues. Please keep in mind that by moving the Arduino and its connected sensors wires can get loose or disconnected so please check the connections after moving the setup to avoid unexpected errors. 

## Controlling the arduino
Once the Arduino and the sensors are connected, one can use the Arduino IDE software to write, compile and upload code to the arduino in order to get it to do something. You can find the C++ code that we used to obtain our results in the folder [Code](/Code). The .ino files are files with code for the Arduino. One can copy the code from these files into a new project in the Arduino IDE application, you can then compile the code by pressing the check mark (top left corner) and then upload the code to the arduino with the upload button (right arrow next to the compile button). The code will then be sent to the arduino and it will start running the code. 
### Wipe the SD card 
We recommend to first clean the SD card in the SD card reader. We can do this via the Arduino:
1. Create a New Sketch in Arduino IDE (File --> New Sketch), make sure the Arduino Uno is connected and visible for the IDE software by clicking Arduino Uno next to the verify/upload buttons and check if it shows Arduino Uno with a port name like e.g. COM 7
2. Replace the default code with the code from [wipe_whole_sd_card.ino](/Code/wipe_whole_sd_card.ino) 
3. Compile the code with the checkmark button
4. Upload the code to the Arduino with the right arrow button
5. If it was performed correctly the serial monitor should have the following output:
```
Initializing SD card...
SD init done.
Deleting all files in root directory...
Done deleting files in root.
```
>[!TIP]
> If for some reason later on you want to remove only one file on the SD card you can use the code [wipe_one_file_on_sd_card.ino](/Code/wipe_one_file_on_sd_card.ino), change the name of the file you want to remove on the SD card in the code and then upload it to the Arduino.
### Taking data
After wiping the SD card we should be left with a fully empty SD card so we can start taking data. To take the data perform the following steps:
1. Create a New Sketch in Arduino IDE (File --> New Sketch), again confirm the connection with Arduino Uno
2. Replace the default code with the full code from [take_data.ino](/Code/take_data.ino) #IF THE NEW CODE IS WORKING CHANGE THE FILE!!!
3. In this code you can change the variable `runId`, which will change the filename of the datafile. 
>[!NOTE]
>By default `runId = 0`, which gives you the filename `data000.csv` for your datafile. The code will check if the datafile has been made before, if e.g. `data000.csv, data001.csv, data002.csv` already exist, the code will just find the next possible data filename: `data003.csv`. 
4. Verify and upload the code to the Arduino, it will now start running untill you disconnect the usb connection with your pc/laptop.
>[!TIP]
>The code will take a sample every 10 seconds, this can be changed by changing the value `const int time_step  = 10000;` (see ---------- PIN & SYSTEM SETTINGS ---------- in the code ). The time step is set in milliseconds.
5. If the code is performing correctly you should see an output in the Serial Monitor similar to this:
```
□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□--- SYSTEM STARTUP ---
Using filename: data001.csv
Initializing SD card... SUCCESS!
Found existing file: data001.csv
New data will be appended.
Initializing CO2 sensor serial... DONE.
Initializing BME280 sensor... SUCCESS!
Ready! Starting loop...

[Loop] Reading sensors and writing to SD...
CO2 bytes received: 9 / 9. CO2: 682 ppm. T: 24.71 C | P: 102548.17 Pa | H: 40.40 % | Data written to SD.

[Loop] Reading sensors and writing to SD...
CO2 bytes received: 9 / 9. CO2: 678 ppm. T: 24.76 C | P: 102545.22 Pa | H: 40.32 % | Data written to SD.
```

>[!IMPORTANT] 
> When connecting the Arduino Uno to a power supply or laptop it will immediately start running the code that was last uploaded. So if for example you run the `take_data` code first from your laptop, then disconnect, and then reconnect again, it will start building a new datafile with the `runId` of the previous.

### Getting the data on your own PC / laptop
After you take the data, of course you want to be able to get the data from the SD card to your PC / laptop to analyze the data. There are two ways to get the data from the SD card: The easiest is taking the SD card out of the SD card reader that was connected to the Arduino, then plugging it into your own PC / laptop if possible. Then simply copy the datafiles you have made to a folder called `data` on your computer. If you don't have a SD card reader on your PC / laptop, don't worry we got you covered! The following steps will tell you how to get the data trough the Arduino:
1. Create again a New Sketch in the Arduino IDE software (File --> New Sketch)
2. Replace the default code with the code from [data_reader_to_serial_monitor](/Code/data_reader_to_serial_monitor.ino)
3. Change the variable `runId` in this code to the one corresponding to the filename of the run you want to get the data from
4. Verify and Upload the code
5. The whole content will now be written to the Serial Monitor in the Arduino IDE software
6. Copy the ouput with the copy output button on the top right corner of the serial monitor (don't try to select it by hand because you can only select the part that is actually visible in the Serial Monitor)
7. Copy that csv formatted text into a .txt file on your computer and convert it into a .csv file, put this datafile in a folder called `data` on your computer


### Analyzing the data
After you obtained the data you can analyze this data by running the python script [data_analysis.py](data_analysis.py). Download this python code to your pc and **place it in the folder where you have made your `data` folder**. In this code you can change the filename of the data you want to analyze and then you can simply run the code with your favourite python interpreter. After running the data analysis script it will make the plots for you. 


## Troubleshooting

- The right device needs to be selected when uploading the code to the Arduino. It should include "arduino" in the name.

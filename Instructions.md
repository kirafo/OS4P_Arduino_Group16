These are the instructions on how to use the Arduino UNO to measure CO2, temperature, pressure and relative humidity.

### Initial test of Arduino UNO
This step is recommended but not strictly necessary for this project.

There is always a possibility that the Arduino UNO itself is faulty, thus it is recommended to perform a simple test to rule this out.
For this, the Arduino UNO, the USB-B 2.0 to USB-C cable, and a computer (with the Arduino IDE installed) is needed. Connect the Arduino UNO to the computer with the USB cable and open the Arduino IDE. Then open the "Blink" script under "File -> Examples -> 01.Basics -> Blink", this is a very basic code that makes the on-board LED blink. To run the script, verify it by pressing the check mark at the top left, afterwards upload it by pressing the arrow on the right of it and select the Arduino. If everything worked correctly, the on-board LED should now be blinking and this step is done. If not, then there might be an issue with the Arduino UNO.
For more information about this step can be found in the official Arduino documentation: https://docs.Arduino.cc/built-in-examples/basics/Blink/

<!-- CSV## brief introduction to the Arduino IDE software? -->
<!-- tell them for instance how to open the serial monitor etc -->


## Connecting the Arduino and sensors

<img width="1225" height="792" alt="image" src="https://github.com/user-attachments/assets/4a48910b-05a3-4d90-adc9-28120f85cdc4" />
This schematic shows how the bread board and the Arduino UNO need to be connected. The colors of the cables are arbitrary, we chose to use different colors for clarity. 


The software we used did not have the sensors/reader, so we used black cables as placeholders. In the attached photo, you can see how the sensors need to be connected to the bread board.

>[!IMPORTANT]
>Make sure all wires are properly connected, a single loose/disconnected wire may cause unexpected issues. Please keep in mind that by moving the Arduino and its connected sensors wires can get loose or disconnected so please check the connections after moving the setup to avoid unexpected errors. 

## Controlling the Arduino
Once the Arduino and the sensors are connected, you can use the Arduino IDE software to write, compile and upload code to the Arduino in order to get it to do something. You can find the C++ code that we used to obtain our results in the folder [Code](/Code). The .ino files are files with code for the Arduino. You can copy the code from these files into a new project in the Arduino IDE application, you can then compile the code by pressing the check mark (top left corner) and then upload the code to the Arduino with the upload button (right arrow next to the compile button). The code will then be sent to the Arduino and it will start running the code. 
### Wipe the SD card 
We recommend to first clean the SD card in the SD card reader. We can do this via the Arduino:
1. Create a New Sketch in Arduino IDE (File --> New Sketch), make sure the Arduino UNO is connected and visible for the IDE software by clicking Arduino UNO next to the verify/upload buttons and check if it shows Arduino UNO with a port name like e.g. COM 7
2. Replace the default code with the code from [wipe_whole_sd_card.ino](/Code/wipe_whole_sd_card.ino) 
3. Compile the code with the checkmark button
4. Upload the code to the Arduino with the right arrow button
5. If it was performed correctly the serial monitor (button on the top right) should have the following output:
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
1. Create a New Sketch in Arduino IDE (File --> New Sketch), again confirm the connection with Arduino UNO
2. Replace the default code with the full code from [take_data_updated.ino](/Code/take_data_updated.ino) 
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
> When connecting the Arduino UNO to a power supply or laptop it will immediately start running the code that was last uploaded. So if for example you run the `take_data` code first from your laptop, then disconnect, and then reconnect again, it will start building a new data file with the `runId` of the previous.

### Getting the data on your own PC / laptop
After you take the data, of course you want to be able to get the data from the SD card to your PC / laptop to analyze the data. There are two ways to get the data from the SD card: The easiest is taking the SD card out of the SD card reader that was connected to the Arduino, then plugging it into your own PC / laptop if possible. Then simply copy the datafiles you have made to a folder called `data` on your computer. If you don't have a SD card reader on your PC / laptop, don't worry we got you covered! The following steps will tell you how to get the data trough the Arduino:
1. Create again a New Sketch in the Arduino IDE software (File --> New Sketch or File --> New )
2. Replace the default code with the code from [data_reader_to_serial_monitor](/Code/data_reader_to_serial_monitor.ino)
3. Change the variable `runId` in this code to the one corresponding to the filename of the run you want to get the data from
4. Verify and Upload the code
5. The whole content will now be written to the Serial Monitor in the Arduino IDE software
6. Copy the output with the copy output button on the top right corner of the serial monitor (don't try to select it by hand because you can only select the part that is actually visible in the Serial Monitor)
7. Copy that csv formatted text into a .txt file on your computer and convert it into a .csv file, put this data file in a folder called `data` on your computer


### Analyzing the data
After you obtained the data you can analyze this data by running the python script [data_analysis.py](data_analysis.py). Download this python code to your pc and **place it in the same folder where you store your `data`**. In this code change the filename of the data you want to analyze and then you can simply run the code with your preferred python interpreter. After running the data analysis script it will make the plots for you. 


## Troubleshooting

- The right device needs to be selected when uploading the code to the Arduino. It should include Arduino" in the name.
  
```
sketch_oct05a:4:10: fatal error: Adafruit_BME280.h: No such file or directory
 #include <Adafruit_BME280.h>
          ^~~~~~~~~~~~~~~~~~~
compilation terminated.
exit status 1
Adafruit_BME280.h: No such file or directory

This report would have more information with
"Show verbose output during compilation"
option enabled in File -> Preferences.
```
- This error message (when attempting to take data) means that one of the necessary libraries is not installed on the Arduino IDE. To fix this open "Sketch -> Include -> Library -> Manage Libraries" in the IDE. Then search for Adafruit BME280 and click on "Install all".
- If the data is not saving to the SD card or the CO2 sensor keeps reading exactly 500ppm it is likely due too a loose connection. Checking all connections and restarting the Arduino (unplugging/re-plugging or pressing the red reset button) will fix the problem.

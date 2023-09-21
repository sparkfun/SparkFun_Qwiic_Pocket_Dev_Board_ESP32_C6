---
icon: simple/arduino
---

!!! attention
	If this is your first time using Arduino, please read through our tutorial on [installing the Arduino IDE](https://learn.sparkfun.com/tutorials/installing-arduino-ide). If you have not installed an Arduino library before, we recommend you check out our [installation guide](https://learn.sparkfun.com/tutorials/installing-an-arduino-library).

With the Qwiic Pocket Dev Board connected to our computer, it's time to set up the boards package in Arduino.

## Installing espressif Arduino Boards

The espressif ESP32 Arduino Boards package includes the Qwiic Pocket Development Board - ESP32-C6 (and Thing Plus version). Install it by navigating to the Boards Manager tab on the left of the IDE, then search for "espressif" and install the latest version of the ESP32 boards package as the screenshot below shows. This assumes the use of Arduino 2.x. Legacy users (Arduino 1.8x and previous) can find the Boards Manager tool in File/Tools/Boards Manager.

## Smart Watch Example Libraries

If you're following along with the smart watch example you'll need to install the Arduino libraries for the three Qwiic breakouts used in it. Install the libraries through Arduino's Library Manager Tool by searching for the following: **"Micro OLED Breakout"**, **"SparkFun Qwiic RTC RV1805"**, and **"SparkFun BMI270"**. Users who prefer to install them manually can download ZIP folders of the libraries by clicking the buttons below:

<center>
[SparkFun Micro OLED Arduino Library (ZIP)](https://github.com/sparkfun/SparkFun_Micro_OLED_Arduino_Library/archive/refs/heads/main.zip){ .md-button .md-button--primary }
</center>

<center>
[SparkFun RV-1805 Arduino Library (ZIP)](https://github.com/sparkfun/SparkFun_RV-1805_Arduino_Library/archive/refs/heads/master.zip){ .md-button .md-button--primary }
</center>

<center>
[SparkFun BMI270 Arduino Library (ZIP)](https://github.com/sparkfun/SparkFun_BMI270_Arduino_Library/archive/refs/heads/main.zip){ .md-button .md-button--primary }
</center>
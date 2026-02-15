**Low-Cost Vision-Based Autonomous 4WD Robot Research Project Documentation**

**ESP32 Image Processing + Arduino Motor Control**

This project presents a low-cost computer vision–based autonomous four-wheeled robot built using an ESP32 camera module for perception and an Arduino Uno (Freenove 4WD kit) for motor control.

The system implements real-time image processing, neural network–based object recognition, and closed-loop autonomous navigation using a serial communication pathway between the ESP32 and Arduino.

Project Overview

The robot:

Detects obstacles using computer vision

Recognizes directional cues (stop, left, right)

Performs real-time motor adjustments

Uses UART serial communication between ESP32 and Arduino

Demonstrates embedded TinyML-style neural inference on constrained hardware

This project was developed as part of a research study on low-cost autonomous navigation systems.

Folder Structure Overview
Automatic_Line_Tracking/
Automatic_Obstacle_Avoidance/
Bluetooth_Remote_Car/
CameraWebServer/
IR_Remote/
LED_Strip/
Main_Project/
RF_Remote_Control_Joystick/
RF_Remote_Control_Robot/
Ultrasonic_Ranging/
Development of a Low-Cost Computer Vision-Based Four-Wheeled Robot for Autonomous Navigation Using ESP32 Image Processing and Arduino Motor Control Research Article.pdf

Main Project Setup (IMPORTANT)

The Main_Project/ folder contains the full vision-based autonomous navigation system.

Follow these steps carefully.

Step 1 — Navigate to Main_Project

Open:

Main_Project/


Inside, you will find:

images/

src/

neural_network/

arduino/

img2h.py

ESP32 project files

Step 2 — Replace Image Dataset

Navigate to:

Main_Project/images/


Replace the existing images with:

Photos of your stop signs

Left-turn signs

Right-turn signs

Any obstacle objects you want the robot to detect

⚠️ Use consistent lighting and clear backgrounds for best results.

Step 3 — Convert Images to Header Files

The ESP32 cannot directly use image files.
They must be converted into .h header files.

In the Main_Project directory, run:

python img2h.py


This script:

Converts your images into C header arrays

Generates .h files

Makes them usable inside the ESP32 firmware

After running, confirm that new header files are generated.

Step 4 — Upload ESP32 Code

Navigate to:

Main_Project/src/


Then go to:

esp32/
neural_network/
esp32_code.ino


Open esp32_code.ino in Arduino IDE.

Select Board:

AI Thinker ESP32-CAM

ESP32 WROVER

ESP32 WROOM

Or compatible ESP32 camera module

Upload the code to your ESP32.

Step 5 — Upload Arduino Code

Navigate to:

Main_Project/arduino/
arduino.ino


Open in Arduino IDE.

Select Board:

Arduino Uno (Freenove 4WD Kit)

Upload to the Arduino board.

System Architecture

ESP32:

Captures images

Runs neural network inference

Detects signs / obstacles

Sends serial commands

Arduino Uno:

Receives serial commands

Controls motor driver shield

Executes movement decisions

Communication:

UART Serial TX/RX

Structured control packets

Other Project Folders

These are standalone example modules provided for modular experimentation:

Folder	Description
Automatic_Line_Tracking	IR-based line following
Automatic_Obstacle_Avoidance	Ultrasonic-based avoidance
Bluetooth_Remote_Car	Bluetooth control
CameraWebServer	ESP32 camera streaming
IR_Remote	Infrared remote control
LED_Strip	LED control demo
RF_Remote_Control_Joystick	RF joystick transmitter
RF_Remote_Control_Robot	RF robot receiver
Ultrasonic_Ranging	Distance measurement example

These are optional and useful for learning or testing individual subsystems.

Research Article Included

The full research paper is included in this repository:

Development of a Low-Cost Computer Vision-Based Four-Wheeled Robot for Autonomous Navigation Using ESP32 Image Processing and Arduino Motor Control

This paper explains:

System architecture

Neural optimization

Experimental setup

Limitations and improvements

Educational implications

Requirements

Hardware:

Freenove 4WD Robot Car Kit (Arduino Uno based)

ESP32-CAM (WROVER/WROOM compatible)

USB-to-Serial adapter (for ESP32-CAM)

Rechargeable batteries

Software:

Arduino IDE

Python 3 (for img2h.py)

ESP32 board package installed in Arduino IDE

Important Notes

Ensure correct TX/RX wiring between ESP32 and Arduino

Disconnect RX/TX when uploading to avoid conflicts

Verify power stability (low voltage can cause motor buzzing)

Use adequate lighting for best image recognition results

Future Improvements

Quantized neural network deployment

Edge Impulse integration

Sensor fusion with ultrasonic + vision

Improved power regulation

Real-time adaptive thresholding

**Author**

**Made by Abhiram Kaakarla**

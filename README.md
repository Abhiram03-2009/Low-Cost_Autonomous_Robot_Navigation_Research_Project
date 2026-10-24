# 🚗 Low-Cost Vision-Based Autonomous 4WD Robot  
## ESP32 Image Processing + Arduino Motor Control

A low-cost autonomous four-wheeled robot implementing real-time computer vision using an ESP32 camera module and Arduino Uno motor control.  

The ESP32 recognizes signs and colored blocks with template matching and sends a command (STOP, LEFT, RIGHT, AVOID) over UART to the Arduino, which drives the motors.

---

# 📌 Project Overview

This system integrates:

- 📷 ESP32-CAM for image capture and template matching  
- 🧠 Embedded object recognition  
- 🔁 UART serial communication  
- ⚙️ Arduino-based motor control  
- 🚦 Autonomous stop / turn behavior  
- 🧪 Experimental testing environment validation  

---

# 📂 Repository Structure
```
├── Automatic_Line_Tracking/
├── Automatic_Obstacle_Avoidance/
├── Bluetooth_Remote_Car/
├── CameraWebServer/
├── IR_Remote/
├── LED_Strip/
├── Main_Project/
├── RF_Remote_Control_Joystick/
├── RF_Remote_Control_Robot/
├── Ultrasonic_Ranging/
```

---

---

# 🚀 Main Project Setup (IMPORTANT)

All core autonomous vision functionality is located in:

Main_Project/

---

# 🖼 Step 1 — Replace Training Images

Navigate to:
Main_Project/images/

Replace the existing images with:

- Stop signs  
- Left-turn signs  
- Right-turn signs  
- Objects you want the robot to detect  

⚠️ Use consistent lighting and clear backgrounds for best detection performance.

---

# 🔄 Step 2 — Convert Images to Header Files

The ESP32 cannot directly use image files.  
They must be converted into `.h` header arrays.

From inside `Main_Project/`, run:

```bash
python img2h.py
```

This script:

Converts images to C header arrays

Generates .h files

Makes them usable in ESP32 firmware

After running, confirm .h files were created successfully.

# 🧠 Step 3 — Upload ESP32 Code

**Navigate to:**

Main_Project/src/esp32/neural network/

**Open:**

esp32_code.ino

In Arduino IDE:

Select Board:

AI Thinker ESP32-CAM

ESP32 WROVER

ESP32 WROOM

Or compatible ESP32 module

Upload the code to the ESP32.

# ⚙️ Step 4 — Upload Arduino Code

**Navigate to:**

Main_Project/src/arduino/

**Open:**

arduino.ino

In Arduino IDE:

Select Board: Arduino Uno

Upload to the Freenove robot car controller

# 🧩 System Architecture
ESP32 Responsibilities

Image acquisition

Template matching: each frame is downscaled to 32×24 grayscale and compared with the stored templates using the sum of absolute differences

Stability check: a detection is accepted only when it wins at least 70% of the last 5 frames

Command generation

Arduino Responsibilities

Receive serial commands (planned; see Current status)

Control motor driver

Execute PWM motor adjustments

Perform turning and braking

Communication

UART Serial TX/RX

Structured command packets

# 📚 Other Included Modules

These folders provide modular demonstrations and alternative control modes:

**- Automatic_Line_Tracking:**	IR-based line following
**- Automatic_Obstacle_Avoidance:**	Ultrasonic obstacle avoidance
**- Bluetooth_Remote_Car:**	Bluetooth manual control
**- CameraWebServer:**	ESP32 video streaming
**- IR_Remote	Infrared:** remote control
**- LED_Strip:** LED control demo
**- RF_Remote_Control_Joystick:**	RF joystick transmitter
**- RF_Remote_Control_Robot:**	RF robot receiver
**- Ultrasonic_Ranging:**	Distance measurement

These are standalone example sketches from the Freenove 4WD Car Kit tutorials (www.freenove.com), and `CameraWebServer` is the standard example from Espressif's ESP32 Arduino core. They were used to test the hardware and are not my original code.

# 📍 Current status

- Working: the ESP32 captures frames, matches them against the 10 stored templates, and prints `CMD:<command>` over serial once a detection is stable.
- Not finished: `Main_Project/src/arduino/arduino.ino` currently runs both motors at a fixed speed and does not yet read the `CMD:` messages, so the robot does not yet stop or turn on its own.
- Known bug: `img2h.py` writes 96×96 templates, but the ESP32 code compares 32×24 frames, so only the first 768 values of each template are used. Setting `IMAGE_WIDTH = 32` and `IMAGE_HEIGHT = 24` in `img2h.py` and regenerating the headers fixes this.

# 🔧 Requirements
**Hardware**

Freenove 4WD Robot Car Kit (Arduino Uno based)

ESP32-CAM (WROVER/WROOM compatible)

USB-to-Serial adapter (for ESP32 upload)

Rechargeable batteries

**Software**

Arduino IDE

Python 3

ESP32 board package installed

# ⚠️ Important Notes

Disconnect RX/TX during uploads to avoid conflicts

Ensure proper grounding between ESP32 and Arduino

Use stable battery voltage to prevent motor buzzing

Maintain consistent lighting for image recognition

# 👤 Author and credits

**Main_Project (template matching, image conversion, ESP32–Arduino integration) by Abhiram Kaakarla.**

Robot hardware and the example sketches in the other folders: Freenove 4WD Car Kit (www.freenove.com). `CameraWebServer`: Espressif ESP32 Arduino core example.

# 🚗 Low-Cost Vision-Based Autonomous 4WD Robot  
## ESP32 Image Processing + Arduino Motor Control

A low-cost autonomous four-wheeled robot implementing real-time computer vision using an ESP32 camera module and Arduino Uno motor control.  

This project demonstrates embedded image processing, lightweight neural network inference, and closed-loop autonomous navigation using serial communication between ESP32 and Arduino.

---

# 📌 Project Overview

This system integrates:

- 📷 ESP32-CAM for image capture and neural inference  
- 🧠 Embedded object recognition  
- 🔁 UART serial communication  
- ⚙️ Arduino-based motor control  
- 🚦 Autonomous stop / turn behavior  
- 🧪 Experimental testing environment validation  

The project was developed as part of a research study on low-cost computer vision–based robotics.

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
├── Research Article
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

```bash```
```python img2h.py```

This script:

Converts images to C header arrays

Generates .h files

Makes them usable in ESP32 firmware

After running, confirm .h files were created successfully.

# 🧠 Step 3 — Upload ESP32 Code

**Navigate to:**

Main_Project/src/esp32/neural_network/

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

Main_Project/arduino/

**Open:**

arduino.ino

In Arduino IDE:

Select Board: Arduino Uno

Upload to the Freenove robot car controller

# 🧩 System Architecture
ESP32 Responsibilities

Image acquisition

Neural network inference

Object recognition

Command generation

Arduino Responsibilities

Receive serial commands

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

These are standalone example implementations.

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

# 🔮 Future Improvements

TinyML quantized neural networks

Edge Impulse deployment

Sensor fusion (ultrasonic + vision)

Improved power regulation

Adaptive environmental thresholding

# 👤 Author

**Made by Abhiram Kaakarla**

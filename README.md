# Vigil-ESP32-Occupancy-System
ESP32-based real-time occupancy detection system using FreeRTOS, PIR and ultrasonic sensors, and a confidence-based sensor fusion algorithm.

# Vigil

## ESP32-Based Real-Time Occupancy Detection System

Vigil is an embedded occupancy monitoring system built using an ESP32 microcontroller, PIR motion sensor, ultrasonic distance sensor, and SSD1306 OLED display.

The system uses FreeRTOS multitasking and a confidence-based sensor fusion algorithm to estimate occupancy state in real time. Sensor data is processed independently through dedicated tasks, synchronized through shared data protection, and displayed through an OLED interface.

---

## Demo

A demonstration of Vigil detecting occupancy, transitioning between states, and recovering from changing sensor conditions:

[Watch the Vigil Demo](https://www.youtube.com/shorts/QiySP-mDp18)

---

## Features

- ESP32-based embedded system
- FreeRTOS multitasking architecture
- PIR motion detection
- Ultrasonic distance measurement
- Confidence-based sensor fusion algorithm
- Real-time occupancy state estimation
- SSD1306 OLED status display
- Mutex-protected shared data communication
- Modular C++ class-based design

---

# System Overview

Vigil determines occupancy by combining multiple sensor inputs instead of relying on a single sensor.

The system uses:

- PIR sensor → detects motion events
- Ultrasonic sensor → confirms physical presence
- Logic layer → combines sensor evidence into a confidence score
- OLED display → shows current occupancy state

The occupancy state is represented using three possible states:

| State | Description |
|---|---|
| EMPTY | No evidence of occupancy |
| TRANSITION | Confidence is changing between states |
| OCCUPIED | Strong evidence of occupancy |

---

# System Architecture

```
                 PIR Sensor
                     |
                     |
                     v

              PIR Sensor Task


            Ultrasonic Sensor
                     |
                     |
                     v

          Ultrasonic Sensor Task


                     |
                     v

              Logic Processing Task

                     |
                     v

             OccupancyData Structure

                     |
              Mutex Protected

                     |
                     v

               OLED Display Task
```

Each subsystem runs independently using FreeRTOS tasks.

---

# FreeRTOS Task Design

Vigil separates system functionality into multiple concurrent tasks.

## PIR Task

Responsibilities:

- Continuously samples the PIR sensor
- Detects motion events
- Updates motion state

Task interval:

```
100 ms
```

---

## Ultrasonic Task

Responsibilities:

- Measures distance readings
- Filters unstable measurements
- Provides presence confirmation

Task interval:

```
1000 ms
```

---

## Logic Task

Responsibilities:

- Combines sensor evidence
- Updates occupancy confidence
- Determines current system state

The confidence model prevents immediate state changes caused by temporary sensor noise.

---

## OLED Task

Responsibilities:

- Reads occupancy data
- Displays:
  - Current occupancy state
  - Confidence percentage

---

# Occupancy Algorithm

Vigil uses a confidence-based decision model.

Sensor evidence modifies the confidence value:

```
Motion detected:
+30 confidence

Ultrasonic confirmation:
+40 confidence
```

Confidence decreases over time when evidence is no longer present.

State thresholds:

```
Confidence >= 70%
        |
        v
    OCCUPIED


30% < Confidence < 70%
        |
        v
    TRANSITION


Confidence <= 30%
        |
        v
      EMPTY
```

This approach prevents rapid switching caused by individual sensor inaccuracies.

---

# Hardware

## Components

| Component | Purpose |
|---|---|
| ESP32 DevKit | Main microcontroller |
| HC-SR501 PIR Sensor | Motion detection |
| HC-SR04 Ultrasonic Sensor | Distance-based presence detection |
| SSD1306 OLED Display | User interface |
| Breadboard | Prototyping |
| Jumper Wires | Connections |

---

# Pin Configuration

| Component | ESP32 Pin |
|---|---|
| PIR Signal | GPIO 4 |
| Ultrasonic Trigger | GPIO 5 |
| Ultrasonic Echo | GPIO 18 |
| OLED SDA | GPIO 21 |
| OLED SCL | GPIO 22 |

Power connections:

```
VCC → Power rail
GND → Ground rail
```

---

# Software Structure

```
src/

├── Vigil.ino

├── PIRSensor.h
├── PIRSensor.cpp

├── UltrasonicSensor.h
├── UltrasonicSensor.cpp

├── Logic.h
├── Logic.cpp

├── OLEDDisplay.h
├── OLEDDisplay.cpp

├── Tasks.h
├── Tasks.cpp

├── SharedData.h

└── SystemState.h
```

---

# Dependencies

Required Arduino libraries:

- Adafruit SSD1306
- Adafruit GFX Library

The ESP32 Arduino Core provides built-in FreeRTOS support.

---

# Future Improvements

Planned improvements:

- ESP-NOW wireless communication between multiple Vigil nodes
- Distributed occupancy monitoring network
- Battery-powered operation
- Improved sensor calibration
- Data logging and analytics
- Web dashboard integration

---

# Technologies Used

- C++
- ESP32
- FreeRTOS
- Sensor Fusion
- Real-Time Embedded Systems
- I2C Communication
- Embedded Multitasking

---

# Author

Built as an embedded systems project focused on real-time sensing, multitasking, and sensor-based decision making.

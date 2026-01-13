# Smart Color-Based Sorting System

Sorting objects by color is essential in industries such as manufacturing, packaging, and recycling. Manual sorting is slow and inconsistent, so this project implements a compact, low-cost automated color-sorting conveyor system using an **Arduino Nano**, **TCS3200 color sensor**, two **servo-driven flaps**, and an **N20 gear-motor belt**.

Objects moving along the conveyor are detected, classified, and sorted into designated bins, demonstrating key **embedded systems principles** such as real-time sensing, PWM-based actuation, and integrated electromechanical control.

---

## Objectives

- Build a compact conveyor with precise color-based sorting.
- Use TCS3200 and dual servos for fast, accurate object diversion.
- Integrate Arduino Nano with real-time control and robust mechanics.
- Demonstrate key embedded concepts: PWM, serial communication, mapping, and calibration.

---

## System Overview

### Mechanical
- 6.3 cm-wide conveyor with custom spur-gear roller driven by N20 motor.
- Height-calibrated servos ensure precise sorting arm placement for smooth belt motion.

### Electronics & Embedded
- Arduino Nano controls TCS3200 sensor and two servos for Blue/Red sorting.
- N20 motor speed controlled via PWM at 3.5 V.
- Serial Monitor at 115200 baud for debugging.

### Software
- Developed in **Arduino IDE** using **Servo** and **Math** libraries.
- Implements **color sensing → normalization → Euclidean distance classification → servo actuation**.
- Includes **brightness filtering**, helper functions for pulse measurement, and normalized RGB calculations.

---

## System Operation

- Conveyor runs continuously while TCS3200 detects object colors.
- Arduino processes sensor data and diverts objects:

| Color | Destination |
|-------|------------|
| Red   | Red bin    |
| Blue  | Blue bin   |
| Green | Passes straight |

- Servo arms retract for the next object.

---

## Embedded System Concepts Used

### Arduino Pin Configuration
- Pins set as **INPUT/OUTPUT** for sensor, servos, and motor.

### Servo Control (PWM)
- Servos receive 50 Hz PWM; Arduino Servo library simplifies control.

### DC Motor Control
analogWrite(MOTOR_PIN, 200); // Controls N20 motor speed

### TCS3200 Color Sensor

- S0-S1: Frequency scaling (20%)

- S2-S3: Select R/G/B photodiode arrays

- pulseIn(OUT_PIN, LOW): Reads pulse width for color intensity
### Key Functions

1. normalizeRGB(unsigned int R, unsigned int G, unsigned int B, float &nr, float &ng, float &nb)

Converts the raw RGB readings into normalized values between 0 and 1 so that nr + ng + nb = 1.
Removes brightness dependency as the raw values of the color sensor depend on lighting conditions, object distance, and surface reflectivity. Normalizing ensures that only the color ratios matter, not absolute intensity.

2. colorDistance(float obj[3], float target[3])
Computes the Euclidean distance between the detected normalized color and a predefined target color (Red or Blue).
Provides a quantitative measure of similarity between the detected object color and reference colors.
Smaller distance → detected color is closer to target.
Thresholding this distance allows us to make classification decisions: which bin the object belongs to.{threshold was set by experimenting }  CNNs extract feature vectors (like color, texture, edges) and compare distances in a feature space to classify objects. Here, the normalized RGB acts as a mini feature vector, and Euclidean distance acts like a similarity measure in that feature space.

3.activateServo(Servo &s)
Purpose:
Physically moves the servo to sort the detected object into the correct bin. 

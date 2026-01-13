# Smart-Color-based-sorting-system
rting objects by color is essential in industries such as manufacturing, packaging, and recycling, 
yet manual sorting remains slow and inconsistent. To address this, the project implements a 
compact, low-cost automated color-sorting conveyor system using an Arduino Nano, TCS3200 
sensor, two servo-driven flaps, and an N20 gear-motor belt. As objects move along the conveyor, 
their color is detected, classified, and sorted into designated bins, demonstrating key embedded
systems principles including real-time sensing, PWM-based actuation, and integrated 
electromechanical control. 
  
2. Objectives: 
➢ Build a compact conveyor with precise color-based sorting. 
➢ Use TCS3200 and dual servos for fast, accurate object diversion. 
➢ Integrate Arduino Nano with real-time control and robust mechanics. 
➢ Demonstrate key embedded concepts: PWM, serial communication, mapping, and 
calibration. 
3. System Overview: 
• Mechanical: 6.3 cm-wide conveyor with a custom spur-gear roller driven by an N20 
motor, aligned via a motor mount. Height-calibrated servos ensure precise sorting arm 
placement, enabling smooth belt motion and reliable object handling. 
• Electronics & Embedded: Arduino Nano controls a TCS3200 color sensor and two servos 
for BLUE?RED sorting. N20 motor runs via PWM at 3.5 V; system debugging through 
Serial Monitor at 115200 baud. 
• Software: Developed in Arduino IDE using the Servo and Math libraries. Includes color 
target vectors, Euclidean distance-based classification, brightness filtering, and helper 
functions for pulse measurement and normalized RGB calculations. Implements a 
complete workflow of color sensing → normalizing→ distance-based classification → 
servo actuation. 
4. System Operation:
➢  Conveyor runs continuously; TCS3200 senses object colors. 
➢ Arduino processes signals; servos divert Blue/Red objects, Green passes straight. 
➢ Arms retract for the next item.
5. Embedded System Concepts Used: 
5.1 Arduino Pin Configuration: 
• All pins for the sensor, servo, and motor are defined as OUTPUT or INPUT based on 
their function 
5.2 Servo Control (PWM): 
• Servos require a 50 Hz PW signal where pulse width determines angle. 
• Arduino’s servo library simplifies this by abstracting the PWM logic. 
5.3 DC Motor Control (analogWrite): 
• The N20 motor is speed-controlled using PWM on pin 3: 
analogWrite(MOTOR_PIN, 200); 
• This outputs a duty cycle that sets speed without requiring a motor driver (assuming low 
load). 
5.4 TCS3200 Color Sensor Operation: 
This sensor uses: 
• S0-S1 for frequency scaling (set to 20%). 
• S2-S3 to select photodiode arrays (R/G/B). 
• pulseIn(OUT_PIN, LOW) is used to read the LOW pulse width. 
5.5 Serial Communication Baud Rate (115200): 
• Serial.begin (115200); configures communication speed at 115200 bits/s. Used for 
debugging distance values and sensor readings.
7 Challenges and limitations; 
• Lighting variations affect color readings. 
• Servo jitter can occur if the power supply isn't isolated. 
• Mechanical tolerance must be precise for accurate sorting. 
• The conveyor speed must be tuned to give sensor enough sampling time. 
8 Applications & Future Enhancements: 
• Useful in manufacturing, packaging, recycling, and academic demonstrations. 
• Suitable for sorting small items like pills, components, and toys. 
• Future upgrades include ESP32 connectivity, camera-based vision, and multi-stage 
sorting. 
• Mechanical mounts and object-detection sensors can be improved for greater accuracy. 
➢ Conveyor runs continuously; TCS3200 senses object colors. 
➢ Arduino processes signals; servos divert Blue/Red objects, Green passes straight. 
➢ Arms retract for the next item. 

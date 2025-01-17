# IGotYourBack

A mechanical recreation of a childhood game – where friends would write messages on your back and you had to focus on the feeling to get it right.

## Project Showcase
[![Project Demo](https://img.youtube.com/vi/ZsXyqrq_RdM/0.jpg)](https://www.youtube.com/watch?v=ZsXyqrq_RdM)

## Description
In this day and age where we are inundated by ubiquitous and instantaneous communication, we invite you to an experience where you communicate with others word by word, one letter at a time. As the user gauges how keenly they can decipher a tactile message, it symbolizes how even the smallest units of communication can be misunderstood and highlights the amount of focus needed to comprehend someone else's intentions. If you have faith and 'lean into' the experience, there's a higher chance you will fare better at getting the message right. We got your back!


## Hardware

### Components
- Arduino Nano BLE (33 IoT) x1
- [MG996R Digital Servo Motor](https://www.amazon.com/diymore-6-Pack-MG996R-Digital-Helicopter/dp/B0CGRP59HJ) x3
  - Operating Voltage: 4.8V-7.2V
  - Stall Torque: 9.4kg/cm (4.8V), 11kg/cm (6V)
  - Speed: 0.17sec/60° (4.8V), 0.14sec/60° (6V)
- SG-5010 Servo Motor x3
  - Operating Voltage: 4.8V-6V
  - Stall Torque: 5.5kg/cm (4.8V), 6.5kg/cm (6V)
  - Speed: 0.16sec/60° (4.8V)
- [Hall Effect Sensor](https://www.digikey.com/en/products/detail/allegro-microsystems/A1324LUA-T/2728144?gQT=1) x1
  - Operating Voltage: 3.3V-5V
  - Digital Output
- Neodymium Magnet x1
  - N52 Grade
  - For switch activation
- Capacitors
  - 220μF Electrolytic Capacitor x3
  - 470μF Electrolytic Capacitor x3
- Wires
  - Solid Core Wire for circuit connections
  - Stranded Wire for servo extensions
- [Switching Power Supply](https://www.circuitspecialists.com/csi3005sm)
  - Output: 0-30V DC, 0-5A
  - Recommended setting: 5V/2A

<!-- ### 3D Printed Parts -->
<!-- [3D Printed Parts will be added here] -->

<!-- ### Circuit Diagram -->
<!-- [Circuit diagram will be added here] -->

## Wiring

Connect the components together in the following order:

| Arduino Pin | Component | Connection Type |
|------------|-----------|-----------------|
| Pin 2 | Hall Effect Sensor | Switch Input |
| Pin 3 | MG996R Servo | X-Axis Motor |
| Pin 5 | MG996R Servo | Y-Axis Motor |
| Pin 9 | MG996R Servo | Z-Axis Motor |
| Pin 15 | SG-5010 Servo | State Flag Motor |
| VIN | Hall Effect Sensor | VIN |
| VIN | MG996R Servo (X-Axis) | VIN |
| VIN | MG996R Servo (Y-Axis) | VIN |
| VIN | MG996R Servo (Z-Axis) | VIN |
| VIN | SG-5010 Servo | VIN |
| VIN | Power Supply | 5V/2A Input |
| GND | Hall Effect Sensor | Ground |
| GND | MG996R Servo (X-Axis) | Ground |
| GND | MG996R Servo (Y-Axis) | Ground |
| GND | MG996R Servo (Z-Axis) | Ground |
| GND | SG-5010 Servo | Ground |
| GND | Power Supply | Ground |

Notes:
- Each servo motor requires:
  - One 220μF capacitor for noise reduction
  - One 470μF capacitor for power stabilization
- Use solid core wire for circuit connections
- Use stranded wire for servo extensions

## Contributors
- Jiyou Park
- Jinhee Shim
- Seungyun Yang
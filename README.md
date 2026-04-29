# ESP32-Based Temperature and Humidity Monitoring System with Blynk IoT and Local Alerts

## Overview

This project implements a real-time environmental monitoring system using an ESP32 and a DHT11 sensor. It not only sends temperature and humidity data to the Blynk IoT platform for remote visualization, but also provides immediate local feedback using an RGB LED and a buzzer.

The system combines cloud-based monitoring with on-device decision making, making it a complete IoT solution.

## Features

* Real-time temperature and humidity monitoring
* Wireless data transmission using ESP32
* Live visualization on Blynk IoT mobile dashboard
* Local alert system using RGB LED
* Buzzer activation for high temperature conditions
* Periodic sensor updates using non-blocking timer

## Hardware Requirements

* ESP32 development board
* DHT11 temperature and humidity sensor
* RGB LED
* Buzzer
* Jumper wires
* Breadboard (optional)

## Circuit Connections

### DHT11 Sensor

| Pin  | Connection |
| ---- | ---------- |
| VCC  | 3.3V       |
| GND  | GND        |
| DATA | GPIO 4     |

### RGB LED

| Color Pin | ESP32 Pin |
| --------- | --------- |
| Red       | GPIO 25   |
| Green     | GPIO 26   |
| Blue      | GPIO 27   |

### Buzzer

| Pin | ESP32 Pin |
| --- | --------- |
| +   | GPIO 13   |
| -   | GND       |

## Working Logic

* Temperature below 25°C

  * Green LED ON
  * Buzzer OFF

* Temperature between 25°C and 30°C

  * Blue LED ON
  * Buzzer OFF

* Temperature above 30°C

  * Red LED ON
  * Buzzer ON

## Software Requirements

* Arduino IDE
* ESP32 Board Package
* Blynk Library
* DHT Sensor Library

## Blynk Configuration

### Template Setup

Create a template in the Blynk Console and use the following:

* Template ID
* Template Name
* Auth Token

### Datastreams

| Name        | Virtual Pin | Data Type | Unit |
| ----------- | ----------- | --------- | ---- |
| Temperature | V0          | Double    | °C   |
| Humidity    | V1          | Double    | %    |

### Mobile Dashboard

Add widgets such as Value Display or Gauge:

* Link Temperature widget to V0
* Link Humidity widget to V1

## Code

Ensure the following structure in your code:

* Blynk template credentials defined before library includes
* Sensor data sent using `Blynk.virtualWrite()`
* Timer used for periodic updates
* Output control logic based on temperature

## Output

* Temperature and humidity values displayed in real time on Blynk app
* RGB LED changes color based on temperature range
* Buzzer activates when temperature exceeds threshold
* Serial Monitor logs sensor readings for debugging

## Troubleshooting

* Ensure WiFi credentials are correct and using a 2.4 GHz network
* Verify Virtual Pins (V0 and V1) match in both code and Blynk
* Check wiring if sensor readings fail
* If RGB LED behaves incorrectly, verify whether it is common anode or common cathode
* Ensure Template ID and Template Name are defined before including Blynk libraries

## Future Scope

* Add threshold customization from Blynk app
* Implement push notifications for alerts
* Store historical data for analysis
* Integrate additional environmental sensors
* Expand to a full home automation or smart environment system

## Author

Anwesha Rath

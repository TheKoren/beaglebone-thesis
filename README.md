# beaglebone-thesis

My Bachelor thesis for the Academic year 2021/22/1.

## Required Hardware

* Beaglebone Black Wireless x1
  * Debian Linux
* Silicon Labs Thunderboard Sense 2 x2

## Task

### Assessment of Air Quality Using an IoT Solution

Inadequate ventilation in different educational institutions often results in air quality that is not sufficient to effective teaching. Such air quality problems include humidity, carbon dioxide (CO2) levels, or the presence of volatile organic compounds (VOCs). In addition, general environmental parameters, such as lighting levels and noise in classrooms, are also factors which make it very difficult or sometimes impossible for students to achieve the active cognitive state necessary for learning.

As part of my thesis, I set out to implement a measurement system using the IoT paradigm to address this problem. The measurement of different environmental characteristics in classrooms are performed by sensor cards from Silicon Labs, Thunderboard Sense 2. The sensor cards allow the creation of low-power systems, capable of handling measurement data on low-power communication interfaces. One of these interfaces is BLE (Bluetooth Low Energy), which was my choice to go with. The central node that scans the sensor network is implemented by a Beaglebone Wireless (BBW) single card computer, which is also able to communicate on this BLE platform.

The air quality can be monitored via a WEB page, in accordance with the IoT approach, broken down into classrooms, and the system is also able to warn the occupants of the room by controlling the LEDs on the sensor cards.


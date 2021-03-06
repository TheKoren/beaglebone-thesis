# beaglebone-thesis

My Bachelor thesis for the Academic year 2021/22/1.

## Required Hardware

* Beaglebone Black Wireless x1
* Silicon Labs Thunderboard Sense 2 x5

## Task

### Assessment of Air Quality Using an IoT Solution
<div align="justify">
 Inadequate ventilation in different educational institutions often results in air quality that is not sufficient to effective teaching. Such air quality problems include humidity, carbon dioxide (CO2) levels, or the presence of volatile organic compounds (VOCs). In addition, general environmental parameters, such as lighting levels and noise in classrooms, are also factors which make it very difficult or sometimes impossible for students to achieve the active cognitive state necessary for learning. <br /><br />
As part of my thesis, I set out to implement a measurement system using the IoT paradigm to address this problem. The measurement of different environmental characteristics in classrooms is performed by sensor cards from Silicon Labs, Thunderboard Sense 2. The sensor cards allow the creation of low-power systems, capable of handling measurement data on low-power communication interfaces. One of these interfaces is BLE (Bluetooth Low Energy), which was my choice to go with. The central node that scans the sensor network is implemented by a Beaglebone Wireless (BBW) single card computer, which is also able to communicate on this BLE platform. <br /><br />
The air quality can be monitored via a WEB page, in accordance with the IoT approach, broken down into classrooms, and the system is also capable to warn the occupants of the room by controlling the LEDs on the sensor cards. <br /><br />
My thesis would present a lower-budget solution to replace more expensive air quality measurement devices, and would provide technical support for the development of other Bluetooth systems based on Beaglebone cards.
</div>

## Architecture
<div align ="middle">
 
![image](https://user-images.githubusercontent.com/44529612/144943456-0e48d183-a87e-4dbd-90b7-4efd37bf0d7a.png)

</div>


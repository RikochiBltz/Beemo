# Beemo - Smart EV Charging System (Technical Documentation)

## System Overview

Beemo is a smart, embedded system designed to automate the electric vehicle (EV) charging process in parking areas. It eliminates the need for human supervision by incorporating intelligent sensing, user interface elements, and control mechanisms.

this is a microcontroller project with pic16f84
to run this project make sure you have isis installed, open the project.dsn file and select the code.c file, the code.c is made with MikroC PRO for PIC.

---

## Core Features

* **Simultaneous Charging**: Supports charging up to 3 EVs at once.
* **Presence Detection**: Automatically activates when a vehicle is detected.
* **LCD Display**: Provides user instructions and system status.
* **Interactive Buttons**: For reservation and exit operations.
* **Electric Gate Control**: Manages vehicle entry and exit.
* **Buzzer Alert**: Indicates when charging is complete.
* **Vehicle Count**: Tracks the number of vehicles charged per day.

---

## Hardware Components

* **Ultrasonic/IR Sensor**: Detects the presence of incoming vehicles.
* **LCD Display (16x2)**: Displays interactive messages.
* **Push Buttons**: Used to reserve a slot and exit the parking space.
* **DC Motors or Servos**: Control entry and exit gates.
* **Relay Module**: Controls power supply to charging circuits.
* **Buzzer**: Notifies user when charging is complete.
* **LED Indicators**: Signal different system states (e.g., available, charging, full).

---

## System Behavior Flow

1. **Detection**: Presence sensor detects vehicle.
2. **Activation**: System powers up and displays "Bienvenue".
3. **Slot Check**: If a slot is available, user can reserve it.
4. **Gate Control**: Gate opens, and vehicle enters.
5. **Charging**: Charging process begins automatically.
6. **Completion**: Upon full charge, buzzer activates.
7. **Exit**: User presses "Exit" button; gate opens.

---

## Charging Logic


* Charging monitored via timers or optional current sensors.
* Charging stops either by timer expiration or charge completion detection.

---

## Scalability & Modularity

* Modular design allows integration of only electronics into existing infrastructure.
* Full-featured version includes physical casing and UI components.

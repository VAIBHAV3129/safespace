# SafeSpace



a desktop guard that alerts you when someone breaches your desk space,but the rest of the time it just tells the time, basically acting as a digital clock


> Built in [Breadboard](https://breadboard.hackclub.com), a Hack Club program. This project took ~1.3 hours of work.



## How To Use It

To use the project, simply plug the ESP32 into a USB power source to activate the system, which will instantly turn on the green status LED to show that it is armed. While your desk is clear, the OLED display will show you a live digital clock followed by the current room temperature and humidity, The moment someone steps into the sensor's path, the system instantly overrides the clock, flashes a bright "BREACH!" warning on the screen, cuts to a red warning LED, and sounds a sharp triple-beep alarm from the buzzer before resetting itself automatically two seconds after the intruder moves away.

## What It Does
it protects you deskspace, a fun hobby project

## How It Works
It displays a rotating digital clock and live room temperature/humidity metrics on an OLED screen while a green LED indicates the system is safe.
An infrared proximity sensor constantly monitors , sending alerts to the ESP32 microcontroller the moment an object enters its path.
Upon detection,it logs a alert, replaces the clock interface with a high-contrast "BREACH!" warning, triggers a red indicator, and pulses the active buzzer before safely resetting.
## Demo

- **Try it:** [https://breadboard.hackclub.com/share/16](https://breadboard.hackclub.com/share/16)

![SafeSpace screenshot](/api/uploads/project-screenshots/rVhEzBAtFuhrt246dpgrV8Uvgfb682wc/16/2835a9d7-31cb-4e4e-9de3-868ed1449c58.png)


## Schematic

The editor snapshot is in `breadboard-project.json`.


## Bill of Materials

- buzzer-active: 1
- dht11: 1
- led-green: 1
- led-red: 1
- obstacle-avoidance-module: 1
- resistor: 2
- ssd1306-i2c: 1


## Firmware

Firmware files are in the `firmware/` folder.


## Build Journal

Build journal entries are kept in [`journals.md`](journals.md).


---



*Made in [Breadboard](https://breadboard.hackclub.com) — 1.3h of work*



<p align="center"><img src="https://cdn.hackclub.com/019efae7-6857-75a2-8bc1-2618087b4eae/a%20bred%20tanuki%20(3).png" width="64" alt="Breadboard mascot" /></p>

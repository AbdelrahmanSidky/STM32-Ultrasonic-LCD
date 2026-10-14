# STM32 Bare-Metal Ultrasonic Distance Meter with LCD

I made this project to measure distance using an HC-SR04 ultrasonic sensor and show the reading live on a 16x2 character LCD. 

Everything here is written completely bare-metal in C using direct register access on the STM32F103C8T6 (Blue Pill). I did not use the STM32 HAL libraries for this because I think writing directly to registers helps you understand what the hardware is actually doing under the hood.

![Project Setup](images/proj1.jpg)

## Why I Built It This Way

One reason I wrote this from scratch is to build solid low-level drivers that I can reuse in other projects, like a robot car or an obstacle avoidance system. 

Another thing is timing accuracy. Ultrasonic sensors depend heavily on precise microsecond timing to measure the sound echo pulse. By setting up the hardware timer directly, I know exactly when the counter starts, stops, and resets without any library overhead getting in the way.

## Hardware Used

* **STM32F103C8T6 (Blue Pill)** running at 8 MHz
* **HC-SR04 Ultrasonic Sensor**
* **16x2 Character LCD (HD44780 controller)** running in 4-bit mode
* **ST-Link V2** for flashing and debugging
* **1 kΩ resistor** connected between LCD pin 3 (VO) and GND for contrast control (I did not have a potentiometer on hand, and 1 kΩ works great to keep the characters readable)

## Pin Connections

### Ultrasonic Sensor (HC-SR04)
* **VCC:** 5V
* **GND:** GND
* **TRIG:** Connected to your configured GPIO output pin
* **ECHO:** Connected to your configured GPIO input pin (make sure to use a 5V-tolerant pin on the STM32 or a simple voltage divider)

### 16x2 LCD (4-Bit Mode)
* **VSS (Pin 1):** GND
* **VDD (Pin 2):** 5V
* **VO (Pin 3):** 1 kΩ resistor to GND
* **RS (Pin 4):** Configured GPIO pin
* **RW (Pin 5):** Configured GPIO pin (or tied straight to GND)
* **EN (Pin 6):** Configured GPIO pin
* **D4–D7 (Pins 11–14):** Configured GPIO data pins
* **D0–D3:** Left unconnected
* **A / K (Pins 15 & 16):** Backlight 5V and GND

## How the Code Works

1. **Timer Setup:** I used General Purpose Timer 1. First, it generates an accurate 10 µs pulse on the TRIG pin to tell the sensor to send its ultrasonic chirp.
2. **Echo Timing:** When the ECHO pin goes HIGH, the timer starts counting. When ECHO drops back to LOW, the timer stops. Because the clock runs at 8 MHz, dividing the counter ticks by 8 gives the exact pulse duration in microseconds.
3. **Distance Calculation:** Sound travels back and forth, so taking microseconds divided by 58 gives the distance straight in centimeters. I capped the check around 100 cm because beyond that, these cheap sensors tend to get noisy and bounce around.
4. **LCD Driver:** The LCD runs in 4-bit mode to save board pins. I added a custom number-printing function that extracts digits and writes them directly to the display without losing trailing zeros or crashing on zero.

## How to Build and Run

1. Open **STM32CubeIDE**.
2. Go to **File -> Import -> Existing Projects into Workspace** and select this project folder.
3. Build the project using the hammer icon.
4. Connect your ST-Link V2 to the SWD pins on the Blue Pill and click **Run** or **Debug**.
5. Once flashed, the screen should light up and show `Distance: X cm` right away.

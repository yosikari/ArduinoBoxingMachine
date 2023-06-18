# Arduino Boxing Machine

[![Boxing Machine](/img.jpeg)](https://www.youtube.com/watch?v=KghgIa7PZJ0)

This project utilizes an Arduino microcontroller to create a boxing machine that measures the speed of punches and displays the results on a 24x8 LED matrix screen. The system incorporates two IR movement sensors to detect the punches, calculates the time difference between the first and second detected movements, and maps the resulting speed to a score ranging from 0 to 999. The score is then displayed on the LED matrix screen.

## Demo Simulation

Check it out here: [Demo Simulation](https://wokwi.com/projects/367863724333201409)

## Components

To replicate this project, you will need the following components:

- Arduino board (e.g., Arduino Uno)
- 24x8 LED matrix screen (based on MAX7219)
- 2 IR movement sensors (e.g., PIR motion sensors)
- Jumper wires
- Power supply (according to the requirements of your components)

## Wiring

Connect the components as follows:

- Connect the IR movement sensors to digital input pins on the Arduino (for example, pins 3 and 4).
- Connect the LED matrix screen to the Arduino using the appropriate pins for data, clock, and load (refer to the manufacturer's instructions).
- Ensure proper power and ground connections for all components.

For a visual representation of the wiring connections, please refer to the circuit diagram associated with the project.

![Circuit Diagram](/circuit.jpeg)

## Installation

To set up and run the Arduino Boxing Machine, follow these steps:

1. Clone or download the project code from the GitHub repository: [https://github.com/yosikari/ArduinoBoxingMachine](https://github.com/yosikari/ArduinoBoxingMachine)
2. Open the Arduino IDE (Integrated Development Environment) on your computer.
3. Connect your Arduino board to your computer using a USB cable.
4. Open the project code (`.cpp` file) in the Arduino IDE.
5. Install any necessary libraries required for the LED matrix screen and the IR movement sensors (MD_Parola, MD_MAX72xx, SPI).
6. Verify and compile the code.
7. Upload the compiled code to your Arduino board.

## Usage

After uploading the code to your Arduino, follow these steps to use the Boxing Machine:

1. Connect the power supply to the Arduino.
2. Ensure the LED matrix screen is properly connected and powered.
3. Position the two IR movement sensors in suitable locations to detect punch movements.
4. Power on the Boxing Machine.
5. The LED matrix screen will display an initial screen or any setup instructions.
6. Stand in front of the sensors and prepare to throw a punch.
7. When the first movement sensor detects your punch, the system will start measuring the time.
8. Throw the punch, and when the second movement sensor detects the movement, the time difference will be calculated.
9. The system will map the time difference to a score between 0 and 999 using a predefined algorithm.
10. The resulting score will be displayed on the LED matrix screen.
11. Repeat steps 6-10 for subsequent punches.

## Contact Me
If you have any questions or feedback about the project, please feel free to reach me out at yosikari@gmail.com.

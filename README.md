# projet_Validation_electronique
Validation Électronique - ESP32 Pico Project
Description
This project is part of the embedded electronic design module, focusing on the validation of a custom electronic board based on the ESP32 Pico microcontroller. The board, initially designed using Altium Designer, integrates communication, measurement, and human-machine interaction features. The current phase involves testing the hardware, identifying and fixing defects, and developing embedded software (BLE communication, unit tests, graphical interface).
Objectives
Verify the overall functionality of the board.
Identify hardware defects related to routing or assembly.
Develop unit tests for each subsystem.
Ensure stable BLE communication between the ESP32 and an external terminal.
Design a user control graphical interface.
Document the validation process and results.
Project Structure
Day 1 (30/06/2025): PCB design initiation and error correction in Altium Designer (reduced errors from 500 to 18).
Day 2 (01/07/2025): Unit testing of LEDs, buzzer, thermistors (CTN), and INA237 sensor via serial monitor.
Day 3 (02/07/2025): Hardware inspection of boards #25-27-002 and #25-27-0005, fixing soldering issues and Rshunt configuration error.
Day 4 (03/07/2025): Implementation of stable BLE communication using the YNOV BLE Interface, testing all components successfully.
Features
Hardware: ESP32 Pico-based board with LEDs (GPIO14, GPIO15), buzzer (GPIO13), thermistors (GPIO25, GPIO26), and INA237 sensor (I2C, GPIO21/22).
Software: VS Code with PlatformIO for programming, BLE communication with a custom YNOV interface, and serial monitoring.
Testing: Unit tests for I/O, I2C, SPI, and sensor readings.
Installation
Clone the Repository:
git clone https://github.com/your-username/validation-electronique-esp32.git
Install Dependencies:
VS Code with the PlatformIO IDE extension.
Altium Designer (for PCB design, if licensed).
YNOV BLE Interface (download from the provided Git repository).
Hardware Setup:
Connect the ESP32 Pico board to a PC via USB.
Ensure proper power supply (3.3V).
Verify soldering of components (CTN, INA237, LEDs).
Configure PlatformIO:
Open the project folder in VS Code.
Install the ESP32 platform via PlatformIO by running pio platform install espressif32 in the terminal.
Build and upload the code using the PlatformIO toolbar (click the "Upload" icon).
Usage
Run unit tests via the serial monitor (115200 baud) within VS Code's PlatformIO interface for LEDs, buzzer, CTN, and INA237.
Use the YNOV BLE Interface to send commands (e.g., LED on/off, buzzer activation) and monitor sensor data.
Check the Difficulties Encountered section for known issues and solutions.
Difficulties Encountered
Issue
Cause
Impact
Solution
Incorrect INA237 readings
Wrong Rshunt value (0.05 Ω)
Incoherent current measurements
Updated to 0.0005 Ω via datasheet
Low voltage on board #25-27-0005
Defective power circuit
Unable to upload code
Resoldered components, confirmed 3.3V
ESP32 not detected by PC
Missing USB driver
Blocked code upload
Installed CH340/CP210x driver


Contributors
BOURAS Amar
ELOTMANI Nassima
HADJI Mourad
Intervenant: Dorian FOURNIER
License
MIT License (or specify your preferred license).
Acknowledgements
Thanks to Dorian FOURNIER for guidance and support throughout the project.



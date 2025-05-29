# Temperature Measurement Project Using LM35 Sensor

**Author:** Eyad  
**Created:** September 12, 2023

## Project Overview

This project reads temperature data from an LM35 temperature sensor connected to a microcontroller. The measured temperature is displayed continuously on an LCD screen.

## Features

- Reads analog temperature values from the LM35 sensor using ADC polling  
- Converts analog readings to temperature in degrees Celsius  
- Displays real-time temperature readings on the LCD  
- Uses interrupts globally enabled for better system management  
- Simple and continuous temperature monitoring  

## Code Functionality

- Initializes required peripherals: ports, LCD, ADC (for LM35 sensor), and global interrupts  
- Continuously reads temperature data in a polling manner  
- Displays the temperature value with the unit 'C' on the LCD screen  
- Updates the display every 500 milliseconds  

## Hardware Requirements

- Microcontroller with ADC and LCD interface  
- LM35 temperature sensor connected to an analog input pin  
- LCD display to show temperature values  
- Proper power supply and connections for all components  

## Usage

1. Connect the LM35 sensor to the microcontroller’s ADC input pin.  
2. Connect the LCD to the microcontroller for output display.  
3. Power the system and run the program.  
4. The LCD will continuously show the current temperature measured by the LM35 sensor.  

## Notes

- The temperature reading is updated every 500 milliseconds.  
- Interrupts are globally enabled, although the program mainly uses polling for ADC reading.  
- The project can be expanded to include alarms or control systems based on temperature thresholds.  

---

For any questions or suggestions, please contact the author.


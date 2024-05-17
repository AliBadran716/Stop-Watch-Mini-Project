# StopWatch Using AVR Microcontroller

## Overview
This project implements a simple stopwatch using an AVR microcontroller. The stopwatch can count seconds, minutes, and hours and display the time on a 7-segment display. It features start, stop, and reset functionalities, controlled via external interrupts.

## Features
- **Time Measurement**: The stopwatch can measure and display time in hours, minutes, and seconds.
- **Start/Stop Functionality**: The stopwatch can be started and stopped using external interrupts.
- **Reset Functionality**: The stopwatch can be reset to zero using an external interrupt.
- **Display**: Time is shown on a multiplexed 7-segment display.

## Components
- AVR microcontroller (e.g., ATmega16/32)
- 7-segment displays
- Push buttons for start, stop, and reset functions
- External clock source (if required)
- Resistors and capacitors for debouncing and stabilization

## Pin Configuration
- **7-Segment Display MUX Control**: PORTA (PA0 to PA5)
- **7-Segment Display Data**: PORTC (PC0 to PC3)
- **Start Button (INT0)**: PD2
- **Stop Button (INT1)**: PD3
- **Reset Button (INT2)**: PB2

## Usage
### Start the Stopwatch
Press the start button connected to INT2 to begin counting.

### Stop the Stopwatch
Press the stop button connected to INT1 to pause counting.

### Reset the Stopwatch
Press the reset button connected to INT0 to reset the time to 00:00:00.

## Code Explanation

### Initialization
- **Interrupt Initialization (`INT_init`)**: Configures external interrupts for start, stop, and reset buttons.
- **Timer Initialization (`TIMER1_init`)**: Configures Timer1 in CTC mode to generate an interrupt every second.

### Main Loop
- Continuously updates the 7-segment display with the current time.

### Interrupt Service Routines (ISR)
- **`ISR(TIMER1_COMPA_vect)`**: Increments the time every second.
- **`ISR(INT0_vect)`**: Resets the stopwatch.
- **`ISR(INT1_vect)`**: Stops the stopwatch.
- **`ISR(INT2_vect)`**: Starts the stopwatch.

### Display Function (`showNumber`)
- Updates the 7-segment display with the current time values.
  
Feel free to reach out if you have any questions or need further assistance.

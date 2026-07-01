# Smart Exam Hall Monitoring and Management System

An embedded systems project built on the **LPC2148 (ARM7)** microcontroller that automates examination timing, environmental monitoring, and status indication in an exam hall — reducing manual intervention and timing errors.

## Aim

To develop a Smart Exam Hall Monitoring System that automates examination timing, environmental monitoring, and status indication, thereby improving examination management efficiency.

## Objectives

- Display the current RTC time and room temperature on the LCD
- Allow examination duration configuration using a keypad
- Implement a countdown timer for examination management
- Display remaining examination time using two multiplexed 7-segment displays
- Provide Green, Yellow, and Red LED alerts based on remaining time
- Enable RTC editing and exam configuration via External Interrupt 0
- Implement Pause/Resume functionality via External Interrupt 1
- Continuously monitor and display room temperature using an LM35 sensor
- Automatically record examination start and end times using the RTC
- Reduce manual timing errors and improve exam hall monitoring efficiency

## Block Diagram

```
KEYPAD ────────┐
SWITCH1 ─(EINT0)─┤                  ├──▶ LCD
SWITCH2 ─(EINT1)─┤     LPC2148      ├──▶ SEGMENTS
LM35 ────(ADC)───┤     + RTC        ├──▶ GREEN LED
                 │                  ├──▶ YELLOW LED
                 │                  ├──▶ RED LED
                 └──────────────────┴──▶ BUZZER
```

## Hardware Requirements

- LPC2148 development board
- 16x2 LCD
- 4x4 matrix keypad
- Switches (x2)
- Seven-segment displays (x2, multiplexed)
- LM35 temperature sensor
- LEDs (Green, Yellow, Red)
- Buzzer
- USB-UART converter / DB-9 cable

## Software Requirements

- Embedded C programming
- Keil µVision (compiler/IDE)
- Proteus (simulation)
- Flash Magic (firmware flashing)

## Project Workflow

1. **Idle state:** LCD shows current RTC date/time and room temperature.
2. **Configuration mode (Switch-1 / EINT0):** Invigilator sets the RTC and configures exam duration via keypad.
3. **Exam start:** RTC logs the start time; countdown timer begins.
4. **During exam:** LCD shows time, temperature, and remaining duration; 7-segment displays show remaining minutes (00–99).
5. **Status alerts:**
   - 🟢 Green LED — more than 10 minutes remaining
   - 🟡 Yellow LED — final 10 minutes
   - 🔴 Red LED — final 1 minute
   - 🔔 Buzzer — sounds when countdown reaches zero
6. **Pause/Resume (Switch-2 / EINT1):** Pauses and resumes the countdown timer without losing elapsed time.
7. **Exam end:** RTC logs the end time automatically for administrative records.

## Repository Structure

```
Src/
├── ADC_pro.c        # ADC driver (LM35 temperature reading)
├── LM35.c            # LM35 sensor handling
├── TEST_RTC.c        # RTC test routines
├── delay.c           # Delay utilities
├── interrupt.c       # EINT0 / EINT1 handlers
├── kpm_pro.c         # Keypad matrix driver
├── lcd_pro.c         # LCD driver
├── seg_pro.c         # 7-segment multiplexing driver
├── time_dly_seg.c    # Timing/delay logic for segment display
├── mini_project.c    # Main application logic
├── defines.h
├── headers.h
├── lcd_defines.h
├── project_defines.h
└── types.h
```

## Getting Started

1. Clone the repository:
   ```
   git clone https://github.com/ashakimidi2518/Smart-exam-hall-monitoring-and-management-system-.git
   ```
2. Open the project in **Keil µVision**.
3. Build the project and generate the `.hex` file.
4. Flash to the LPC2148 board using **Flash Magic**, or simulate using **Proteus**.

## Notes

Code follows industry-standard embedded programming practices: modular structure, consistent naming conventions, and separation of drivers (ADC, LCD, keypad, segment, RTC) from application logic (`mini_project.c`).

# Smart Exam Hall Monitoring and Management System

An embedded systems project built on the **NXP LPC2148 (ARM7TDMI-S)** microcontroller that automates key aspects of exam-hall management — timing, room environment monitoring, and status alerts — using **Keil µVision** for firmware development and **Proteus ISIS** for circuit simulation.

---

## 📋 Overview

This project simulates a self-contained exam-hall controller that:
- Tracks exam time using a **Real-Time Clock (RTC)** and displays it on an LCD
- Reads room **temperature** via an **LM35** sensor through the on-chip ADC
- Accepts operator input (e.g. exam codes, start/stop commands) through a **4x4 matrix keypad**
- Displays live status (time, temperature, exam state) on a **16x2/20x4 character LCD** and a **7-segment display**
- Signals exam start/end and alerts via a **buzzer**
- Indicates system/exam status using **status LEDs** (Green / Yellow / Red)

> **Note:** The Proteus simulation schematic uses the **LPC2124** device model as a stand-in for the **LPC2148**, since the LPC2148 is not natively available in the Proteus component library. Pin-out and peripheral behavior are equivalent for the features used in this project.

---

## 🖥️ Circuit Diagram (Proteus ISIS)

![Circuit Diagram](assets/circuit_diagram.jpg)

**Key connections shown above:**

| Component | Function | Connected To |
|---|---|---|
| **U1 (LPC2124/LPC2148)** | Main microcontroller | Central controller for all peripherals |
| **LCD2 (LM044L)** | Character LCD display | Port 0 pins (RS, RW, E, D0–D7) — shows time, temperature, exam status |
| **Keypad (4x4 Matrix)** | User input | Rows A–D and Columns 1–4 mapped to Port 0/Port 1 GPIO pins |
| **U2 (LM35)** | Temperature sensor | ADC input (AIN) for room temperature monitoring |
| **7-Segment Display** | Numeric/timer display | Multiplexed via Port 1 GPIO pins |
| **BUZ1 (Buzzer)** | Audible alert | Driven via GPIO for exam start/end signals |
| **D1, D2, D3 (LEDs)** | Status indication (Green / Yellow / Red) | GPIO output pins |
| **R1, R2 (Pull-ups) + Push Buttons** | Manual control inputs | Interrupt/GPIO pins (EINT / general input) |

---

## 📂 Project Structure

```
src/
├── mini_project.c          # Main application entry point
├── defines.h / types.h     # Global definitions and type declarations
│
├── LCD Driver
│   ├── lcd.h
│   ├── lcd_def.h
│   └── lcd_pro.c
│
├── Keypad Matrix Driver
│   ├── kpm.h
│   ├── kpm_defines.h
│   └── kpm_pro.c
│
├── ADC / Temperature (LM35)
│   ├── ADC.h
│   ├── ADC_defines.h
│   ├── ADC_pro.c
│   ├── LM35.h
│   └── LM35.c
│
├── Real-Time Clock
│   ├── TEST_RTC.h
│   ├── TEST_RTC_defines.h
│   └── TEST_RTC.c
│
├── 7-Segment Display
│   ├── seg.h
│   ├── seg_defines.h
│   ├── seg_pro.c
│   ├── time_dly_seg.h
│   └── time_dly_seg.c
│
├── Interrupts
│   ├── interrupt.h
│   ├── interrupt_defines.h
│   └── intreputs.c
│
├── Timing Utilities
│   ├── delay.h
│   └── delay.c
│
└── LEDs
    └── led_defines.h
```

---

## 🛠️ Tools & Technologies

| Tool | Purpose |
|---|---|
| **Keil µVision** | Embedded C firmware development, compilation, and debugging |
| **Proteus ISIS** | Circuit design and real-time simulation |
| **NXP LPC2148 (ARM7TDMI-S)** | Target microcontroller |
| **Embedded C** | Firmware language |

---

## ⚙️ Peripherals Used

- **GPIO** — LED, buzzer, keypad row/column scanning
- **ADC** — LM35 temperature reading
- **RTC** — Real-time exam timing
- **External Interrupts (EINT)** — Push-button triggered events
- **Timers** — Delay generation and 7-segment display multiplexing

---

## ▶️ How to Run the Simulation

1. Open the project in **Keil µVision** and build `mini_project.c` to generate the `.hex` file.
2. Open the Proteus schematic (`.pdsprj`) file.
3. Load the generated `.hex` file into **U1 (LPC2124/LPC2148)** via its properties dialog.
4. Run the simulation — the LCD will initialize, the RTC will start ticking, and the keypad/LM35/7-segment/buzzer/LEDs will respond as programmed.

---

## 🚀 Features

- ✅ Real-time exam clock display
- ✅ Live room temperature monitoring
- ✅ Keypad-based input for exam control
- ✅ Visual (LCD + 7-segment + LED) and audible (buzzer) status feedback
- ✅ Modular, well-commented driver-based firmware architecture

---

## 👤 Author

**Asha Kimidi** — [ashakimidi2518](https://github.com/ashakimidi2518)

---

## 📄 License

This project is open for educational and academic use. Feel free to fork and build upon it.

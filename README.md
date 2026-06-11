# EcoLight Maestro – Time & Intensity Adaptive Street Light Automation

## Project Overview
EcoLight Maestro is an LPC2148-based smart street light automation system that controls street lighting based on real-time clock and ambient light intensity.

## Features
- Real-Time Clock (RTC) display
- Automatic day calculation from date
- LCD display of Time, Date, and Day
- Keypad-based RTC configuration
- LDR-based light intensity monitoring
- Automatic street light control
- Custom LCD symbols
- Interrupt-driven menu system

## Hardware Used
- LPC2148 ARM7 Microcontroller
- 16x2 LCD
- 4x4 Matrix Keypad
- LDR Sensor
- LED
- Push Button
- Proteus Simulation

## Software Used
- Embedded C
- Keil uVision
- Proteus 8 Professional

## Working
The system continuously displays time, date, and day on the LCD. The user can modify Hour, Minute, Second, Date, Month, and Year through a keypad menu. The day of the week is automatically recalculated whenever the date is changed. During nighttime (6 PM to 6 AM), the LDR monitors ambient light and automatically turns ON the street light when low light conditions are detected.

## Project Files
- Source Code (.c)
- Header Files (.h)
- Proteus Project (.pdsprj)
- Circuit Screenshot

## Author
Bhaskar

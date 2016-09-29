# Summary #
This repository contains code for a small project on a PIC-Microcontroller "PIC16F1825".
The aim of the project is to controll a 12-V-LED-Strip via PWM. The values for red, green and blue are received via USART.
Many files are created from MCC itself. MCC is a small tool for MPLAB-X for code-generation.

# Devices used #
- PIC16F1825
- 12-V-LED-Strip
- 12-V-Power-Supply
- USB-TTL-Transferer
- PICKIT 3 for programming

# USART-Command-String #
One command string is build this way: 创(rrr,ggg,bbb)创 where as 创(创 is ASCII-Sign 0x28,  创)创 is 0x29, 创,创 is 0x2C. rrr, ggg, bbb are each digits from ``0`` (0x30) to ``9`` (0x39) each. Minimum value for the whole value is 0 and maximum 255.

# IDE and compiling #
I used the IDE MPLAB-X and compiled with XC8 (v1.35). You can download the compiler from the Microchip-Homepage and select it after the installation in the IDE.
As the programmer I used PICkit 3.
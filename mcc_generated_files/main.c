/*
 * File:   main.c
 * Author: Frosty
 * Small program which receives via USART RGB-Values (r,g,b)\n
 * Created on 25. September 2016, 12:40
 */
#include "mcc.h"

/*
 * Pins used for USART and 3x PWM
 *        ________
 *   5V -|1  °  14|- GND
 *      -|2     13|- TX  (ICSPDAT)
 *      -|3     12|- RX  (ICSPCLK)
 *(VPP) -|4     11|- CCP3
 * CCP1 -|5     10|-
 *      -|6      9|- CCP4
 *      -|7______8|-
 */

// (r,g,b)\n 
// 01234567 = 8 chars/bytes
void loadPWMValues();

// Prototypes
void loadRedPWM(uint8_t value);
void loadGreenPWM(uint8_t value);
void loadBluePWM(uint8_t value);
void enableLED();
void disableLED();

void main(void) {
    SYSTEM_Initialize(); // Set up Microchip
    enableLED(); // Show State-LED

    // Set every PWM-Value to 0
    loadRedPWM(0);
    loadBluePWM(0);
    loadGreenPWM(0);
    uint8_t red, green, blue;
    char received;

    while (1) {
        // Small state machine
        received = getch();

        if (received == '(') {
            red = getch();
            received = getch();
            if (received == ',') {
                green = getch();
                received = getch();
                if (received == ',') {
                    blue = getch();
                    received = getch();
                    if (received == ')') {
                        loadRedPWM(red);
                        loadGreenPWM(green);
                        loadBluePWM(blue);
                        //printf("Completed\n");
                    } else {
                        printf("Z6: Missing )\n");
                    }
                } else {
                    printf("Z4: Missing ,\n");
                }
            } else {
                printf("Z2: Missing ,\n");
            }
        } else {
            printf("Z0: Missing (\n");
        }
    }

    disableLED(); //Shouldn't come here
    return;
}

void loadRedPWM(uint8_t value) {
    PWM4_LoadDutyValue(value);
}

void loadGreenPWM(uint8_t value) {
    EPWM1_LoadDutyValue(value);
}

void loadBluePWM(uint8_t value) {
    PWM3_LoadDutyValue(value);
}

void enableLED() {
    LATCbits.LATC0 = 1;
}

void disableLED() {
    LATCbits.LATC0 = 0;
}

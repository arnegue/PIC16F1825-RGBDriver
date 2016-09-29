/*
 * File:   main.c
 * Author: Frosty
 * Small program which receives via USART RGB-Values (rrr,ggg,bbb)\n
 * Created on 25. September 2016, 12:40
 */
#include "mcc.h"

/*
 * Pins used for USART and 3x PWM
 *        ________
 *   5V -|1  °  14|- GND
 *      -|2     13|- TX
 *      -|3     12|- RX
 *      -|4     11|- CCP3
 * CCP1 -|5     10|-
 *      -|6      9|- CCP4
 *      -|7______8|-
 */
#define ASCII_DIFFERENCE 48

#define BUFFER_SIZE 13
char serialBuffer[BUFFER_SIZE];
int bufferIndex = 0;

// Prototypes
void loadPWMValues();
void loadRedPWM(uint8_t value);
void loadGreenPWM(uint8_t value);
void loadBluePWM(uint8_t value);

void main(void) {
    SYSTEM_Initialize();
    
    // Set every PWM on 0
    PWM3_LoadDutyValue(0);
    PWM4_LoadDutyValue(0);
    EPWM1_LoadDutyValue(0);    
    
    while(1){
        // Receive Char
        char received = getch();
        if (received != '\n') {
            serialBuffer[bufferIndex] = received;
            bufferIndex++;            
            if (received == ')' && bufferIndex != 13) {
                printf("ErrorBI\n");
                bufferIndex = 0;
            }
            // If index reaches BUFFER_SIZE, the receive is completed
            if (bufferIndex == BUFFER_SIZE) {
                bufferIndex = 0;
                loadPWMValues();
            }
        }
    }
    return;
}

void loadRedPWM(uint8_t value){
    PWM3_LoadDutyValue(value);
}

void loadGreenPWM(uint8_t value){
    EPWM1_LoadDutyValue(value);    
}


void loadBluePWM(uint8_t value){
    PWM4_LoadDutyValue(value);
}


// Method which loads the new PWM-Values to LED-Strip
void loadPWMValues() {
    uint8_t r, g, b;
    if (serialBuffer[0] == '(' && serialBuffer[4] == ',' && serialBuffer[8] == ',' && serialBuffer[12] == ')') {
        r =  (serialBuffer[1]  - ASCII_DIFFERENCE) * 100;
        r += (serialBuffer[2]  - ASCII_DIFFERENCE) * 10;
        r += (serialBuffer[3]  - ASCII_DIFFERENCE);

        g =  (serialBuffer[5]  - ASCII_DIFFERENCE) * 100;
        g += (serialBuffer[6]  - ASCII_DIFFERENCE) * 10;
        g += (serialBuffer[7]  - ASCII_DIFFERENCE);

        b =  (serialBuffer[9]  - ASCII_DIFFERENCE) * 100;
        b += (serialBuffer[10] - ASCII_DIFFERENCE) * 10;
        b += (serialBuffer[11] - ASCII_DIFFERENCE);

        loadRedPWM(r);
        loadGreenPWM(g);
        loadBluePWM(b);
    } else {
        printf("ERROR_NUMBERS\n");
    }
}

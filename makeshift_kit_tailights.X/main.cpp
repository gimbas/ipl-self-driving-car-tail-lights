/* 
 * File:   main.cpp
 * Author: Rafael Silva
 *
 * Created on November 7, 2019
 */

// PIC32MX150F128B Configuration Bit Settings

// 'C' source line config statements

// DEVCFG3
// USERID = No Setting
#pragma config PMDL1WAY = OFF           // Peripheral Module Disable Configuration (Allow multiple reconfigurations)
#pragma config IOL1WAY = OFF            // Peripheral Pin Select Configuration (Allow multiple reconfigurations)

// DEVCFG2
#pragma config FPLLIDIV = DIV_12        // PLL Input Divider (12x Divider)
#pragma config FPLLMUL = MUL_24         // PLL Multiplier (24x Multiplier)
#pragma config FPLLODIV = DIV_256       // System PLL Output Clock Divider (PLL Divide by 256)

// DEVCFG1
#pragma config FNOSC = FRC              // Oscillator Selection Bits (Fast RC Osc (FRC))
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disabled)
#pragma config IESO = OFF               // Internal/External Switch Over (Disabled)
#pragma config POSCMOD = OFF            // Primary Oscillator Configuration (Primary osc disabled)
#pragma config OSCIOFNC = OFF           // CLKO Output Signal Active on the OSCO Pin (Disabled)
#pragma config FPBDIV = DIV_1           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/1)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config WINDIS = OFF             // Watchdog Timer Window Enable (Watchdog Timer is in Non-Window Mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled (SWDTEN Bit Controls))
#pragma config FWDTWINSZ = WINSZ_25     // Watchdog Timer Window Size (Window Size is 25%)

// DEVCFG0
#pragma config JTAGEN = OFF             // JTAG Enable (JTAG Disabled)
#pragma config ICESEL = ICS_PGx1        // ICE/ICD Comm Channel Select (Communicate on PGEC1/PGED1)
#pragma config PWP = OFF                // Program Flash Write Protect (Disable)
#pragma config BWP = OFF                // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF                 // Code Protect (Protection Disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>
#include "systick.h"
#include "spi.h"
#include "lights.h"

int main() 
{
    systick::init();
    
    TRISDbits.TRISD9 = 0;
    LATDbits.LATD9 = 1; 
    
    TRISDbits.TRISD8 = 0;
    LATDbits.LATD8 = 1; 
    
    TRISFbits.TRISF5 = 0; // PF5 output
    TRISFbits.TRISF6 = 0; // PF6 output
    
    RPF5R = 0b1000; // SDO1 PPS
    
    INTCONbits.MVEC = 1;
    asm volatile("ei"); // enable interrupts
    
    spi::init(SPI_MODE_0, 1000000);
    
    lights::init();
    
    for(;;)
    {
        static uint64_t last_blink = 0;
        if(systick::count > (last_blink + 500))
        {
            LATDbits.LATD9 ^= 1;
            last_blink = systick::count;
        }
        
        static uint64_t last_color_cycle = 0;
        if(systick::count > (last_color_cycle + 50))
        {
            static uint16_t color_map_index_red = 120, color_map_index_green = 0, color_map_index_blue = 240;

            lights::set(0, color_map[color_map_index_red], color_map[color_map_index_green], color_map[color_map_index_blue]);
            lights::set(1, color_map[color_map_index_red], color_map[color_map_index_green], color_map[color_map_index_blue]);
            lights::set(2, color_map[color_map_index_red], color_map[color_map_index_green], color_map[color_map_index_blue]);
            lights::set(3, color_map[color_map_index_red], color_map[color_map_index_green], color_map[color_map_index_blue]);
            lights::set(4, color_map[color_map_index_red], color_map[color_map_index_green], color_map[color_map_index_blue]);
            lights::set(5, color_map[color_map_index_red], color_map[color_map_index_green], color_map[color_map_index_blue]);
            lights::set(6, color_map[color_map_index_red], color_map[color_map_index_green], color_map[color_map_index_blue]);
            lights::set(7, color_map[color_map_index_red], color_map[color_map_index_green], color_map[color_map_index_blue]);
            
            lights::update();

            if(color_map_index_red >= 359) color_map_index_red = 0;
            else color_map_index_red++;
            
            if(color_map_index_green >= 359) color_map_index_green = 0;
            else color_map_index_green++;
            
            if(color_map_index_blue >= 359) color_map_index_blue = 0;
            else color_map_index_blue++;

            last_color_cycle = systick::count;
        }
        
        static uint32_t iterations = 0;
        if(iterations >= 1000000)
        {
            iterations = 0;
            LATDbits.LATD8 ^= 1;
        }    
        else iterations++;
        
    }
    
    return 0; // should never reach here
}
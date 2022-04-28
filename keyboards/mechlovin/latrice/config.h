/*
Copyright 2020 Team Mechlovin'

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x4D4C
#define MANUFACTURER    Mechlovin
#define PRODUCT         Mechlovin Latrice

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 4

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
#define MATRIX_ROW_PINS { B5, B6, C6, C7, F6 }
#define MATRIX_COL_PINS { B4, F7, F5, F4 }

#define DIODE_DIRECTION COL2ROW

/*
 * HD44780 LCD Display Configuration
 */

#define LCD_LINES           2     //< number of visible lines of the display
#define LCD_DISP_LENGTH    16     //< visibles characters per line of the display
#define LCD_IO_MODE      1            //< 0: memory mapped mode, 1: IO port mode
#if LCD_IO_MODE
#define LCD_PORT         PORTD        //< port for the LCD lines
#define LCD_DATA0_PORT   LCD_PORT     //< port for 4bit data bit 0
#define LCD_DATA1_PORT   LCD_PORT     //< port for 4bit data bit 1
#define LCD_DATA2_PORT   LCD_PORT     //< port for 4bit data bit 2
#define LCD_DATA3_PORT   LCD_PORT     //< port for 4bit data bit 3
#define LCD_DATA0_PIN    5            //< pin for 4bit data bit 0
#define LCD_DATA1_PIN    3            //< pin for 4bit data bit 1
#define LCD_DATA2_PIN    2            //< pin for 4bit data bit 2
#define LCD_DATA3_PIN    1            //< pin for 4bit data bit 3
#define LCD_RS_PORT      LCD_PORT     //< port for RS line        
#define LCD_RS_PIN       7            //< pin  for RS line        
#define LCD_RW_PORT      LCD_PORT     //< port for RW line        
#define LCD_RW_PIN       6            //< pin  for RW line        
#define LCD_E_PORT       LCD_PORT     //< port for Enable line     
#define LCD_E_PIN        4            //< pin  for Enable line    
#endif
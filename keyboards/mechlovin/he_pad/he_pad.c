/*
Copyright 2022 Stefan Sundin "4pplet" <4pplet@protonmail.com>

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

void board_init(void) {
    // Disable the PD peripheral in pre-init because its pins (B4, B6) are being used in the matrix:
    PWR->CR3 |= PWR_CR3_UCPD_DBDIS;
    // Call the corresponding _user() function (see https://docs.qmk.fm/#/custom_quantum_functions)
};

#ifdef RGB_MATRIX_ENABLE
const is31fl3733_led_t PROGMEM g_is31fl3733_leds[IS31FL3733_LED_COUNT] = {
    { 0, SW11_CS2,  SW10_CS2,  SW12_CS2 }, //D402
    { 0, SW11_CS3,  SW10_CS3,  SW12_CS3 }, //D403
    { 0, SW11_CS4,  SW10_CS4,  SW12_CS4 }, //D404
    { 0, SW11_CS5,  SW10_CS5,  SW12_CS5 }, //D405
    { 0, SW11_CS6,  SW10_CS6,  SW12_CS6 }, //D406
    { 0, SW11_CS7,  SW10_CS7,  SW12_CS7 }, //D407
    { 0, SW11_CS8,  SW10_CS8,  SW12_CS8 }, //D408
    { 0, SW11_CS9,  SW10_CS9,  SW12_CS9 }, //D409
    { 0, SW11_CS10, SW10_CS10, SW12_CS10 }, //D410
    { 0, SW11_CS11, SW10_CS11, SW12_CS11 }, //D411
    { 0, SW11_CS12, SW10_CS12, SW12_CS12 }, //D412
    { 0, SW11_CS13, SW10_CS13, SW12_CS13 }, //D413
    { 0, SW11_CS14, SW10_CS14, SW12_CS14 }, //D414
    { 0, SW11_CS15, SW10_CS15, SW12_CS15 }, //D415
    { 0, SW11_CS1,  SW10_CS1,  SW12_CS1 }, //D401
    { 0, SW8_CS4,  SW7_CS4,  SW9_CS4 }, //D420
    { 0, SW8_CS5,  SW7_CS5,  SW9_CS5 }, //D421
    { 0, SW8_CS6,  SW7_CS6,  SW9_CS6 }, //D422
    { 0, SW8_CS7,  SW7_CS7,  SW9_CS7 }, //D423
    { 0, SW8_CS8,  SW7_CS8,  SW9_CS8 }, //D424
    { 0, SW8_CS9,  SW7_CS9,  SW9_CS9 }, //D425
    { 0, SW8_CS10, SW7_CS10, SW9_CS10 }, //D426
    { 0, SW8_CS11, SW7_CS11, SW9_CS11 }, //D427
    { 0, SW8_CS12, SW7_CS12, SW9_CS12 }, //D428
    { 0, SW8_CS13, SW7_CS13, SW9_CS13 }, //D429
    { 0, SW8_CS14, SW7_CS14, SW9_CS14 }, //D430
    { 0, SW8_CS15, SW7_CS15, SW9_CS15 }, //D431
    { 0, SW11_CS16, SW10_CS16, SW12_CS16 }, //D416
    { 0, SW8_CS2,  SW7_CS2,  SW9_CS2 }, //D418
    { 0, SW8_CS3,  SW7_CS3,  SW9_CS3 }, //D419
    { 0, SW5_CS5,  SW4_CS5,  SW6_CS5 }, //D437
};

#define XXX NO_LED
led_config_t g_led_config = {
    {
    {   0,   2,   4,   6,   8,  10,  12 },
    {   1,   3,   5,   7,   9,  11, XXX },
    {  14,  16,  18,  20,  22,  24,  26 },
    {  15,  17,  19,  21,  23,  25,  13 },

    }, {
    {  0,0  }, { 16,0  }, { 32,0  }, { 48,0  }, { 65,0  }, { 81,0  }, { 97,0  }, {113,0  }, {129,0  }, {145,0  },
    {161,0  }, {178,0  }, {194,0  }, {218,0  }, {  4,16 }, { 24,16 }, { 40,16 }, { 57,16 }, { 73,16 }, { 89,16 },
    {105,16 }, {121,16 }, {137,16 }, {153,16 }, {170,16 }, {186,16 }, {202,16 }, {224,24 },
    }, {
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1
    }
};

#endif

/* Copyright 2022 Team Mechlovin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "obelisk.h"


#ifdef RGB_MATRIX_ENABLE
const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
    {0, B_1, A_1, C_1}, //D41
    {0, B_2, A_2, C_2},
    {0, B_3, A_3, C_3},
    {0, B_4, A_4, C_4},
    {0, B_5, A_5, C_5}, //D105

    {0, B_6, A_6, C_6}, //D77
    {0, B_7, A_7, C_7},
    {0, B_8, A_8, C_8},
    {0, B_9, A_9, C_9},
    {0, B_10, A_10, C_10}, //D106

    {0, E_1, D_1, F_1}, //D78
    {0, E_2, D_2, F_2},
    {0, E_3, D_3, F_3},
    {0, E_4, D_4, F_4},
    {0, E_5, D_5, F_5}, //D107

    {0, E_6, D_6, F_6}, //D79
    {0, E_7, D_7, F_7},
    {0, E_8, D_8, F_8},
    {0, E_9, D_9, F_9},
    {0, E_10, D_10, F_10}, //D108
    
    {0, H_1, G_1, I_1}, //D80
    {0, H_2, G_2, I_2},
    {0, H_3, G_3, I_3},
    {0, H_4, G_4, I_4},
    {0, H_5, G_5, I_5}, //D109

    {0, H_6, G_6, I_6}, //D81
    {0, H_7, G_7, I_7},
    {0, H_8, G_8, I_8},
    {0, H_9, G_9, I_9},
    {0, H_10, G_10, I_10}, //D110

    {0, K_6, J_6, L_6}, //D82
    {0, K_7, J_7, L_7},
    {0, K_8, J_8, L_8},
    {0, K_9, J_9, L_9},
    {0, K_10, J_10, L_10}, //D111 
};

led_config_t g_led_config = {
{
        // Key Matrix to LED Index
    {NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED},
    {NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED},
    {NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED},
    {NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED},
    {NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED},
    {NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED,    NO_LED},
}, {
        //LED Index to Physical Positon
  {0,  0},     {56,  0},      {112,  0},      {168,  0},      {224,  0},
  {0, 10},     {56, 10},      {112, 10},      {168, 10},      {224, 10},
  {0, 21},     {56, 21},      {112, 21},      {168, 21},      {224, 21},
  {0, 32},     {56, 32},      {112, 32},      {168, 32},      {224, 32},
  {0, 42},     {56, 42},      {112, 42},      {168, 42},      {224, 42},
  {0, 53},     {56, 53},      {112, 53},      {168, 53},      {224, 53},
  {0, 64},     {56, 64},      {112, 64},      {168, 64},      {224, 64},
    }, {
        4,            4,              4,              4,              4,
        4,            1,              1,              1,              4,
        4,            1,              1,              1,              4,
        4,            1,              1,              1,              4,
        4,            1,              1,              1,              4,
        4,            1,              1,              1,              4,
        4,            4,              4,              4,              4,
    } 
};

#endif
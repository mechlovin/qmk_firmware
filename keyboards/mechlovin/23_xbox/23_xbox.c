/* Copyright 2020 Team Mechlovin
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

#include "23_xbox.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
  //Key Matrix to LED Index
  {0,         1,         2,           3,          4,          5},
  {6,         7,         8,           9,          10,         11},
  {12,        13,        14,          15,         16,         17},
  {18,        19,        20,          21,         22,         23}
}, {
  //LED Index to Physical Positon
  {  0,  0},  { 45,  0},  { 89, 0 },  { 134, 0 },  { 179, 0},   { 224, 0},
  { 0,  21},  { 45, 21},  { 89, 21 }, { 134, 21},  { 179, 21},  {224, 21},
  {  0, 42},  { 45, 42},  { 89,42 },  { 134, 42},  { 179, 42},  { 224,42},
  { 0,  64},  { 45, 64},  { 89, 64 }, { 134, 64},  { 179,64},   {224, 64},               
}, {
  1,          1,          1,          1,          1,          1,
  1,          1,          1,          1,          1,          1,  
  1,          1,          1,          1,          1,          1,  
  1,          1,          1,          1,          1,          1, 
} };

#endif


// PERSISTENT MEMORY (PMEM) CONFIGURATION ----------------------------------------------------------
#ifdef VIA_ENABLE
// Declaring a type indicator_config that stores color and enabled state
typedef struct _indicator_config_t {
// H, S, V store the color values; func stores the function (caps lock, scroll, num, layer indication); index stores the RGB LED index; and enabled stores the enabled state
        uint8_t h;
        uint8_t s;
        uint8_t v;
        uint8_t func ;
        uint8_t index ;
        bool enabled;    
} indicator_config ;

/* List of functions:
    0x0000 CAPS LOCK
    0x0001 NUM LOCK
    0x0002 SCROLL LOCK
    0x0003 LAYER 0
    0x0004 LAYER 1
    0x0005 LAYER 2
    0x0006 LAYER 3
*/

// Declaring a keyboard_indicators type that stores the indicators states

typedef struct _keyboard_indicators_t {
    indicator_config ind1 ;
    indicator_config ind2 ;
    indicator_config ind3 ;
    indicator_config ind4 ;
    indicator_config ind5 ;
    indicator_config ind6 ;
    indicator_config ind7 ;
    indicator_config ind8 ;
    indicator_config ind9 ;
    indicator_config ind10 ;
    indicator_config ind11 ;
    indicator_config ind12 ;
    indicator_config ind13 ;
    indicator_config ind14 ;
    indicator_config ind15 ;
    indicator_config ind16 ;
    indicator_config ind17 ;
    indicator_config ind18 ;
    indicator_config ind19 ;
    indicator_config ind20 ;
    indicator_config ind21 ;
    indicator_config ind22 ;
    indicator_config ind23 ;
    indicator_config ind24 ;
} keyboard_indicators ;

int indicator_number = (int)sizeof(keyboard_indicators)/(int)sizeof(indicator_config) ;

// Checks if the available EECONFIG DATA SIZE is exactly the size as keyboard_indicators
_Static_assert(sizeof(keyboard_indicators) == EECONFIG_KB_DATA_SIZE, "Mismatch in keyboard indicators stored data");

// Declaring a new variable indicators of the type keyboard_indicators
keyboard_indicators indicators;
uint8_t* pIndicators = (uint8_t*)&indicators ; // Gets a pointer to the first indicator

// This function returns the pointer to an indicator given an index
indicator_config* get_indicator_p (int index) {
    return (indicator_config*) (pIndicators + sizeof(indicator_config)*index) ;
}

// Initializing persistent memory configuration: default values are declared and stored in PMEM
void eeconfig_init_kb(void) {
    // Default values: all indicators start at white, 150 (roughly 60%) brightness value. Indicators 1 and 2 are active by default. Indicators 3 and 4 are disabled.
    // INDICATOR 1: CAPS LOCK
    indicators.ind1.h = 240;
    indicators.ind1.s = 100;
    indicators.ind1.v = 255;
    indicators.ind1.func = 3;
    indicators.ind1.index = 0;
    indicators.ind1.enabled = false;

    // INDICATOR 2: SCROLL LOCK
    indicators.ind2.h = 240;
    indicators.ind2.s = 100;
    indicators.ind2.v = 255;
    indicators.ind2.func = 3;
    indicators.ind2.index = 1;
    indicators.ind2.enabled = false;

    // INDICATOR 3: NUM LOCK
    indicators.ind3.h = 240;
    indicators.ind3.s = 100;
    indicators.ind3.v = 255;
    indicators.ind3.func = 3;
    indicators.ind3.index = 2;
    indicators.ind3.enabled = false;

    // INDICATOR 4: LAYER 0
    indicators.ind4.h = 240;
    indicators.ind4.s = 100;
    indicators.ind4.v = 255;
    indicators.ind4.func = 3;
    indicators.ind4.index = 3;
    indicators.ind4.enabled = false;

    // INDICATOR 5: LAYER 1
    indicators.ind5.h = 240;
    indicators.ind5.s = 100;
    indicators.ind5.v = 255;
    indicators.ind5.func = 3;
    indicators.ind5.index = 4;
    indicators.ind5.enabled = false;

    // INDICATOR 6: LAYER 2
    indicators.ind6.h = 240;
    indicators.ind6.s = 100;
    indicators.ind6.v = 255;
    indicators.ind6.func = 3;
    indicators.ind6.index = 5;
    indicators.ind6.enabled = false;

    // INDICATOR 7: LAYER 3
    indicators.ind7.h = 240;
    indicators.ind7.s = 100;
    indicators.ind7.v = 255;
    indicators.ind7.func = 3;
    indicators.ind7.index = 6;
    indicators.ind7.enabled = false;

    // INDICATOR 8: LAYER 3
    indicators.ind8.h = 240;
    indicators.ind8.s = 100;
    indicators.ind8.v = 255;
    indicators.ind8.func = 3;
    indicators.ind8.index = 7;
    indicators.ind8.enabled = false;

    // INDICATOR 9: LAYER 3
    indicators.ind9.h = 240;
    indicators.ind9.s = 100;
    indicators.ind9.v = 255;
    indicators.ind9.func = 3;
    indicators.ind9.index = 8;
    indicators.ind9.enabled = false;

    // INDICATOR 10: LAYER 3
    indicators.ind10.h = 240;
    indicators.ind10.s = 100;
    indicators.ind10.v = 255;
    indicators.ind10.func = 3;
    indicators.ind10.index = 9;
    indicators.ind10.enabled = false;

    // INDICATOR 11: LAYER 3
    indicators.ind11.h = 240;
    indicators.ind11.s = 100;
    indicators.ind11.v = 255;
    indicators.ind11.func = 3;
    indicators.ind11.index = 10;
    indicators.ind11.enabled = false;

    // INDICATOR 12: LAYER 3
    indicators.ind12.h = 240;
    indicators.ind12.s = 100;
    indicators.ind12.v = 255;
    indicators.ind12.func = 3;
    indicators.ind12.index = 11;
    indicators.ind12.enabled = false;

    // INDICATOR 13: LAYER 3
    indicators.ind13.h = 240;
    indicators.ind13.s = 100;
    indicators.ind13.v = 255;
    indicators.ind13.func = 3;
    indicators.ind13.index = 12;
    indicators.ind13.enabled = false;

    // INDICATOR 14: LAYER 3
    indicators.ind14.h = 240;
    indicators.ind14.s = 100;
    indicators.ind14.v = 255;
    indicators.ind14.func = 3;
    indicators.ind14.index = 13;
    indicators.ind14.enabled = false;

    // INDICATOR 15: LAYER 3
    indicators.ind15.h = 240;
    indicators.ind15.s = 100;
    indicators.ind15.v = 255;
    indicators.ind15.func = 3;
    indicators.ind15.index = 14;
    indicators.ind15.enabled = false;

    // INDICATOR 16: LAYER 3
    indicators.ind16.h = 240;
    indicators.ind16.s = 100;
    indicators.ind16.v = 255;
    indicators.ind16.func = 3;
    indicators.ind16.index = 15;
    indicators.ind16.enabled = false;

    // INDICATOR 17: LAYER 3
    indicators.ind17.h = 240;
    indicators.ind17.s = 100;
    indicators.ind17.v = 255;
    indicators.ind17.func = 3;
    indicators.ind17.index = 16;
    indicators.ind17.enabled = false;

    // INDICATOR 18: LAYER 3
    indicators.ind18.h = 240;
    indicators.ind18.s = 100;
    indicators.ind18.v = 255;
    indicators.ind18.func = 3;
    indicators.ind18.index = 17;
    indicators.ind18.enabled = false;

    // INDICATOR 19: LAYER 3
    indicators.ind19.h = 240;
    indicators.ind19.s = 100;
    indicators.ind19.v = 255;
    indicators.ind19.func = 3;
    indicators.ind19.index = 18;
    indicators.ind19.enabled = false;

    // INDICATOR 20: LAYER 3
    indicators.ind20.h = 240;
    indicators.ind20.s = 100;
    indicators.ind20.v = 255;
    indicators.ind20.func = 3;
    indicators.ind20.index = 19;
    indicators.ind20.enabled = false;

    // INDICATOR 20: LAYER 3
    indicators.ind21.h = 240;
    indicators.ind21.s = 100;
    indicators.ind21.v = 255;
    indicators.ind21.func = 3;
    indicators.ind21.index = 20;
    indicators.ind21.enabled = false;

    // INDICATOR 22: LAYER 3
    indicators.ind22.h = 240;
    indicators.ind22.s = 100;
    indicators.ind22.v = 255;
    indicators.ind22.func = 3;
    indicators.ind22.index = 21;
    indicators.ind22.enabled = false;

    // INDICATOR 23: LAYER 3
    indicators.ind23.h = 240;
    indicators.ind23.s = 100;
    indicators.ind23.v = 255;
    indicators.ind23.func = 3;
    indicators.ind23.index = 22;
    indicators.ind23.enabled = false;

    // INDICATOR 24: LAYER 3
    indicators.ind24.h = 240;
    indicators.ind24.s = 100;
    indicators.ind24.v = 255;
    indicators.ind24.func = 3;
    indicators.ind24.index = 23;
    indicators.ind24.enabled = false;

    // Write default value to EEPROM now
    eeconfig_update_kb_datablock(&indicators);
}

void rgb_matrix_startup(void) {
    rgb_matrix_disable_noeeprom();
    wait_ms(20);
    rgb_matrix_reload_from_eeprom();
    rgb_matrix_enable_noeeprom();
}

// At the keyboard start, retrieves PMEM stored configs
void keyboard_post_init_kb(void) {
    debug_enable = true;
    debug_matrix = true;
    rgb_matrix_startup();
    eeconfig_read_kb_datablock(&indicators);
    rgb_matrix_indicators_kb();
}

bool set_indicator(indicator_config indicator) {
    switch (indicator.func)
    {
        case 0: // If indicator is set as caps lock
        {
            if (host_keyboard_led_state().caps_lock) return true;
        }
        case 1: // If indicator is set as num lock
        {
            if (host_keyboard_led_state().num_lock) return true;
        }
        case 2: // If indicator is set as scroll lock
        {
            if (host_keyboard_led_state().scroll_lock) return true;
        }
        case 3: // If indicator is set as layer 0
        case 4:
        case 5:
        case 6:
        {
            if ( IS_LAYER_ON( (int)(indicator.func) - 3  ) ) return true;
        }
        default:
        {
            return false;
        }
    }
    return false;
}

HSV return_indicator_hsv (indicator_config indicator){
    return (HSV){indicator.h, indicator.s, indicator.v};
}

// INDICATOR CALLBACK ------------------------------------------------------------------------------
bool rgb_matrix_indicators_kb(void) {
    // First decides if action is needed. If a user code is defined, or the indicator is disabled, then does not act.
    if (!rgb_matrix_indicators_user()) return false;

    RGB rgb_current_indicator ;
    indicator_config* current_indicator_p ;
    int index ;

    for (index = 0 ; index < indicator_number ; index++) {
        current_indicator_p = get_indicator_p(index) ;
        if (current_indicator_p -> enabled) {
            rgb_current_indicator = hsv_to_rgb(return_indicator_hsv( *(current_indicator_p) ));
            if (set_indicator( *(current_indicator_p)) ) rgb_matrix_set_color( current_indicator_p -> index, rgb_current_indicator.r, rgb_current_indicator.g, rgb_current_indicator.b);
            else rgb_matrix_set_color(current_indicator_p -> index, 0, 0, 0);
       }
    }
    return true;
}

// VIA CONFIGURATION -------------------------------------------------------------------------------
enum via_indicator_color {
    id_ind1_enabled = 1,
    id_ind1_brightness = 2,
    id_ind1_color = 3,
    id_ind1_func = 4,
    id_ind1_index = 5,
//
    id_ind2_enabled = 6,
    id_ind2_brightness = 7,
    id_ind2_color = 8,
    id_ind2_func = 9,
    id_ind2_index = 10,
//
    id_ind3_enabled = 11,
    id_ind3_brightness = 12,
    id_ind3_color = 13,
    id_ind3_func = 14,
    id_ind3_index = 15,
//
    id_ind4_enabled = 16,
    id_ind4_brightness = 17,
    id_ind4_color = 18,
    id_ind4_func = 19,
    id_ind4_index = 20,
//
    id_ind5_enabled = 21,
    id_ind5_brightness = 22,
    id_ind5_color = 23,
    id_ind5_func = 24,
    id_ind5_index = 25,
//
    id_ind6_enabled = 26,
    id_ind6_brightness = 27,
    id_ind6_color = 28,
    id_ind6_func = 29,
    id_ind6_index = 30,
//
    id_ind7_enabled = 31,
    id_ind7_brightness = 32,
    id_ind7_color = 33,
    id_ind7_func = 34,
    id_ind7_index = 35,
//
    id_ind8_enabled = 36,
    id_ind8_brightness = 37,
    id_ind8_color = 38,
    id_ind8_func = 39,
    id_ind8_index = 40,
//
    id_ind9_enabled = 41,
    id_ind9_brightness = 42,
    id_ind9_color = 43,
    id_ind9_func = 44,
    id_ind9_index = 45,
//
    id_ind10_enabled = 46,
    id_ind10_brightness = 47,
    id_ind10_color = 48,
    id_ind10_func = 49,
    id_ind10_index = 50,
//
    id_ind11_enabled = 51,
    id_ind11_brightness = 52,
    id_ind11_color = 53,
    id_ind11_func = 54,
    id_ind11_index = 55,
//
    id_ind12_enabled = 56,
    id_ind12_brightness = 57,
    id_ind12_color = 58,
    id_ind12_func = 59,
    id_ind12_index = 60,
//
    id_ind13_enabled = 61,
    id_ind13_brightness = 62,
    id_ind13_color = 63,
    id_ind13_func = 64,
    id_ind13_index = 65,
//
    id_ind14_enabled = 66,
    id_ind14_brightness = 67,
    id_ind14_color = 68,
    id_ind14_func = 69,
    id_ind14_index = 70,
//
    id_ind15_enabled = 71,
    id_ind15_brightness = 72,
    id_ind15_color = 73,
    id_ind15_func = 74,
    id_ind15_index = 75,
//
    id_ind16_enabled = 76,
    id_ind16_brightness = 77,
    id_ind16_color = 78,
    id_ind16_func = 79,
    id_ind16_index = 80,
//
    id_ind17_enabled = 81,
    id_ind17_brightness =82,
    id_ind17_color = 83,
    id_ind17_func = 84,
    id_ind17_index = 85,
//
    id_ind18_enabled = 86,
    id_ind18_brightness = 87,
    id_ind18_color = 88,
    id_ind18_func = 89,
    id_ind18_index = 90,
//
    id_ind19_enabled = 91,
    id_ind19_brightness = 92,
    id_ind19_color = 93,
    id_ind19_func = 94,
    id_ind19_index = 95,
//
    id_ind20_enabled = 96,
    id_ind20_brightness = 97,
    id_ind20_color = 98,
    id_ind20_func = 99,
    id_ind20_index = 100,
//
    id_ind21_enabled = 101,
    id_ind21_brightness = 102,
    id_ind21_color = 103,
    id_ind21_func = 104,
    id_ind21_index = 105,
//
    id_ind22_enabled = 106,
    id_ind22_brightness = 107,
    id_ind22_color = 108,
    id_ind22_func = 109,
    id_ind22_index = 110,
//
    id_ind23_enabled = 111,
    id_ind23_brightness = 112,
    id_ind23_color = 113,
    id_ind23_func = 114,
    id_ind23_index = 115,
//
    id_ind24_enabled = 116,
    id_ind24_brightness = 117,
    id_ind24_color = 118,
    id_ind24_func = 119,
    id_ind24_index = 120,
};

#define INDICATOR_PROPERTY_NUMBER 5

int indi_index;
int data_index;
void indicator_config_set_value( uint8_t *data )
{
    // data = [ value_id, value_data ]
    uint8_t *value_id;
    value_id = &(data[0]);
    uint8_t *value_data = &(data[1]);

    /* Suppose that the brightness value of indicator 3 is being changed; then

       index = (12-1)/INDICATOR_PROPERTY_NUMBER = (12-1)/5 = 2 (integer division!), which indeed relates to indicator 3 (ind1 is 0, ind2 is 1 etc)
       data_index = (12 - index*INDICATOR_PROPERTY_NUMBER) = 12 - 2*5 = 2, which indeed relates to a brightness setting (0 is for enabled, 1 for brightness, 2 for color and 3 for func)

       Therefore, the basic idea is that index is about which indicator the set_value is about, and data_index about what indicator property it is
    */
    indi_index = ( (int)(*value_id) - 1) / (int)INDICATOR_PROPERTY_NUMBER;
    data_index = (int)(*value_id) - indi_index*(int)INDICATOR_PROPERTY_NUMBER;
    indicator_config* current_indicator_p = get_indicator_p(indi_index);
    switch ( data_index )
    {
        case 1 :
        {
                current_indicator_p -> enabled = value_data[0];
                break;
        }
        case 2 :
        {
                current_indicator_p -> v = value_data[0];
                break;
        }
        case 3:
        {
                current_indicator_p -> h = value_data[0];
                current_indicator_p -> s = value_data[1];
                break;
        }
        case 4:
        {
                current_indicator_p -> func = value_data[0];
                break;
        }
        case 5:
        {
                current_indicator_p -> index = value_data[0];
                break;
        }
    }
    // Run callback after update
    rgb_matrix_indicators_kb();
}


void indicator_config_get_value( uint8_t *data )
{
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    indi_index = ( (int)(*value_id) - 1) / (int)INDICATOR_PROPERTY_NUMBER;
    data_index = (int)(*value_id) - indi_index*(int)INDICATOR_PROPERTY_NUMBER;
    indicator_config* current_indicator_p = get_indicator_p(indi_index);
    switch ( data_index )
    {
        case 1:
        {
            value_data[0] =  current_indicator_p -> enabled;
            break;
        }
        case 2:
        {

            value_data[0] = current_indicator_p -> v;
            break;
        }
        case 3:
        {

            value_data[0] = current_indicator_p -> h;
            value_data[1] = current_indicator_p -> s;
            break;
        }
        case 4:
        {

            value_data[0] = current_indicator_p -> func;
            break;
        }
        case 5:
        {

            value_data[0] = current_indicator_p -> index;
            break;
        }
    }
}

void indicator_config_save(void)
{
    eeconfig_update_kb_datablock(&indicators);
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if ( *channel_id == id_custom_channel ) {
        switch ( *command_id )
        {
            case id_custom_set_value:
            {
                indicator_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value:
            {
                indicator_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save:
            {
                indicator_config_save();
                break;
            }
            default:
            {
                // Unhandled message.
                *command_id = id_unhandled;
                break;
            }
        }
        return;
    }

    *command_id = id_unhandled;
}
#endif // VIA_ENABLE
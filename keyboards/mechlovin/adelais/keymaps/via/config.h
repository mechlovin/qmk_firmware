/*
Copyright 2021 Mechlovin' Studio

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

#define PRODUCT_ID   0xAD03

#define OLED_BRIGHTNESS 20

#ifndef IOS_DEVICE_ENABLE
  // USB_MAX_POWER_CONSUMPTION value for this keyboard
  #define USB_MAX_POWER_CONSUMPTION 400
#else
  // fix iPhone and iPad power adapter issue
  // iOS device need lessthan 100
  #define USB_MAX_POWER_CONSUMPTION 100
#endif

#ifdef RGBLIGHT_ENABLE
  #ifndef IOS_DEVICE_ENABLE
    #define RGBLIGHT_VAL_STEP 17
  #else
    #define RGBLIGHT_LIMIT_VAL 35
    #define RGBLIGHT_VAL_STEP 4
  #endif
  #ifndef RGBLIGHT_HUE_STEP
    #define RGBLIGHT_HUE_STEP 10
  #endif
  #ifndef RGBLIGHT_SAT_STEP
    #define RGBLIGHT_SAT_STEP 17
  #endif
#endif
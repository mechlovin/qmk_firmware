/*
Copyright 2026 Mechlovin' Studio

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

#define BLOCKER_LED_COUNT 4
#define UG_LED_COUNT      RGBLIGHT_LED_COUNT - BLOCKER_LED_COUNT

// Fixed LED indices
#define CAPS_LED_INDEX    30
#define BLOCKER_LED_INDEX 14

// EECONFIG: 5 indicator_config × 6 bytes = 30 bytes
#define EECONFIG_KB_DATA_SIZE (5 * 6)

#define WEAR_LEVELING_LOGICAL_SIZE 2048
#define WEAR_LEVELING_BACKING_SIZE 4096

#define RGB_FADE_ENABLE
#define RGB_FADE_OUT_MS   20
#define RGB_FADE_IN_MS    200
#define RGB_FADE_POWER_STEP  12
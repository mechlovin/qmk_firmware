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

#ifdef RGBLIGHT_ENABLE
#define BLOCKER_LED_COUNT 3
#define INDICATOR_COUNT   BLOCKER_LED_COUNT
#define UG_LED_COUNT RGBLIGHT_LED_COUNT - BLOCKER_LED_COUNT

#define INDICATOR_START_INDEX   (UG_LED_COUNT + BLOCKER_LED_COUNT - INDICATOR_COUNT)

#define INDICATOR_CAPS_LED_INDEX    (INDICATOR_START_INDEX + 0)
#define INDICATOR_NUM_LED_INDEX     (INDICATOR_START_INDEX + 1)
#define INDICATOR_SCROLL_LED_INDEX  (INDICATOR_START_INDEX + 2)

// custom_rgblight_config_t (2 bytes) + indicator_config_t (10 bytes) = 12 bytes
#define EECONFIG_USER_DATA_SIZE 12
#endif


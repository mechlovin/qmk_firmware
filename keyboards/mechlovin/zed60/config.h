/*
Copyright 2022 Mechlovin'

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

#define WS2812_SPI_DRIVER SPID1 // default: SPID1
#define WS2812_SPI_MOSI_PAL_MODE 5 // MOSI pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 5

#define RGB_FADE_ENABLE
#define RGB_FADE_OUT_MS   20
#define RGB_FADE_IN_MS    200
#define RGB_FADE_POWER_STEP  12
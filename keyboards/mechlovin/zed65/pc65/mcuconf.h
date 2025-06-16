/* Copyright 2022 QMK
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

#pragma once

#include_next <mcuconf.h>

// Định nghĩa lại số endpoint cho OTG FS Device
#undef DWC2_USB_OTG_FS_NUM_EP
#define DWC2_USB_OTG_FS_NUM_EP      8   // EP0 + 7 cặp IN/OUT

// (Nếu ChibiOS version cũ hơn, có thể là:)
#undef STM32_OTG_FS_NUM_IN_EPS
#define STM32_OTG_FS_NUM_IN_EPS     7   // EP1–EP7 IN
#undef STM32_OTG_FS_NUM_OUT_EPS
#define STM32_OTG_FS_NUM_OUT_EPS    7   // EP1–EP7 OUT

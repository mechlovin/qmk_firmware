// Copyright %(YEAR)s %(YOUR_NAME)s (@%(USER_NAME)s)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define XXX KC_NO

#define LAYOUT( \
    K00, K02, K03, K04, K05, K06, K07, K08, K09, K69, K68, K67, K66, K65, K64, K63, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K79, K78, K77, K76, K75, K74, K73, K62, K61, K60, KB0, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K89, K88, K87, K86, K85, K84, K83, K72, K71, K70, KA0, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K99, K98, K96, K82, K81, K80, \
    K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, KA9, KA6, KA5, KA4, K92, K91, K90, KB1, \
    K50, K51, K52, K55, K58, K59, KB8, KB6, KB5, KB4, KB3, KA2, KA1  \
) { \
    { K00, XXX, K02, K03, K04, K05, K06, K07, K08, K09 }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19 }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29 }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39 }, \
    { K40, K41, K42, K43, K44, K45, K46, K47, K48, K49 }, \
    { K50, K51, K52, XXX, XXX, K55, XXX, XXX, K58, K59 }, \
    { K60, K61, K62, K63, K64, K65, K66, K67, K68, K69 }, \
    { K70, K71, K72, K73, K74, K75, K76, K77, K78, K79 }, \
    { K80, K81, K82, K83, K84, K85, K86, K87, K88, K89 }, \
    { K90, K91, K92, XXX, XXX, XXX, K96, XXX, K98, K99 }, \
    { KA0, KA1, KA2, XXX, KA4, KA5, KA6, XXX, XXX, KA9 }, \
    { KB0, KB1, XXX, KB3, KB4, KB5, KB6, XXX, KB8, XXX }, \
}

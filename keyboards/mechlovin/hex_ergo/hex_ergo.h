#include "quantum.h"
#include <stdint.h>
#include <stdbool.h>

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_16MHz       0x00


#define LAYOUT( \
    K00, K01,   K02, K03, K04, K05, K06, K07, K47,         K08, K09, K0A, K0B, K0C, K0D, K0E,      K58,   \
    K10, K11,   K12,    K13, K14, K15, K16, K17,        K18, K19, K1A, K1B, K1C, K1D, K1E, K1F,    K59,   \
    K20, K21,   K22,     K23, K24, K25, K26, K27,        K28, K29, K2A, K2B, K2C, K2D, K2F,        K5A,   \
    K30, K31,   K32,  K43, K33, K34, K35, K36, K37,         K38, K39, K3A, K3B, K3C, K3D,     K3E, K3F,   \
    K40, K41,   K42,         K44,  K45,  K46,            K48,          K49,    K4A,      K4E, K4F, K5B    \
) { \
    { K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B,   K0C,   K0D,   K0E,   KC_NO }, \
    { K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,   K1A,   K1B,   K1C,   K1D,   K1E,   K1F   }, \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B,   K2C,   K2D,   KC_NO, K2F   }, \
    { K30,   K31,   K32,   K33,   K34,   K35,   K36,   K37,   K38,   K39,   K3A,   K3B,   K3C,   K3D,   K3E,   K3F   }, \
    { K40,   K41,   K42,   K43,   K44,   K45,   K46,   K47,   K48,   K49,   K4A,   KC_NO, KC_NO, KC_NO, K4E,   K4F   }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K58,   K59,   K5A,   K5B,   KC_NO, KC_NO, KC_NO, KC_NO }, \
}

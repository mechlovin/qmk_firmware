
#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x4C4D  
#define PRODUCT_ID      0xE160  
// The official ErgoDone VID and PID are documented at http://pid.codes/1209/2328/.
#define DEVICE_VER      0x0001
#define MANUFACTURER    Mechlovin Studio
#define PRODUCT         Hex Ergo

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 16

#define TAPPING_TOGGLE  1

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

#define TAPPING_TERM    200
/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

#define USB_MAX_POWER_CONSUMPTION 500

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION
//#define DEBUG_MATRIX_SCAN_RATE

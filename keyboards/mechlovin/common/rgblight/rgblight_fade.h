#pragma once
#include "quantum.h"

#ifndef RGFL_FADE_IN_STEP
#    define RGFL_FADE_IN_STEP   1      // tăng 1 mỗi bước
#endif
#ifndef RGFL_FADE_INTERVAL
#    define RGFL_FADE_INTERVAL  4      // ms giữa mỗi bước
#endif

#ifdef __cplusplus
extern "C" {
#endif

void rgb_fade_init(void);
void rgb_fade_start(uint8_t target);
void rgb_fade_loop(void);

#ifdef __cplusplus
}
#endif

# Merisi Milleottocento

![milleottocento](Insert IMG)

milleottocento PCB, A 1800 Compact keyboard PCB.

* Keyboard Maintainer: [Mechlovin' Studio](https://mechlovin.studio/)
* Hardware Supported: Milleottocento
* Hardware Availability: [Mechlovin' Studio](https://mechlovin.studio/)

Make example for this keyboard (after setting up your build environment):

    make mechlovin/merisi/milleottocento:default_ansi

Flashing example for this keyboard:

    make mechlovin/merisi/milleottocento:default_ansi

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 4 ways:

* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.
* **Bootloader reset**: hold Backspace (1,14) key while plugging in (jump to bootloader)
* **Bootmagic reset**: hold ESC (0,0) key while pluging in (jump to bootloader and reset EEPROM)
* **Physical reset button**: Briefly press the button on the front of the PCB - some may have pads you must short instead
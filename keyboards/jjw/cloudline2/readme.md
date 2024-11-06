# tkl2

![tkl2]()

The TKL2 PCB, which compatible with TKL2 keyboard.

* Keyboard Maintainer: [Mechlovin' Studio](https://github.com/mechlovin)
* Hardware Supported: TKL2, STM32F103CBT6
* Hardware Availability: [Mechlovin' Studio](https://mechlovin.studio)

Make example for this keyboard (after setting up your build environment):

    make jjw/tkl2:default

Flashing example for this keyboard:

    make jjw/tkl2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 4 ways:

* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.
* **Bootloader reset**: hold BackSpace (1,13) key while plugging in (jump to bootloader)
* **Bootmagic reset**: hold ESC (0,0) key while pluging in (jump to bootloader and reset EEPROM)
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead

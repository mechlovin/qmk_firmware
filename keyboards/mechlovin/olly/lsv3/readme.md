# Olly lsv3

![Olly lsv3](https://i.imgur.com/lDMnyS4lh.png)

A replacement PCB for Duck lsv3 75% keyboard.

* Keyboard Maintainer: [Mechlovin' Studio](https://github.com/mechlovin)
* Hardware Supported: Duck lsv3, APM32F103
* Hardware Availability: [Olly lsv3](https://mechlovin.studio)

Make example for this keyboard (after setting up your build environment):

    make mechlovin/olly/lsv3:default

Flashing example for this keyboard:

    make mechlovin/olly/lsv3:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (Escape) and plug in the keyboard
* **Bootloader reset**: Hold down the key at (0,14) in the matrix (Backspace) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
* **Hardware reset**: Press reset button (located on the bottom side of the PCB) 

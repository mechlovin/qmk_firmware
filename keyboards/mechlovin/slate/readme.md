# Slate

![slate](https://i.imgur.com/ng09fJ9l.jpeg)

The PCB for Slate the FRL keyboard.

* Keyboard Maintainer: [Mechlovin' Studio](https://github.com/mechlovin)
* Hardware Supported: Slate, Atmega32u4
* Hardware Availability: [GB](https://geekhack.org/index.php?topic=115251.0).

Make example for this keyboard (after setting up your build environment):

    make mechlovin/slate:default

Flashing example for this keyboard:

    make mechlovin/slate:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

**Reset Key:** 3 ways to put the Slate into bootloader:
- By keycode: Tap RESET keycode.
- By bootmagic: hold ESC key while plugging in.
- By hardware: Push reset button on bottom of the PCB while the PCB is plugged in.
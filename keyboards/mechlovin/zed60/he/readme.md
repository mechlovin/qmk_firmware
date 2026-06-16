# Zed60-HE

An analog (Hall Effect) 60% keyboard with adjustable actuation point, Rapid Trigger, VIA and per-key RGB.

* Keyboard Maintainer: [Mechlovin'](https://github.com/mechlovin)
* Hardware Supported: STM32G431CBT6, 5× 74HC4067 analog multiplexers, IS31FL3741 RGB driver

Make example for this keyboard (after setting up your build environment):

    make mechlovin/zed60/he:default

Flashing example for this keyboard:

    make mechlovin/zed60/he:default:flash

## Hardware

* 5× 74HC4067 16-channel muxes — one IC per matrix row (IC1→row0 … IC5→row4),
  channel select = matrix column.
  * Channel-select lines S0–S3 → B11, B12, B14, B13 (shared)
  * COM of IC1–IC5 → A4, A5, A6, A7, B2 (all ADC2 inputs)
* IS31FL3741 RGB driver on I2C1 (SCL A15 / SDA B7), 63 per-key LEDs.

## Actuation & per-key Hall-effect settings

VIA is built in (keyboard-level — no separate `via` keymap). Per-key actuation
point, Rapid Trigger (press/release sensitivity, continuous), a live travel
visualizer and guided calibration are exposed over VIA custom channel 1 — use the
EC Tools tab in the Mechlovin configurator. `zed60_he_via.json` is the VIA design.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and
the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly hold the button on the back of the PCB whilst plugging in the keyboard.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if available.

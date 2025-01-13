
# Infinitec Macropad MKI

The Macropad MKI is the perfect companion for every desk. 
Beeing not the biggest or the most expenisve it shines with affordabilidy and the handmade style.

## Photos

![Macropad MKI](https://github.com/Donnervogel/vial-qmk/MKI.jpg)


## Setup the Env

clone the repo

```bash
  git clone https://github.com/Donnervogel/vial-qmk

```
```bash
   git submodule update --init --recursive

```
install requirements

```bash
   pip install -r requirements.txt

```
```bash
   sudo apt-get install -y gcc-arm-none-eabi gcc-avr avrdude dfu-programmer dfu-util

```
install qmk
```bash
   pip install qmk

```
setup qmk
```bash
   qmk setup

```
## Compile

Compile the firmware

```bash
  qmk compile -kb mki -lm imi
```


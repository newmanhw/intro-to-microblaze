# Baby's First SoC

## Overview
In this lab, you will learn how to put a processor onto your FPGA. You will then use this microprocessor to control some hardware that is on the FPGA, as well as learn how to handle some I/O components fully in software. This will definitely refresh your mind about microprocessors! Ideally, this will prepare you with some extra skills to use for your final project.

## Resources
Refer to the User Manual below for pin connections and peripherals you can use:
https://www.realdigital.org/doc/496fed57c6b275735fe24c85de5718c2

# Instructions

## Setting up the Microblaze

Make sure to select the `xc7s50csga324-1` as the FPGA part to target.

Please watch the following video for all setup instructions.
https://youtu.be/x__NwUMkB80?si=GMS5lMFyEwcl28UG

You will follow the entire tutorial and take a picture of your PuTTY terminal showing the text:
```
Starting Application
My name is <YOUR NAME>
```
along with the board having the LEDs mapped to the switches. Probably easiest to take this photo with your phone.

The starter code that is used in the video is located in `sw/example.c`. Make sure that you are able to get the basic LED application to work.

One thing I forgot to mention in the video is that writing to the AXI peripherals and APB peripherals are exactly the same. There is no difference in how you access them from the software perspective (as was shown with the switches being AXI and the LEDs being APB).
Note that the RGBs are also accessible via software, but they are are at an offset from the rest of the LEDs.
You can imagine that this APB component has 3 registers:

| Reg1 | Reg2 | Reg3 |
|------|-------|------|
| LEDS | RGB0 | RGB1 |
| 32 bits | 32 bits | 32 bits |
| [31:16] unused | [31:3] unused | [31:3] unused |
| BASEADDR | BASEADDR + 4*1 | BASEADDR + 4*2|

So, to write to RGB1, for example, you would write to LEDS Base address + 4*2 
You can add a #define at the top of your file like: 

`#define RGB1_ADDR LEDS_ADDR+4*2`

Then, you could write to the bottom 3 bits of that address (can send to the whole register but only bottom 3 are used).

Inspecting the code that was used for the LED APB component, you must now create your own APB component for the 16 switches, create your own IP for this, and showcase Task 3 working with your custom component (i.e. replace the AXI GPIO component).
Refer to: https://www.realdigital.org/doc/78e6f9b1a03ba4ca131ff3ba2e4dff3f
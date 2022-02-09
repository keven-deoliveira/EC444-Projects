# Code Readme

### timer.c 

The main program that drives the system.

Contains functions to:
- Drive servo motor
- Count down using timer & timer interrupts
- Drive alphanumeric display
- Handle buttons inputs & debouncing
- Use RTOS to run several tasks

___


### display.h 

Contains a data structure containing the alphanumeric font table, which is needed for showing appropriate values on the alphanumeric display.

___

Resources:
- https://github.com/BU-EC444/bu-ec444-whizzer/blob/Spring-2022/skills/timer.md
- https://github.com/BU-EC444/bu-ec444-whizzer/blob/Spring-2022/briefs/design-patterns/dp-timer.md
- https://github.com/BU-EC444/bu-ec444-whizzer/blob/Spring-2022/skills/rtos.md
- https://github.com/BU-EC444/code-examples/tree/master/i2c-display
- https://github.com/espressif/esp-idf/tree/master/examples/peripherals/mcpwm/mcpwm_servo_control
- https://github.com/adafruit/Adafruit_LED_Backpack/blob/master/Adafruit_LEDBackpack.cpp

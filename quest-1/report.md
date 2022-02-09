# Fish Feeder
Authors: Keven DeOliveira, Brian Jung, Fabio Amado

Date: 2022-02-08
-----

## Summary

The goal of Quest one was to create a "fish feeder" from the skills we have learned in cluster01. The objective includes having to spin the Servo right and left three times without chatter, displaying hours and minutes on the alphanumeric display, and showing each second countdown with no time loss.

We used what we learned in skill07 and set GPIO input and output pins to set up the button that allows the user to set up the hour for each interval. We used what we learned in skill08 to help set up the  display using Adafruit 14-segment Alphanumeric Display. We also used what we learned in skill09 to set up the servo to spin right and left three times. 

To understand the code in more detail, please go to [CODE README](https://link-url-here.org) in the code folder for more information. 

## Self-Assessment

### Objective Criteria

| Objective Criterion | Rating | Max Value  | 
|---------------------------------------------|:-----------:|:---------:|
| Servo spins right then left three times without chatter at prescribed time intervals | 1  |  1     | 
| Alphanumeric display indicates hours and minutes | 1 |  1     | 
| Display shows countdown time report every second with no time loss | 1 |  1     | 
| Food dispensed at specified times | 1 |  1     | 
| Demo delivered at scheduled time and report submitted in team folder with all required components | 1 |  1     | 
| NA |  |       | 
| Investigative question response | 1 |  1     | 


### Qualitative Criteria

| Qualitative Criterion | Rating | Max Value  | 
|---------------------------------------------|:-----------:|:---------:|
| Quality of solution | 4 |  5     | 
| Quality of report.md including use of graphics | 3 |  3     | 
| Quality of code reporting | 3 |  3     | 
| Quality of video presentation | 3 |  3     | 


## Solution Design

To improve the quality of the solution, we added a few more features to the "fish feeder" that we would like to highlight. First, to improve the user experience with the alphanumeric display, we added a minute and seconds display that begins at the last hour (ie. 1:00 to 59:59). This will not be confusing because the seconds will be constantly changing. Second, we added a "feed holder" from a pill bottle, tape and paper. The blue area includes holes, punctured with a thumbtack to act as the food dispenser. Lastly, we also added a manual button so that the user can input the hours for each new cycle or leave it to keep it constant. 

Initially, we wanted our system to have two buttons instead of one: one button to set the desired interval (in hours), and another to start the system once the user has set the interval. However, after several hours of developing and debugging, there were several issues that prevented us from moving forward with this design choice.

The first major issue that we encountered was one with the RTOS tasks and “unresolved watchdogs”. At first, these errors were difficult to understand and no research could provide much assistance. We tried to work with a TA as well on handling the issue, but we were unable to fix it. After some troubleshooting, Keven discovered that the issue was because of processes overlapping. To fix it, we set the priorities of the conflicting tasks as low as possible.

Fixing this first problem then introduced more issues, where tasks were being started infinitely as if in an infinite loop, almost causing Keven’s computer to crash. Unfortunately due to time constraints, we could not debug this issue. Instead, we compromised and kept a single button for setting intervals. Users are given ~10 seconds to set their interval, which seems to be an appropriate amount of time to set up to 24 hour intervals.


## Sketches and Photos
<center><img src="./images/Fish Feeder Circuit1.jpg" width="25%" /></center>  
<center> </center>

![alt text](https://github.com/BU-EC444/Jung-Homoon/blob/master/skills/cluster-0/02/images/skill02.png?raw=true)

## Supporting Artifacts
- [Press here to watch our video of the project!](https://drive.google.com/file/d/1Z3l409PpMPkjmaKKFfOX0v_C60dNzloV/view?usp=sharing)


## Modules, Tools, Source Used Including Attribution

Used Modules:
- <stdio.h>
- <string.h>
- "esp_types.h"
- "driver/gpio.h"
- "freertos/FreeRTOS.h"
- "freertos/task.h"
- "freertos/queue.h"
- "driver/periph_ctrl.h"
- "driver/timer.h"
- "driver/uart.h"
- "esp_vfs_dev.h"
- "driver/i2c.h"
- "sdkconfig.h"
- "esp_log.h"
- "driver/mcpwm.h"


## References
- https://github.com/BU-EC444/bu-ec444-whizzer/blob/Spring-2022/skills/timer.md
- https://github.com/BU-EC444/bu-ec444-whizzer/blob/Spring-2022/briefs/design-patterns/dp-timer.md
- https://github.com/BU-EC444/bu-ec444-whizzer/blob/Spring-2022/skills/rtos.md
- https://github.com/BU-EC444/code-examples/tree/master/i2c-display
- https://github.com/espressif/esp-idf/tree/master/examples/peripherals/mcpwm/mcpwm_servo_control
- https://github.com/adafruit/Adafruit_LED_Backpack/blob/master/Adafruit_LEDBackpack.cpp

-----


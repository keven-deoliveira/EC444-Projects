# Hurricane Box with Remote Access
Authors: Keven DeOliveira, Brian Jung, Aryton Reulet

Date: 2022-03-17
-----

## Summary

This project is the Hurricane Box, complete with remote access. The goal was to create a Hurricane Box using the skills we learned in cluster 3. The objectives of this assignment were to:

- Measure temperature, acceleration, and other values (in our case, the battery level)
- Send ESP32 sensor data over WiFi
- Remotely access through a portal to control an LED and to configure features at a remote client
- Include webcam sourcing video, embedded in a single portal window.

In order to complete our task, we made use of past skills to control a GPIO pin for the LED, toggling it between high and low depending on the state of the button on our HTML client. Using a UDP connection, we are able to send information between our server and our ESP32, communicating information to our frontend as well as the button toggle for the LED. We used the skills from this past cluster to drive the accelerometer and PiCamera. We also used skills from the last cluster to drive an ADC pin to control the thermistor.


## Self-Assessment

### Objective Criteria

| Objective Criterion | Rating | Max Value  | 
|---------------------------------------------|:-----------:|:---------:|
| Objective One | 1  |  1     | 
| Objective Two | 1 |  1     | 
| Objective Three | 1 |  1     | 
| Objective Four | 1 |  1     | 
| Objective Five | 1 |  1     | 
| Objective Six | 1 |  1     | 
| Objective Seven | 1 |  1     | 


### Qualitative Criteria

| Qualitative Criterion | Rating | Max Value  | 
|---------------------------------------------|:-----------:|:---------:|
| Quality of solution | 5 |  5     | 
| Quality of report.md including use of graphics | 3 |  3     | 
| Quality of code reporting | 3 |  3     | 
| Quality of video presentation | 3 |  3     | 


## Solution Design



## Sketches and Photos
![ESP32 Circuit](https://github.com/BU-EC444/Team13-DeOliveira-Jung-Reulet/blob/master/quest-3/images/IMG-0391.JPG)

![Rpi w/ camera](https://github.com/BU-EC444/Team13-DeOliveira-Jung-Reulet/blob/master/quest-3/images/IMG-0392.JPG)


## Supporting Artifacts
- [Link to video demo](). Not to exceed 120s


## Modules, Tools, Source Used Including Attribution

- Raspberry Pi
- ESP32
- Port Forwarding
- DDNS
- NodeJS
- Socket Programming (UDP)

## References

- Our past skills
- https://github.com/espressif/esp-idf/tree/master/examples/protocols/sockets/udp_client
- https://github.com/BU-EC444/code-examples/tree/Spring-2022/i2c-accel

-----


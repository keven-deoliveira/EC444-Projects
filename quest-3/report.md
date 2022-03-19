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

**What are steps you can take to make your device and system low power?**
There are a few ways to reduce the power required by the system. First we quickly realized that it is more efficent for both power and computation to bunch all the data together for sensor data. this way there are not multiple channels of communication required by opening up multiple servers. We, however, still wanted to decouple the to make sure other systems worked if one went down and split it in to three distinct components. Webcam, sensor data, and website. 
Another way to reduce power is to reduce the sampling rate, this way the system does not having to constantly be sampling in a high rate and instead can be sampling every second.
One other way the way UDP connection is set up. Right now we have a handshake where the client and server send and recieve data and need awknowledgement (a successful send and recieve) to move on. Instead we can have it constantly sending for the sensor data and only sending a ON OFF signal when the button is toggled.



## Self-Assessment

### Objective Criteria

| Objective Criterion | Rating | Max Value  | 
|---------------------------------------------|:-----------:|:---------:|
| Measures acceleration, temperature, and battery level | 1  |  1     | 
| Displays real-time data (temperature, vibration, battery level) at remote clinet via portal using separate IP network. | 1 |  1     | 
| Controls LED on box from remote client via portal. | 1 |  1     | 
| Sources web cam video into remote client. | 1 |  1     | 
| ESP32 and Rpi are connected wirelessly to router; ESP32 sensor data are delivered to local node server (on local laptop or Rpi) | 1 |  1     | 
| Demo delivered at scheduled time and report submitted in team folder with all required components | 1 |  1     | 
| Investigative question response | 1 |  1     | 


### Qualitative Criteria

| Qualitative Criterion | Rating | Max Value  | 
|---------------------------------------------|:-----------:|:---------:|
| Quality of solution | 5 |  5     | 
| Quality of report.md including use of graphics | 3 |  3     | 
| Quality of code reporting | 3 |  3     | 
| Quality of video presentation | 3 |  3     | 


## Solution Design

Our solution is real time, accurate and dynamic. The server recieves information from the sensors connected to the esp32 every second while also recieving a continuous stream from the raspberry pi camera. The server also sends an on/off signal to the esp32 on the same 1 second cycle to switch the LED on or off. Our server is listening to multiple ports to collect all of the information recieved from the sensors and camera. The server will parsect all the information all of the information being sent to it and create an HTML page with all the information in one location.

We port forwarded the server through a DDNS so that the HTML page that the server creates with all the calculated information and graphs will be accessable to any device anywhere.


## Sketches and Photos
![ESP32 Circuit](https://github.com/BU-EC444/Team13-DeOliveira-Jung-Reulet/blob/master/quest-3/images/IMG-0391.JPG)

![Rpi w/ camera](https://github.com/BU-EC444/Team13-DeOliveira-Jung-Reulet/blob/master/quest-3/images/IMG-0392.JPG)

![asdfasdf](https://user-images.githubusercontent.com/65934595/159101046-24356327-0413-46c5-86e1-1f86e271cd1d.png)

## Supporting Artifacts
- [https://drive.google.com/file/d/1Elb9Gx54p-Y0gLpIbjCmB6S_xfnUhwjJ/view?usp=sharing](). Not to exceed 120s


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


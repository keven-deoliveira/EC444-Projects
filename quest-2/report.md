# Quest Tactile Internet
Authors: Ayrton Reulet, Brian Jung, Keven DeOliveira

Date: 2022-2-23
-----

## Summary
This project is called Tactile Internet. 
The goal of this Quest was to create a "Tactile Internet" from the skills we have learned in cluster02. The objective includes having to read the values from all three ultrasonic sensor, thermistor, and the IR sensor. Once we are able to get data from these sensors to ESP32, we then display the values on the console as text. Then we save this console data to a file on our host as a txt. Finally we plot the data we are getting.

This project makes us use all the skills we learning in cluster02 and some from cluster01 such as setting GPIO input pins. We use skills 13,14,15 to connect all three sensors and just changing the input pins with the GPIO settings. Then we use node.js we learned from skill 16 to do all the backend parsing and processing. Finally we use skill 17 and canvas.js to display the incoming data in a live dynamic chart!

## Self-Assessment


### Objective Criteria

| Objective Criterion | Rating | Max Value  | 
|---------------------------------------------|:-----------:|:---------:|
| Periodic reporting of ultrasonic range in m | 1 |  1     | 
| Periodic reporting of IR range in m |  1  |  1     | 
| Periodic reporting of temperature in C | 1 |  1     | 
| Results displayed at host as text |  1  |  1     | 
| Results graphed at host continously based on reporting period |  1  |  1     | 
| Demo delivered at scheduled time and report submitted in team folder with all required components | 1  |  1     | 
| Investigative question response | 1 |  1     | 

| Objective Criterion | Rating | Max Value  | 
|---------------------------------------------|:-----------:|:---------:|
| Total objective criteria | 7 |  7     | 


### Qualitative Criteria

| Qualitative Criterion | Rating | Max Value  | 
|---------------------------------------------|:-----------:|:---------:|
| Quality of solution | 5 |  5     | 
| Quality of report.md including use of graphics | 3 |  3     | 
| Quality of code reporting | 3 |  3     | 
| Quality of video presentation | 3 |  3     | 

| Qualitative Criterion | Rating | Max Value  | 
|---------------------------------------------|:-----------:|:---------:|
| Total qualitative criteria | 14 |  14    | 

## Solution Design

Our solution is real time, accurate and dynamic. The chart updates every second with the newest data from all three sensors that also refresh every second. The graph shows the exact time the data was collected. On top of that, we made the code write to a log.txt file that also saves the timestamp and the data from all three sensors. Finally, to make our chart even easier to understand, we added a break in the middle so the distnace in m (usually fairly small) is zoomed in (scaled) and then we see the temperature in celsius that is relatively higher (~20). Please watch our video and read our code README!

Tabulate and compare the accuracy and speed of the IR and ultrasonic sensors. Which one would you prefer to use to support driving a robotic car?
It seems like IR sensor tends to fluctuate a lot more. We would prefer to use a ultrasonic sensor to support driving a robotic car. This makes sense because IR sensor uses reflected light can be relatively unreliable due to interfernce from other IR lights (for example sunlight). Ultrasonic sensors work using sound waves and its not affected by as many factors as the IR sensor.


## Sketches and Photos
![canvasjsQuest](https://user-images.githubusercontent.com/65934595/155830100-2183ba7a-5308-4093-adf1-b544c0c099b8.png)

![Circuit 1](https://github.com/BU-EC444/Team13-DeOliveira-Jung-Reulet/blob/master/quest-2/images/quest2%20pic1.jpg)

![Circuit 3](https://github.com/BU-EC444/Team13-DeOliveira-Jung-Reulet/blob/master/quest-2/images/quest2%20pic3.jpg)

## Supporting Artifacts

[LINK TO VIDEO](https://drive.google.com/file/d/1hqpNLqbCA_BrbYPr6pWUm23zb65npKQJ/view?usp=sharing)

## Modules, Tools, Source Used Including Attribution

- ADC Pins
- NodeJS
- SerialPort
- CanvasJS

## References

- https://canvasjs.com/javascript-charts/line-chart-axis-scale-breaks/
- https://canvasjs.com/html5-javascript-dynamic-chart/

-----


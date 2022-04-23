# Cruise Control
Authors: Keven DeOliveira, Brian Jung, Ayrton Reulet

Date: 2022-04-22
-----

## Summary

In this 

To understand the code in more detail, please go to [CODE README](https://github.com/BU-EC444/Team13-DeOliveira-Jung-Reulet/blob/master/quest-5/code/README.md) in the code folder for more information. 

### Investigative Question
How would you change your solution if you were asked to provide 'adaptive' cruise control?
Adaptive cruise control is when the vehicle's acceleration and braking is automatically controlled by monitoring other vehicles and objects on the road. It keeps a safe distance from the vehicle infront of you while keeping the speed of the vehicle steady.
In order to implement this, we just have to tweak our PID a little while adding more sensors for the car to be more "aware" of the surroundings. For example, the front LIDAR sensor sesnes distance of what is in front of you. In case of a wall - where the car sees that the distance value decreases over time - it stops the car when it senses 30cm (in order to account for momemtum). Now we need to add logic to see if the distance sensor infront is dynamic. Keep PID for cruise control (keeping the car going at 0.1m/s - 0.4m/s) until they sense that it is coming close to something. Then slow down but don't come to a halt and see if the distance increases. If the distance increase, logic tells us its most likely a car in front, then we can keep a safe distance using PID and cruise control. If it continues to decrease, then the car should come to a halt. 
Another way to implement this (while less possible real life, but very possible for ESP controlled crawlers) is to have the microcontrollers that control the speed of the crawlers to communicate with each other, through UDP or other wireless communication to send out heartbeats of the speed. This way the crawlers can all have the same speed.

## Self-Assessment

### Objective Criteria

| Objective Criterion | Rating | Max Value  | 
|---------------------------------------------|:-----------:|:---------:|
| Controls steering to maintain center of course +/- 25cm for entire length | 1 |  1     | 
| Uses PID for speed control holding a fixed speed setpoint after startup and before slowdown [0.1-0.4 m/s] | 1 |  1     | 
| Stops within 20cm of end without collision | 1 |  1     | 
| Start and stop instructions issued wirelessly from phone, laptop, or ESP | 1 |  1     | 
| Measures wheel speed or distance | 1 |  1     | 
| Uses alpha display to show current distance or speed | 1 |  1     | 
| Successfully traverses A-B in one go, no hits or nudges | 1 |  1     | 


### Qualitative Criteria

| Qualitative Criterion | Rating | Max Value  | 
|---------------------------------------------|:-----------:|:---------:|
| Quality of solution | 5 |  5     | 
| Quality of report.md including use of graphics | 3 |  3     | 
| Quality of code reporting | 3 |  3     | 
| Quality of video presentation | 3 |  3     | 


## Solution Design

Our design does everything the quest asks for and more! 

### How our solution went beyond in terms of quality.
First of all, we put a lot of effort to make the crawler not only functional in terms of meeting all the solution requirements but stylish. We have added a flag that read "Team 13" in the back as an added feature. On top of that we got a wooden plank that can host multiple breadboards as well as sensors. Instead of having just one sensor on the side (while we needed only one for this quest), we also added one on the other side so that the car was more "aware" of the surrounding.
As you can see from our stopping video (Linked in Supporting Artifacts), we also made our solution be able to stop within 10cm of the end of track without collision. This is a 2X improvement of the 20cm of end of track. 
Finally, you can also see 


## Sketches and Photos
<center><img src="./images/ece444.png" width="25%" /></center>  
<center> </center>


## Supporting Artifacts
- [https://drive.google.com/file/d/1kvqwCQBQP28MW1RcSRvF-KN-pCSozhlZ/view?usp=sharing](). Not to exceed 120s

UDP VIDEO: https://drive.google.com/file/d/18dYRJ_PFgDP6qInHt3qFe9l_b0fncPgg/view?usp=sharing
Stopping Video: https://drive.google.com/file/d/1I4LekqM_9tsAxEZcZT6NDzT9R9GB0hK-/view?usp=sharing
Everything Combined: https://drive.google.com/file/d/1I4LekqM_9tsAxEZcZT6NDzT9R9GB0hK-/view?usp=sharing


## Modules, Tools, Source Used Including Attribution

## References
- Cluster 5 skills
- Provided links in quest 5
- Provided links in cluster 5

-----


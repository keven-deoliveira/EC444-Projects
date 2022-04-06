# Electronic Voting
Authors: Keven DeOliveira, Ayrton Reulet, Brian Jung

Date: 2022-04-05
-----

## Summary

In this Electronic Voting quest, our goal was to create an electronic voting network where all votes would be securely accounted for and then sent to the main voting database to be tallied. All of the votes and who they were from were to be saved and displayed from the database to an HTML server where all the results of the past or current election could be cleared from the database with the press of a button (on the HTML frontend). 

To do this we used a combination of the knowledge we learned from IR RX/TX and Leader Election skills. We had to take the secure IR connection from the IR RX/TX skill and incorporate that as individual votes in an election. We made sure that any esp32 could vote to any one of the other five connected esp32s in the LAN including the current leader. Specifics of how this was done can be found in the README file. 

When an esp32 would cast a vote to a receiving esp32 the onboard LED would flash to indicate it had casted a vote. The receiving esp32 would also blink the onboard LED to indicate that it had received a vote. Once any esp32 had received a vote their job was to send that vote over UDP to the current leader. When the current leader received a vote its job was to forward that vote also through UDP to the raspberry pi server. It should be noted that the UDP message sent to the leader also carried the voter ID so that the database could store who was casting the vote. The leader also had to peridoically send out a heartbeat message so that all the esp32s were aware of who the leader is and that the current leader is still online. That way if the leader was disconnected either through power or off the network the first esp32 that noticed the lack of a heartbeat message would become the new leader and immediately send out a heartbeat pulse. Once the raspberry pi server had received the UDP message from the leader the information was stored in the database and updated to the HTML interface to display a vote had been casted along with who casted the vote color that was voted for.

There are of course security flaws involed with any sort of networking and connected systems, electronic voting is no exception. Here are a list of some potential ways that our voting system could be hacked:

1.) VOTING FRAUD - someone could hack into an esp and change the ID number to pretent to be voting as someone else. This would be like if someone voted under someone else's name.

2.) ADDITIONAL VOTING - Another esp could be logged on to the LAN of our network and cast a vote from a new voting ID. Maybe a vote from an unknown voter would be counted in an electronic voting election. This could also be done by changing a esp's ID that is already on the LAN to a new ID not accounted for.

3.) SECURITY BREACH - the database itself could be hacked into and artifically add votes for a specific color of the hackers choice; or for the same result votes already casted could be deleted from the database of certain colors that the hacker doesn't like.

4.) NETWORK OFFLINE - one easy way to stop the entire election process would be to take the router offline. Taking the router offline would stop all communication between both server and the leader, and also the voters and the leader.

5.) TAMPERING WITH EQUIPMENT - someone could tamper with the circuit of the fobs and maybe replace the IR with a white LED, broken IR, or even disconnect the transmission button. There are a whole lot of ways someone could change the circuit to not allow one or multiple of the esps to cast votes. There would also be no way for the leader or the server to know that the voting isn't working for certain esps.


## Self-Assessment

### Objective Criteria

| Objective Criterion | Rating | Max Value  | 
|---------------------------------------------|:-----------:|:---------:|
| Fob performs IR NFC data exchange of vote to another fob (LED indication) | 1 | 1 | 
| Receiving fob communicates vote to Poll Leader (LED indication) via network communciation | 1 | 1 | 
| Poll leader (LED indication) is replaced if fails | 1 | 1 | 
| Poll leader reports votes to server database | 1 | 1 | 
| Portal allows query to database to show actual vote counts per candidate | 1 | 1 | 
| Operates over multiple sites or with all avaliable fobs (up to 9) | 1 | 1 | 
| Investigative question response | 1 | 1 | 


### Qualitative Criteria

| Qualitative Criterion | Rating | Max Value  | 
|---------------------------------------------|:-----------:|:---------:|
| Quality of solution | 5 |  5     | 
| Quality of report.md including use of graphics | 3 |  3     | 
| Quality of code reporting | 3 |  3     | 
| Quality of video presentation | 3 |  3     | 


## Solution Design

We highly recommend looking at the code README that includes a lot of information about how everything was implementing and what libaries were used. This will give a better understanding of how the solution design was implemented. The code README is linked in the supporting artifact, or you can press on the code folder from the current directory.

## Sketches and Photos
<center><img src="./images/ece444.png" width="25%" /></center>  
<center> </center>


## Supporting Artifacts
- [Press here to watch the video demo!](https://drive.google.com/file/d/1_ilZExYNMJ1wD292D40Bi5A-SnDH0FJf/view)
- [Press here to go to the code README!](https://github.com/BU-EC444/Team13-DeOliveira-Jung-Reulet/blob/master/quest-4/code/README.md)


## Modules, Tools, Source Used Including Attribution

## References

-----


var app = require('express')();
var fs = require("fs");
const path = require("path");
var dgram = require("dgram");
const batteryLevel = require('battery-level');

// Predefine 
var payload = "";
var data = []; // Array to store payload data from UDP datagram
var buttonToggle;
var batteryLvl;

// Setting up server
var PORT = 3000;
var HOST = '192.168.1.112';
var server = dgram.createSocket('udp4');

app.get('/', (req,res) => {
    res.sendFile(__dirname + '/frontend.html')
})

app.get('/api', async (req, res) => {
    console.log(req.query.q);
    buttonToggle = req.query.q
    res.send("ok")
});

server.on('listening', function () {
    var address = server.address();
    console.log('UDP Server listening on ' + address.address + ":" + address.port);
});

var msgResponse = "OFF"
server.on('message', function (message, remote) {
    getBattery()
    if (typeof(batteryLvl) == "undefined") {batteryLvl = 0}

    if (buttonToggle == "ON") {
        msgResponse="ON";
    } else { msgResponse="OFF"}
    console.log(remote.address + ':' + remote.port +' - ' + message);

    newMessage = message.toString('utf-8');
    curData = newMessage.split(',');
    numArray = curData.map(Number);
    numArray.push(batteryLvl);
    
    console.log(numArray)
    app.get('/data', (req,res) => {
        app.emit('dataEvent');
        res.send(numArray)
    });

    server.send(msgResponse, 0, msgResponse.length, remote.port, remote.address, function(err, bytes) {
        if (err) throw err;
        console.log('UDP server message sent to ' + remote.address +':'+ remote.port);
    });

});

server.bind(PORT, HOST);

app.listen(42069, () => {
    console.log("go to http://localhost:42069/");
});

function getBattery() {
    batteryLevel().then(level => {
        batteryLvl = level
    });
}
var app = require('express')();
var http = require("http").Server(app);
const io = require("socket.io");
var fs = require("fs");

const { SerialPort, ReadlineParser  } = require("serialport");

var dataStream = []

app.get('/', (req,res) => {
    res.sendFile(__dirname + '/canvas.html')
})

function hello(arg) {

    pureData = arg.split("\r")[0]
    splitData = pureData.split(",")
    dataStream = [Number(splitData[0]),Number(splitData[1]),Number(splitData[2])]

    fs.appendFile('log.txt', `\n${dataStream[0]} , ${dataStream[1]} , ${dataStream[2]}`, function (err) {
        if (err) return console.log(err);
        console.log('Logged data: ', dataStream);
    });

    app.get('/data', (req,res) => {
        app.emit('dataEvent');
        res.send(dataStream)
    });

}


const port = new SerialPort({
    path:'COM5', 
    baudRate: 115200,
});

const parser = new ReadlineParser()
port.pipe(parser)
parser.on('data', hello)

app.listen(8080, () => {
    console.log("go to http://localhost:8080/");
});


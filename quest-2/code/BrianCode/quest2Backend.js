var app = require('express')();
var http = require("http").Server(app);

const { SerialPort, ReadlineParser  } = require("serialport");

var dataStream = []

app.get('/', (req,res) => {
    res.sendFile(__dirname + '/canvas.html')
})

function hello(arg) {
    // console.log(arg)
    pureData = arg.split("\r")[0]
    splitData = pureData.split(",")
    dataStream = [Number(splitData[0]),Number(splitData[1]),Number(splitData[2])]
    // dataStream.push(pureData.split(","))
    // console.log(dataStream)

    app.get('/data', (req,res) => {
        app.emit('dataEvent');
        res.send(dataStream)
    })
    console.log(dataStream)
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

const http = require('http');
const hostname = '127.0.0.1';
const port = 3000;
const server = http.createServer((req, res) => {
     res.statusCode = 200;
     res.setHeader('Content-Type', 'text/plain');
     res.end('Hello World\n'); });

server.listen(port, hostname, () => {
     console.log(`Server running at http://${hostname}:${port}/`);
});

var io = require('socket.io').listen(server); 
io.sockets.on('connection', socket);

var serialport = require("serialport");
var SerialPort = serialport.SerialPort;
var sp = new SerialPort("COM4", {
parser: serialport.parsers.readline("n"),
baudrate: 9600
});

sp.on("open", function() {
console.log('open');
});
sp.on('data', function(data) {
console.log('data received: ' + data);
});
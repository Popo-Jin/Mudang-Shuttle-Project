// app.js

// ......

var mongoose    = require('mongoose');

// ......

// [ CONFIGURE mongoose ]

// CONNECT TO MONGODB SERVER
var db = mongoose.connection;
db.on('error', console.error);
db.once('open', function(){
    // CONNECTED TO MONGODB SERVER
    console.log("Connected to mongod server");
});

mongoose.connect('mongodb+srv://dbamdin:admin1234!@cluster0-9wasi.mongodb.net/test?retryWrites=true&w=majority');

// ......
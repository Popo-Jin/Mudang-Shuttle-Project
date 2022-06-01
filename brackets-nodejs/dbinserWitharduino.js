var serialport = require('serialport');
var portName = "COM4";

var MongoClient = require('mongodb').MongoClient;
var url = "mongodb+srv://dbamdin:admin1234!@cluster0-9wasi.mongodb.net/test?retryWrites=true&w=majority";

var myPort = new serialport(portName, {
    baudRate:9600,
    parser: new serialport.parsers.Readline('\n')
});

var datas = '';
var resultdata = '';

myPort.on('data', function(data) {

    MongoClient.connect(url, function(err, db) {
      if (err) throw err;
      var dbo = db.db("mydb");
      /*dbo.createCollection("dbtest", function(err, res) {
        if (err) throw err;
        console.log("Collection created!");
      }); */
      if(data == '@') {
        console.log(datas.toString());

        //데이터만 뽑기 위해 자르는 부분
        
        resultdata = datas.slice(datas.indexOf(':')+1, datas.length);  
          
        console.log("result : " + resultdata.toString());
          
        if(datas.slice(0,datas.indexOf(':')) == "Lat") {
            dbo.collection('dbtest').insert({"Lat":resultdata});
        }
        else if(datas.slice(0,datas.indexOf(':')) == "Long") {
            dbo.collection('dbtest').insert({"Long":resultdata});
        }
          
        datas = '';
        resultdata = '';
     }
     else {
        datas = datas.concat(data);
     }
  });
});



//  C:\Users\Jin\MongoDB\Server\4.2\bin>mongod --dbpath C:\Users\Jin\MongoDB\datas

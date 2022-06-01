/* ****** 아두이노에서 받은 GPS좌표 몽고DB에 업데이트 ****** */

var SerialPort = require('serialport');
var MongoClient = require('mongodb').MongoClient;
var url = "mongodb+srv://dbamdin:admin1234!@cluster0-9wasi.mongodb.net/BLSDB?retryWrites=true&w=majority";
 
var port = new SerialPort("COM4", {
  baudRate:9600,
  parser: new SerialPort.parsers.Readline('\n')
});

var datas = '';
var resultdata = '';

port.open(function() {
    console.log("connected");
    port.on('data', function(data) {
        if(data == '@') {
            //console.log(datas.toString());
            
            //데이터만 뽑기 위해 자르는 부분
            resultdata = datas.slice(datas.indexOf(':')+1, datas.length);
            //console.log("result : " + resultdata.toString());
            
            if(datas.slice(0,datas.indexOf(':')) == "Lat") {
                console.log("Lat은  " + resultdata);
                var inputTmp =  resultdata;
                //console.log(inputTmp);
                MongoClient.connect(url, function(err, db) {
                    //dbo.collection('dbtest').insert({"Lat":resultdata});
                    if (err) throw err;
                    var dbo = db.db("BLSDB");
                    dbo.collection('GPS').update({ name: 'Lat' } , { $set: { value: parseFloat(inputTmp)}});
                    db.close();
                })
            }
            else if(datas.slice(0,datas.indexOf(':')) == "Long") {
                console.log("Long은 " + resultdata);
                
                var inputTmp2 = resultdata;
                //console.log(inputTmp2);
                MongoClient.connect(url, function(err, db) {
                    //dbo.collection('dbtest').insert({"Long":resultdata});
                    if (err) throw err;
                    var dbo = db.db("BLSDB");
                    dbo.collection('GPS').update({ name: 'Long' } , { $set: { value: parseFloat(inputTmp2)}});
                    db.close();
                })
            }
            else if(datas.slice(0,datas.indexOf(':')) == "Time") {
                console.log("Time은 " + resultdata);
                
                var inputTmp3 = resultdata;
                //console.log(inputTmp3);
                MongoClient.connect(url, function(err, db) {
                    //dbo.collection('GPS').insert({name: 'Speed'}, {value:resultdata});
                    if (err) throw err;
                    var dbo = db.db("BLSDB");
                    dbo.collection('GPS').update({ name: 'Time' } , { $set: { value: parseFloat(inputTmp3)}});
                    db.close();
                })
            }
            else if(datas.slice(0,datas.indexOf(':')) == "Course") {
                //console.log("Course는 " + resultdata);
                
                var inputTmp4 = resultdata;
                //console.log(inputTmp4);
                MongoClient.connect(url, function(err, db) {
                    //dbo.collection('GPS').insert({name: 'Time'}, {value:resultdata});
                    if (err) throw err;
                    var dbo = db.db("BLSDB");
                    dbo.collection('GPS').update({ name: 'Course' } , { $set: { value: inputTmp4}});
                    db.close();
                })
            }
            else {
                
            };
            
            /*
             MongoClient.connect(url, function(err, db) {
                if (err) throw err;
                var dbo = db.db("mydb"); 
                if(datas.slice(0,datas.indexOf(':')) == "Lat") {
                    dbo.collection('dbtest').insert({"Lat":resultdata});
                }
                else if(datas.slice(0,datas.indexOf(':')) == "Long") {
                    dbo.collection('dbtest').insert({"Long":resultdata});
                }
             }); */
            
            datas = '';
            
        }
        else {
            datas = datas.concat(data);
        }
    })
});



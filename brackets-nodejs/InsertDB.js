
var MongoClient = require('mongodb').MongoClient;
var url = "mongodb+srv://dbamdin:admin1234!@cluster0-9wasi.mongodb.net/BLSDB?retryWrites=true&w=majority";

MongoClient.connect(url, function(err, db) {
                    //dbo.collection('dbtest').insert({"Lat":resultdata});
                    if (err) throw err;
                    var dbo = db.db("BLSDB");
                    dbo.collection('GPS').insert({name:"Lat", value:0.0});
                    dbo.collection('GPS').insert({name:"Long", value:0.0});
                    dbo.collection('GPS').insert({name:"Time", value:'0'});
                    dbo.collection('GPS').insert({name:"Course", value:'0'});
                    //dbo.collection('GPS').update({ name: 'Lat' } , { $set: { value: parseFloat(inputTmp)}});
                    db.close();
                })
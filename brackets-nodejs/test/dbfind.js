var MongoClient = require('mongodb').MongoClient;
var url = "mongodb+srv://dbamdin:admin1234!@cluster0-9wasi.mongodb.net/test?retryWrites=true&w=majority";

MongoClient.connect(url, function(err, db) {
  if (err) throw err;
  var dbo = db.db("mydb");
  dbo.createCollection("customers", function(err, res) {
    if (err) throw err;
    console.log("Collection created!");
    db.people.insert({"name": "velopert"})
    WriteResult({ "nInserted" : 1 })
    db.close();
      
  });
});

//C:\Users\Jin\MongoDB\Server\4.2\bin>mongod --dbpath C:\Users\Jin\MongoDB\datas
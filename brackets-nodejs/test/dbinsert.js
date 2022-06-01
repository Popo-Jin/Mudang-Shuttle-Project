var Client = require('mongodb').MongoClient;

Client.connect("mongodb+srv://dbamdin:admin1234!@cluster0-9wasi.mongodb.net/test?retryWrites=true&w=majority", function(error, db){
    if(error) {
        console.log(error);
    } else {
        // 1. 입력할 document 생성
        var michael = {name:'Michael', age:15, gender:'M'};
        // 2. student 컬렉션의 insert( ) 함수에 입력
        db.collection('test').insert(michael);

        db.close();
    }
});
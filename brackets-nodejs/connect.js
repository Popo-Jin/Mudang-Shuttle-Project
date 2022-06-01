const mongoose = require('mongoose');

mongoose.connect("mongodb+srv://dbamdin:admin1234!@cluster0-9wasi.mongodb.net/test?retryWrites=true&w=majority")
const db = mongoose.connection;
db.on('error', console.error);  // mongoDB 연동 실패 시 에러 메시지 출력
db.once('open', () =>{
  console.log('connected to mongoDB server'); // mongoDB 연동 성공 시 메시지 출력
});

const Schema = mongoose.Schema;

/* 스키마 생성 */
const TestGPS = new Schema({
  Lat: Number,
  Long: Number
});

/* 해당 스키마에 데이터 추가 */
TestGPS.statics.create = function(Lat, Long){
  const testgps1 = new this({
    lat,
    long
  });
  return testgps1.save();
};

/* 해당 스키마의 데이터 조회 */
TestGPS.statics.findOne = function(testgs1){
  return this.findOne({
    lat
  }).exec();
}  

module.exports = mongoose.model('TestGPS', TestGPS);

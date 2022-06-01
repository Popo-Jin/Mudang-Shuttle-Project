const mongoose = require('mongoose');
const Schema  = mongoose.Schema;

const userSchema = new Schema({
    password : {
        type:String,
        required: true
    },
    email : {
        type:String,
        required: true,
    },
    id:{
        type:String,
        required: true
    },
    name:{
        type:String,
        default: "User"
    },
    phone:{
        type:String,
        default: "111111111"
    }
});


module.exports = mongoose.model('Client', userSchema);
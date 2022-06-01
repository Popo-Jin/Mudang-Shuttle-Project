const express = require('express');
const mongoose = require('mongoose');
const bodyParser = require('body-parser');
const server = express();
const User = require('./models/User');
require("dotenv").config({ path : './variables.env' });
//mongodb+srv://root:1234@test-oymtp.mongodb.net/test?retryWrites=true&w=majority
server.use(bodyParser.urlencoded({ extended: true }));
server.use(bodyParser.json());

//Read User
server.get('/api/User',(req,res)=>{
    // const newUser = new User();
    // newUser.email = "dkwlsfk22@naver.com";
    // newUser.name = "이진하";
    // newUser.phone = 1033662794 ;
    // newUser.save()
    //     .then((user)=>{
    //         console.log(user);
    //         res.json({
    //             message:" User Created Successfully"
    //         });
    //     })
    //     .catch((err)=>{
    //         res.json({
    //             message:" User was not Created Successfully"
    //         });
    //     });

    
    User.find(function(err, users){
        if(err) return res.status(500).send({error : 'databas failure'});
        res.json(users);
    })
});



//Create User
server.post('/api/User',(req,res)=>{
    var user = new User();
    user.name = req.body.name;
    user.email = req.body.email;
    user.phone = req.body.phone;
    user.id = req.body.id;
    user.password = req.body.password;

    user.save(function(err){
        if(err){
            console.error(err);
            res.json({result : 0});
            return;
        }

        res.json({result: 1});

    })

})

//Update user
server.put('/api/User/:user_id',function(req,res){
    User.update({_id: req.params.user_id},{$set: req.body}, function(err,output){
        if(err) res.status(500).json({error : ' database failure'});
        console.log(output);
        if(!output.n) return res.status(404).json({error : 'User not found'});
        res.json({message: 'User updated'});
    })
});

//Delete user
server.delete('/api/User/:user_id',function(req,res){
    User.remove({_id: req.params.user_id},{$set: req.body},function(err,output){
        if(err) res.status(500).json({error : ' database failure'});
        res.status(204).end();
    })
})

server.listen(3000, err =>{
    if(err){
        return console.log(err);
    }else{
        
        mongoose.connect(process.env.MONGODB_URL, {useNewUrlParser : true} , (err) => {
            if(err){
                console.log(err);
            }else{
                console.log("Connected to DB Successfully")
                console.log(mongoose.Collection('dbtest'))
            }
        });
    }
});
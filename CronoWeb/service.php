<?php
session_start();

require("connect.php");
require("db.php");

$retArr = array('retCode' => 0, 'msg' => "null");

$com=filter_input(INPUT_POST, 'com');

//Execute login
if($com=="login" && filter_input(INPUT_POST, 'usr')=="adi" && filter_input(INPUT_POST, 'pass')=="salam"){
    $_SESSION["login"]="ok";
    $retArr["retCode"]=0;
    $retArr["msg"]="Login ok";
}

//No valid login? Return with error.
if(!isset($_SESSION["login"])){
    $retArr["retCode"]=1;
    $retArr["msg"]="Acces forbiden";
    echo json_encode($retArr);
    return;
}

//The login is valid (since we got here). Return Valid login.
if($com=="loginValid"){
    $retArr["retCode"]=0;
    $retArr["msg"]="Valid login";
    echo json_encode($retArr);
    return;
}

//Get the secret shared key for a specific ID
if($com=="getSSK"){
    $id=filter_input(INPUT_POST, 'ID');
    $ssk=  getSSK($id);
    if($ssk!=""){    
        $retArr["retCode"]=0;
        $retArr["msg"]=$ssk;
    }else{
        $retArr["retCode"]=1;
        $retArr["msg"]="Invalid ID.";
    }
    echo json_encode($retArr);
    return;
}

if($com=="serv"){
    $retArr["msg"]="Service query";
    $t=json_decode(filter_input(INPUT_POST, 'time'));
    $retArr["time"]=$t;
}

if($com=="start"){
    $retArr["msg"]="Start received";
    $t=json_decode(filter_input(INPUT_POST, 'time'));
}

echo json_encode($retArr);


<?php
session_start();

//require("connect.php");

$retArr = array('ret' => 0, 'msg' => "null");

$com=filter_input(INPUT_POST, 'com');

if($com=="login" && filter_input(INPUT_POST, 'usr')=="adi" && filter_input(INPUT_POST, 'pass')=="salam"){
    $_SESSION["login"]="ok";
    $retArr["msg"]="Login ok";
}

if(!isset($_SESSION["login"])){
    $retArr["msg"]="Acces forbiden";
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


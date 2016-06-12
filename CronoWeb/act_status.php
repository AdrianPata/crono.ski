<?php
session_start();
require("./connect.php");
require("./db.php");

if(isset($_SESSION["usrID"])){
    $retArr = array('retCode' => 0, 'msg' => "OK");
    $status= getStatus();
    $retArr['ActiveUsrName']= $status->ActiveUsrName;
    $retArr['ActiveUsrStatus']= $status->ActiveUsrStatus;
    $retArr['CronoStartStatus']= $status->CronoStartStatus;
} else {
    $retArr = array('retCode' => 1, 'msg' => "Forbidden.");
}

echo json_encode($retArr);


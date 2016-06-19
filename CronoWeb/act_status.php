<?php
session_start();
require("./connect.php");
require("./db.php");

if(isset($_SESSION["usrID"])){
    $retArr = array('retCode' => 0, 'msg' => "OK");
    $status= getStatus();
    $retArr['ActiveUsrId']= $status->ActiveUsrId;
    $retArr['ActiveUsrName']= $status->ActiveUsrName;
    $retArr['ActiveUsrStatus']= $status->ActiveUsrStatus;
    $retArr['CronoStartStatus']= $status->CronoStartStatus;
    $retArr['ResultStatus']= $status->ResultStatus;
    $retArr['Version']= $status->Version;
} else {
    $retArr = array('retCode' => 1, 'msg' => "Forbidden.");
}

echo json_encode($retArr);


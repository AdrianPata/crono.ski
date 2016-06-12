<?php
require_once './objects.php';

function getSSK($id){
    global $conn;
    $sql = "SELECT SecretSharedKey FROM Devices where Identification='".$id."'";
    $result = mysqli_query($conn,$sql);
    if (mysqli_num_rows($result) > 0){
        $row = mysqli_fetch_assoc($result);
        return $row["SecretSharedKey"];
    } else {
        return "";
    }
}

function validateRFID($id){
    global $conn;
    $sql = "SELECT id FROM Users where card='".$id."'";
    $result = mysqli_query($conn,$sql);
    if (mysqli_num_rows($result) > 0){
        return true;
    }else {
        return false;
    }
}

function loginUser($usr,$pass){
    global $conn;
    $sql = "SELECT * FROM Users where name='".$usr."' and password='".sha1("rty".$pass)."'";
    $result = mysqli_query($conn,$sql);
    if (mysqli_num_rows($result) > 0){
        $row = mysqli_fetch_assoc($result);
        return $row["id"];
    }else{
        return 0;
    }
}

function resetStatus(){
    global $conn;
    $sql="update WebStatus set ActiveUsr=0,UsrStatus=0,CronoStartStatus=0 where id=1";
    mysqli_query($conn,$sql);
}

function getStatus(){
    global $conn;
    $sql = "SELECT u.id,u.name,ws.UsrStatus,ws.CronoStartStatus FROM cronoweb.WebStatus ws
                left outer join Users u on (u.id=ws.ActiveUsr)";
    $result = mysqli_query($conn,$sql);
    if (mysqli_num_rows($result) > 0){
        $row = mysqli_fetch_assoc($result);
        $status=new Status();
        $status->ActiveUsrId=$row["id"];
        $status->ActiveUsrName=$row["name"];
        $status->ActiveUsrStatus=$row["UsrStatus"];
        $status->CronoStartStatus=$row["CronoStartStatus"];
        return $status;
    }else{
        return new Status();
    }
}

function updateStatus($com){
    global $conn;
    if($com==="CronoStartConnected") {
        $sql="update WebStatus set CronoStartStatus=1,ActiveUsr=0 where id=1";
    }
    if($com==="CronoStartDisconnected") {
        $sql="update WebStatus set CronoStartStatus=0,ActiveUsr=0 where id=1";
    }
    mysqli_query($conn,$sql);
}
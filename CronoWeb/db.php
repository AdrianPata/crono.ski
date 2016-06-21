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
        $row = mysqli_fetch_assoc($result);
        mysqli_query($conn,"update WebStatus set ActiveUsr=".$row["id"].",UsrStatus=1 where id=1");
        return true;
    }else {
        return false;
    }
}

function loginUser($usr,$pass){
    global $conn;
    $sql = "SELECT * FROM Users where name='".$usr."' and password='".sha1("rty".$pass)."' and type=0";
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
    $sql="update WebStatus set ActiveUsr=0,UsrStatus=0,CronoStartStatus=0,version=version+1 where id=1";
    mysqli_query($conn,$sql);
}

function getStatus(){
    global $conn;
    $sql = "SELECT u.id,u.name,ws.UsrStatus,ws.CronoStartStatus,ws.Result,ws.version FROM WebStatus ws
                left outer join Users u on (u.id=ws.ActiveUsr)";
    $result = mysqli_query($conn,$sql);
    if (mysqli_num_rows($result) > 0){
        $row = mysqli_fetch_assoc($result);
        $status=new Status();
        $status->ActiveUsrId=$row["id"];
        $status->ActiveUsrName=$row["name"];
        $status->ActiveUsrStatus=$row["UsrStatus"];
        $status->CronoStartStatus=$row["CronoStartStatus"];
        $status->ResultStatus=$row["Result"];
        $status->Version=$row["version"];
        return $status;
    }else{
        return new Status();
    }
}

function updateStatus($com){
    global $conn;
    if($com==="CronoStartConnected") {
        $sql="update WebStatus set CronoStartStatus=1,ActiveUsr=0,version=version+1 where id=1";
    }
    if($com==="CronoStartDisconnected") {
        $sql="update WebStatus set CronoStartStatus=0,ActiveUsr=0,version=version+1 where id=1";
    }
    if($com==="CronoStartSTART") {
        $sql="update WebStatus set UsrStatus=2,version=version+1 where id=1";
    }
    if($com==="CronoStartFINISH") {
        $sql="update WebStatus set UsrStatus=3,version=version+1 where id=1";
    }
    mysqli_query($conn,$sql);
}

function getCurrentSportsman(){
    global $conn;
    $sql = "SELECT ws.ActiveUsr FROM WebStatus ws";
    $result = mysqli_query($conn,$sql);
    if (mysqli_num_rows($result) > 0){
        $row = mysqli_fetch_assoc($result);
        $r=$row["ActiveUsr"];
    }
    return $r;
}

function getCurrentRecordNo(){
    global $conn;
    $sql = "SELECT RecordNo FROM WebStatus";
    $result = mysqli_query($conn,$sql);
    if (mysqli_num_rows($result) > 0){
        $row = mysqli_fetch_assoc($result);
        $r=$row["RecordNo"];
        
        $sql="update WebStatus set RecordNo=".($r+1);
        mysqli_query($conn,$sql);
    }
    return $r;
}

function updateResult($time){
    global $conn;
    $sql="update WebStatus set Result=".$time.",version=version+1 where id=1";
    mysqli_query($conn,$sql);
    $sql="insert into Results (usrid,result,rtime,record) values (".getCurrentSportsman().",".$time.",NOW(),".getCurrentRecordNo().")";
    mysqli_query($conn,$sql);
}

function getResults(){
    global $conn;
    $list=array();

    $sql="select r.record as rid,r.usrid,u.name,r.result,r.rtime from Results r "
            . "inner join Users u on (u.id=r.usrid)"
            . "order by result asc";
    $result = mysqli_query($conn,$sql);
    $t=mysqli_num_rows($result);
    for($i=0;$i<$t;$i++){
        $row = mysqli_fetch_assoc($result);
        $rowa=array();
        $rowa["rid"]=$row["rid"];
        $rowa["usrid"]=$row["usrid"];
        $rowa["name"]=$row["name"];
        $rowa["result"]=$row["result"];
        $rowa["rtime"]=$row["rtime"];
        $list[$i]=$rowa;
    }
    
    $sql="select max(r.record) as mrid from Results r";
    $result = mysqli_query($conn,$sql);
    if(mysqli_num_rows($result)>0){
        $row = mysqli_fetch_assoc($result);
        $max=$row["mrid"];
    }
    
    $resp=array();
    $resp["total"]=$t;
    $resp["max"]=$max;
    $resp["list"]=$list;
    
    return $resp;
}

function getAllowShut(){
    global $conn;
    $sql = "SELECT allowShut FROM WebStatus";
    $result = mysqli_query($conn,$sql);
    if (mysqli_num_rows($result) > 0){
        $row = mysqli_fetch_assoc($result);
        $r=$row["allowShut"];
    }
    return $r;
}

function changeAllowShot($v){
    global $conn;
    $sql="update WebStatus set allowShut=".$v;
    mysqli_query($conn,$sql);
}
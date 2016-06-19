<?php
session_start();
require("./connect.php");
require("./db.php");

if(isset($_SESSION["usrID"])){
    $res=getResults();
} else {
    $res=array();
    $res["total"]=0;
}

echo json_encode($res);
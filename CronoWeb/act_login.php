<?php
session_start();
require("./connect.php");
require("./db.php");


$usr=filter_input(INPUT_POST, 'usr');
$pass=filter_input(INPUT_POST, 'pass');

$id=loginUser($usr,$pass);
if($id>0){
    $_SESSION["usrID"]=$id;
}

header("Location: index.php");

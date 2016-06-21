<?php
session_start();
require("./connect.php");
require("./db.php");



if(isset($_SESSION["usrID"])){
    $v=filter_input(INPUT_GET,"v");
    echo $v;
    changeAllowShot($v);
    echo "ok";
}else {
    echo "Acces denied.";
}

<?php
session_start();
require("./connect.php");
require("./db.php");



if(isset($_SESSION["usrID"]) && getAllowShut()==1){

    $data = array("usr" => "adi", "pass" => "salam","com"=>"shut");
    $data_string = json_encode($data);

    $ch=  curl_init();
    curl_setopt($ch, CURLOPT_URL, "https://hub.crono.ski/");
    curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "POST");
    curl_setopt($ch, CURLOPT_POSTFIELDS, $data_string);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($ch, CURLOPT_VERBOSE, 1); 
    curl_setopt($ch, CURLOPT_HTTPHEADER, array(                                                                          
        'Content-Type: application/json',                                                                                
        'Content-Length: ' . strlen($data_string))                                                                       
    ); 
    curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
    curl_setopt($ch, CURLOPT_CAINFO, '/home/pataro/public_html/crono.ski/lets-encrypt-x3-cross-signed.pem');
    $response=  curl_exec($ch);
    echo curl_error($ch);
    curl_close($ch);
    echo $response;    
} else {
    echo "Access denied";
}
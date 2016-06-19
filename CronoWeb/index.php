<?php
if(!isset($_SERVER['HTTPS']) || $_SERVER['HTTPS'] == ""){
    $redirect = "https://".$_SERVER['HTTP_HOST'].$_SERVER['REQUEST_URI'];
    header("HTTP/1.1 301 Moved Permanently");
    header("Location: $redirect");
	die();
}

session_start();

if(isset($_SESSION["usrID"])){
    $pag="./form_Results.php";
} else {
    $pag="./form_Login.php";
}

?>
<html>
<head>
    <link rel="stylesheet" type="text/css" href="style.css">
    <link rel="stylesheet" type="text/css" href="style_login.css">
    <script src="jquery-3.0.0.min.js"></script>
    <script src="tools.js"></script>
</head>
<body>
    <div class="bgSizeCover">
        <?php require $pag; ?>
        <div class="bottompanel">Photo: Ted Ligety of the United States sets off during a training session for the Alpine Skiing Men's Super Combined Downhill. (http://www.ibtimes.co.uk/)</div>
    </div>
</body>
</html>

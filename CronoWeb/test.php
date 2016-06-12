<html>
    <body>
        <form action="service.php" method="post">
            Com:<input type="text" name="com"/><br>
            Usr:<input type="text" name="usr"/><br>
            Pass:<input type="text" name="pass"/><br>
            ID:<input type="text" name="ID"/><br>
            <input type="submit" value="Login">
        </form>
<?php

$ch=  curl_init();
curl_setopt($ch, CURLOPT_URL, "https://crono:3898");
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
$response=  curl_exec($ch);
echo curl_error($ch);
curl_close($ch);
echo $response;

/*
$r = new HttpRequest('https://localhost:3898', HttpRequest::METH_POST);
$r->setOptions(array('cookies' => array('lang' => 'de')));
$r->addPostFields(array('user' => 'mike', 'pass' => 's3c|r3t'));
//$r->addPostFile('image', 'profile.jpg', 'image/jpeg');
try {
    echo $r->send()->getBody();
} catch (HttpException $ex) {
    echo $ex;
}
 */

echo sha1("rtyadrian");

?>
    </body>
</html>
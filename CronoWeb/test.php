
<html>
    <body>
        <form action="service.php" method="post">
            Com:<input type="text" name="com"/><br>
            Usr:<input type="text" name="usr"/><br>
            Pass:<input type="text" name="pass"/><br>
            ID:<input type="text" name="ID"/><br>
            time:<input type="text" name="time"/><br>
            <input type="submit" value="Login">
        </form>
<?php

/*
$data = array("usr" => "adi", "pass" => "salam","com"=>"shut");
$data_string = json_encode($data);

$ch=  curl_init();
curl_setopt($ch, CURLOPT_URL, "https://hub.crono.ski/");
curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "POST");
curl_setopt($ch, CURLOPT_POSTFIELDS, $data_string);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
curl_setopt($ch, CURLOPT_HTTPHEADER, array(                                                                          
    'Content-Type: application/json',                                                                                
    'Content-Length: ' . strlen($data_string))                                                                       
); 
curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, true);
curl_setopt ($ch, CURLOPT_CAINFO, "/home/pataro/public_html/crono.ski/lets-encrypt-x3-cross-signed.pem");
$response=  curl_exec($ch);
echo curl_error($ch);
curl_close($ch);
echo $response;
echo "<p>".getcwd()."</p>";
*/

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

?>
    </body>
</html>
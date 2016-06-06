<?php

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


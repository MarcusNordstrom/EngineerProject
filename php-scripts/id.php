<?php
require_once ('connection.php');
function mb_str_shuffle() {
    $tmp = preg_split("//u", "ABCDEFGHIJKLMNOPQRSTUVWXYZÅÄÖ", -1, PREG_SPLIT_NO_EMPTY);
    // $tmp = preg_split("//u", "ÅÄÖ", -1, PREG_SPLIT_NO_EMPTY);
    shuffle($tmp);
    return join("", $tmp);
}
$randomString = mb_substr(mb_str_shuffle(),0,1);

$getID = "SELECT id FROM data WHERE bokstav = ' ' LIMIT 1";
$sql_update = "UPDATE data 
                SET bokstav= $bokstav
                WHERE id=$id";

$result = mysqli_query($con,$getID);
    while($row = mysqli_fetch_array($result)) {
        echo $row['id'] , "-" , $randomString, "!";
        $id = $row['id'];
        mysqli_query($con,"UPDATE data SET bokstav='$randomString' WHERE id=$id");
        mysqli_close($con);
    }
    
?>
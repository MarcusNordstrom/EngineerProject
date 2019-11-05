
<!DOCTYPE html>
<html>

<?php
/**
 * Class to get an id from node that is used to map word 
 */
require_once 'connection.php';
$host = "localhost";
$username = "admin";
$db_name = "saol";
$pass = "pass";
$con = mysqli_connect($GLOBALS['host'], $GLOBALS['username'], $GLOBALS['pass']);
$db = mysqli_select_db ( $con, $GLOBALS['db_name']);
//Get id from node
$id = $_GET['id'];

//Reset all nodes buttonpress value and update with latest buttonpress
$sqlResetKnapptryck = "UPDATE data SET knapptryck = 0";
$sqlSetKnapptryck = "UPDATE data SET knapptryck = 1 WHERE id = '$id'";
mysqli_query($con, $sqlResetKnapptryck);
mysqli_query($con, $sqlSetKnapptryck);
require_once 'displaycontroller.php';
require_once 'saol.php';

//Map word and check according to SAOL
$word = getWordFromId();
checkWord($word[0]);
?>
</html>
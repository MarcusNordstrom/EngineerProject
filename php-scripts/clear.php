<?php
require_once 'connection.php';
$con = mysqli_connect($GLOBALS['host'], $GLOBALS['username'], $GLOBALS['pass']);
$db = mysqli_select_db ( $con, $GLOBALS['db_name']);
$sqlClearKnapptryck = "UPDATE data SET knapptryck = 0; ";
$sqlClearWords .= "DELETE FROM words; ";
mysqli_query($con, $sqlClearKnapptryck);
mysqli_query($con, $sqlClearWords);
mysqli_close($con);
?>
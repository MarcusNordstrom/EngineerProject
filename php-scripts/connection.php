<?php
$username = "admin";
$pass = "pass";
$host = "localhost";
$db_name = "saol";
$con = mysqli_connect ($host, $username, $pass);
$db = mysqli_select_db ( $con, $db_name );
?>

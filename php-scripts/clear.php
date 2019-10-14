<?php
require_once ('connection.php');    
    if(isset($_POST['nw_update'])){
        $sql_clear = "UPDATE data SET bokstav = ' ', vgranne='0', hgranne='0'";
        mysqli_query($con, $sql_clear);
        mysqli_close($con);
    }
?>
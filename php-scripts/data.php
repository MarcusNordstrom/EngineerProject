<?php
    include ('connection.php');
    /*
    * Swappa ut nedanstående kod för att ta emot post requests istället.
    $temp1=$_POST["temperature"];
    $hum1=$_post["humidity"];
    $heat1=$post["heat_index"];
    $sql_insert = "INSERT INTO data (temperature, humidity, heat_index) 
        VALUES ('".$temp1."','".$hum1."','".$heat1."')"; 
    */

    if(isset($_POST['nw_update'])){
        echo("You clicked button one!");
        $sql_clear = "UPDATE data SET bokstav = ' ', vgranne='0', hgranne='0'";
        mysqli_query($con, $sql_clear);
        mysqli_close($con);
    }
    
    $id = $_GET['id'];
    $bokstav = $_GET['bokstav'];
    $vgranne = $_GET['vgranne'];
    $hgranne = $_GET['hgranne'];

    $sql_insert = "INSERT INTO data (bokstav, vgranne, hgranne) VALUES ('".$_GET["bokstav"]."', '".$_GET["vgranne"]."', '".$_GET["hgranne"]."')";
    $sql_update = "UPDATE data 
                    SET bokstav='$bokstav', vgranne='$vgranne', hgranne='$hgranne'
                    WHERE id=$id";
    #if(mysqli_query($con,$sql_insert))
    if(mysqli_query($con,$sql_update))
        {
        echo "Set bokstav to: '$bokstav', vgranne to: '$vgranne', hgranne to: '$hgranne' for ID: '$id'";
        mysqli_close($con);
        }
    else
    {
    echo "error is ".mysqli_error($con );
    }
?>
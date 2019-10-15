<?php
require_once('connection.php');

$firstNodeSelect = "SELECT Id, Bokstav, HGranne FROM Nodes WHERE HGranne <> 0 AND VGranne = 0 LIMIT 1";

//Get first letter of the word
if ($result = $mysqli_query($con, $firstNodeSelect)) {
  
    while($row = mysqli_fetch_array($result)) {
            $nextGranne = $row['hgranne'];
            $id = $row['id'];
            $letter = $row['bokstav'];
        }
          //TODO: ADD LETTER/ID TO DB/ARRAY
   
    do {
        //Get next letter of the word, where id = previous nodes neighbor
        if ($result = mysqli_query($con, "SELECT id, bokstav, hgranne FROM data WHERE id = $nextGranne")) {
            while($row = mysqli_fetch_array($result)) {
                $nextGranne = $row['hgranne'];
                $id = $row['id'];
                $letter = $row['bokstav'];
            }
        //TODO: ADD LETTER/ID TO DB/ARRAY
        }
        else {
            $nextGranne = 0;
        }
    } while($nextGranne != 0);
}
$mysqli_close($con);

?>

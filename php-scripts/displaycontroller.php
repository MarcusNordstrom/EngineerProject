<?php
$host = "localhost";
$username = "admin";
$db_name = "nodes";
$pass = "pass";

function getFirstNode($id) {
    $link = mysqli_connect($GLOBALS['host'], $GLOBALS['username'], $GLOBALS['pass']);
    $db = mysqli_select_db ( $link, $GLOBALS['db_name']);

    // Check connection
    if($link === false){
        die("ERROR: Could not connect. " . mysqli_connect_error());
    }
    $previousNode = 0;
   
    do {
        $sqlGetPreviousNode = "SELECT id, vgranne FROM data WHERE id = '$id'";
        if ($result = mysqli_query($link, $sqlGetPreviousNode)) {
            while ($row = mysqli_fetch_array($result)) {
                $previousNode = $row['vgranne'];       
            }    
            if ($previousNode != 0) {
                $id = $previousNode;
            }               
        }
    } while ($previousNode != 0);
  
    return $id;
}

function getWord() {
   
    $link = mysqli_connect($GLOBALS['host'], $GLOBALS['username'], $GLOBALS['pass']);
    $db = mysqli_select_db ( $link, $GLOBALS['db_name'] );
// Check connection
if($link === false){
    die("ERROR: Could not connect. " . mysqli_connect_error());
}
    $firstNodeSelect = "SELECT id, bokstav, hgranne FROM data WHERE vgranne = 0 AND hgranne !=0";
    $word = "";
    $ids = [];
    //Get first letter of the word
    if ($result = mysqli_query($link, $firstNodeSelect)) {
        
        while($row = mysqli_fetch_array($result)) {
                $nextNode = $row['hgranne'];
                $id = $row['id'];
                $letter = $row['bokstav'];

                $word .= $letter;
                $ids[] = $id;
  
                
            }          
       
        do {
            $sqlNext = "SELECT id, bokstav, hgranne FROM data WHERE id = '$nextNode'";
            //Get next letter of the word, where id = previous nodes neighbor
            if ($result = mysqli_query($link, $sqlNext)) {
                //Check if more than one result, if so synchronize form server (?)
           
                while($row = mysqli_fetch_array($result)) {
                    $nextNode = $row['hgranne'];
                    $id = $row['id'];
                    $letter = $row['bokstav'];
                    $ids[] = $id;
                    $word .= $letter;
                }
            }
            else {
                $nextNode = 0;
                echo "Internal server error!";
            }
        } while($nextNode != 0);
       
    }
    $idsSql = join(",",$ids);   
    $sql = "SELECT bokstav FROM data WHERE id NOT IN ($idsSql)";  
    $deadWord = "";
    if ($result2 = mysqli_query($link, $sql)) {
        while($row2 = mysqli_fetch_array($result2)) {
            $deadLetter = $row2['bokstav'];
            $deadWord .= $deadLetter;
        }
    }
    
    mysqli_close($link);
    return array($word, $deadWord);
}

function GetApprovedWords() {
    $link = mysqli_connect($GLOBALS['host'], $GLOBALS['username'], $GLOBALS['pass']);
$db = mysqli_select_db ( $link, "nodes" );
// Check connection
if($link === false){
    die("ERROR: Could not connect. " . mysqli_connect_error());
}
    $words = [];
    $score = [];
    $slqSelectWords = "SELECT ord, score FROM words  ";
    if ($result = mysqli_query($link, $slqSelectWords)) {
        while($row = mysqli_fetch_array($result)) {
            $words[] = $row['ord'];
            $score[] = $row['score'];
        }
   
    }
    mysqli_close($link);
    
    return array($words, $score);
    
}

function GetScore() {
    $link = mysqli_connect($GLOBALS['host'], $GLOBALS['username'], $GLOBALS['pass']);
    $db = mysqli_select_db ( $link, $GLOBALS['db_name']);
    $sqlSumScore = "SELECT SUM(score) AS score_sum FROM words";
    if ($result = mysqli_query($link, $sqlSumScore)) {
        $row = mysqli_fetch_assoc($result);
        $sum = $row['score_sum'];
    }
   
    mysqli_close($link);
    return $sum;
}

?>

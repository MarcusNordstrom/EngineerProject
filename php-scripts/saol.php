<?php



$host = "localhost";
$username = "admin";
$db_name = "saol";
$pass = "pass";
/**
 * Function to check if word exists, if word exists add it to table of correct words
 * Function scrapes saol website, if search result contains 'gav inga svar' the word does not exist
 */
function checkWord($word) {
    
    $baseurl = 'https://svenska.se/tri/f_saol.php?sok=';
    $search = $baseurl.$word;
   
    
    $contents = file_get_contents($search);
   
    $match = strpos($contents,'gav inga svar');
   
    if($match == TRUE){
      
        return FALSE;
    } 
    else {     
  
        insertWord($word);
        return TRUE;
    }
}

//Function inserts word into table 
function insertWord($word) {
    require_once 'connection.php';
    
    $con = mysqli_connect($GLOBALS['host'], $GLOBALS['username'], $GLOBALS['pass']);
    $db = mysqli_select_db ( $con, $GLOBALS['db_name']);
   
      // Check connection
      if($con === false){
        die("ERROR: Could not connect. " . mysqli_connect_error());
    }
    $score = calculateScore($word); 
   $correctWord = "INSERT INTO words VALUES (NULL, '$word', $score)";
                  
                  
     if (mysqli_query($con, $correctWord)) {
     
    }
    else {
        echo "Insert failed!";
    }
    mysqli_close($con);
}
//Aggregates the score for the word according to points for each letter.
function calculateScore($wordstring) {   
 
    $word =  preg_split("//u", $wordstring, -1, PREG_SPLIT_NO_EMPTY);
    $points = array("A" => 1, "B" => 4,"C" => 8,"D" => 1,"E" => 1, "F" => 3,"G" => 2,"H" => 2,"I" => 1,"J" => 7,"K" => 2,"L" => 1,"M" => 2,"N" => 1,
    "O" => 2,"P" => 4,"Q" => 10,"R" => 1,"S" => 1,"T" => 1,"U" => 4,"V" => 3,"W" => 3,"X" => 8,"Y" => 7,"Z" => 10, "Å" => 4, "Ä" => 3, "Ö" => 4);
    $sum = 0;

  
  
    foreach ($word as $letter) {
     
      $sum += $points[$letter];
      
    }
    
    return $sum;
  }

?>
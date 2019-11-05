<?php 

/**
 * Get word based on which node has had its button pressed.
 * First we find out which node is the first in the word,
 * then we map out the rest of the word using knowledge of its 
 * neighbors.
 */
function getWordFromId() {
    require_once 'connection.php';
    $link = mysqli_connect($GLOBALS['host'], $GLOBALS['username'], $GLOBALS['pass']);
    $db = mysqli_select_db ( $link, $GLOBALS['db_name']);

    // Check connection
    if($link === false){
        die("ERROR: Could not connect. " . mysqli_connect_error());
    }
    $previousNode = 0;
    $id = 0;
    
    //Get node from which button was pressed
    $sqlGetKnapptryckNode = "SELECT id, vgranne FROM data WHERE knapptryck = 1 AND bokstav != ''";
    if ($result = mysqli_query($link, $sqlGetKnapptryckNode)) {
       
        
        while ($row = mysqli_fetch_array($result)) {
            $id = $row['id'];
            $vgranne = $row['vgranne'];    
        }
         //If no nodes are selected, show all nodes as inactive
        if ($id == 0) {
            $sqlGetAllNodes = "SELECT bokstav FROM data WHERE bokstav != ''";
            $word = "";
            if ($result = mysqli_query($link, $sqlGetAllNodes)) {
                while ($row = mysqli_fetch_array($result)) {
                    $word .= $row['bokstav'];
                }
            }
        return array("", $word);
        }
    }
    
    //First node found, map rest of the word
    if ($vgranne != 0) {
    do {
        $sqlGetPreviousNode = "SELECT id, vgranne FROM data WHERE id = '$id' AND bokstav != ''";
        if ($result = mysqli_query($link, $sqlGetPreviousNode)) {
            while ($row = mysqli_fetch_array($result)) {
                $previousNode = $row['vgranne'];       
            }    
            if ($previousNode != 0 && $previousNode != $id) {
                $id = $previousNode;
            }   
            else {
                $previousNode = 0;
            }            
        }
    } while ($previousNode != 0);
}
    
    return getWordFromFirstNode($id);
}

/**
 * Maps out the rest of the word based on the first node
 * Parameter: id of first node of the word
 *
 */
function getWordFromFirstNode($id) {
   
    $link = mysqli_connect($GLOBALS['host'], $GLOBALS['username'], $GLOBALS['pass']);
    $db = mysqli_select_db ( $link,$GLOBALS['db_name']);
    // Check connection
    if($link === false){
        die("ERROR: Could not connect. " . mysqli_connect_error());
    }
    $firstNodeSelect = "SELECT id, bokstav, hgranne FROM data WHERE id = '$id'";
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
                //Check if more than one result
                //Add letters to string and id to array to map left over letters
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
                echo "Error 500: Internal server error!";
            }
        } while($nextNode != 0);
       
    }
    //Get nodes that are not in play
    $idsSql = join(",",$ids);   
    $sql = "SELECT bokstav FROM data WHERE id NOT IN ($idsSql) AND bokstav != ''";  
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


/**
 * Get all words that have at least two letters in them
 */
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

    //Get the letters for the nodes that aren't included in the word
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

/**
 * Returns approved words and score to be displayed in the results list
 */
function GetApprovedWords() {
    require_once 'connection.php';
    $link = mysqli_connect($GLOBALS['host'], $GLOBALS['username'], $GLOBALS['pass']);
    $db = mysqli_select_db ( $link, $GLOBALS['db_name'] );
// Check connection
    if($link === false){
    die("ERROR: Could not connect. " . mysqli_connect_error());
    }
    $words = [];
    $score = [];
    $slqSelectWords = "SELECT ord, score FROM words";
    if ($result = mysqli_query($link, $slqSelectWords)) {
        while($row = mysqli_fetch_array($result)) {
            $words[] = $row['ord'];
            $score[] = $row['score'];
        }
   
    }
    mysqli_close($link);
    
    return array($words, $score);
    
}

/**
 * Function to get total score of the approved words
 */
function GetScore() {
    $link = mysqli_connect($GLOBALS['host'], $GLOBALS['username'], $GLOBALS['pass']);
    $db = mysqli_select_db ( $link, $GLOBALS['db_name'] );
    $sqlSumScore = "SELECT SUM(score) AS score_sum FROM words";
    $sum = 0;
    if ($result = mysqli_query($link, $sqlSumScore)) {
        $row = mysqli_fetch_assoc($result);
        $sum = $row['score_sum'];
    }
   
    mysqli_close($link);
    return $sum;
}

?>

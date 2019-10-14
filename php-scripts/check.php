<?php
$baseurl = 'https://svenska.se/tri/f_saol.php?sok=';
$word = $_GET['ord'];
$search = $baseurl.$word;
$contents = file_get_contents($search);
$match = strpos($contents,'gav inga svar');
if($match == TRUE){
    echo '0';
} else {
    echo '1';
}
?>
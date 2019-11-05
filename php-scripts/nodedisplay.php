<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
</head>

  
  <?php 
  
  header("Refresh: 3; URL=nodedisplay.php"); // Refresh the webpage every second
  require_once 'displaycontroller.php';
  require_once 'saol.php';

  $word = getWordFromId();
  //Chosen word
  $wordArray = preg_split("//u", $word[0], -1, PREG_SPLIT_NO_EMPTY);
  //Unused letters
  $deadLetters = preg_split("//u", $word[1], -1, PREG_SPLIT_NO_EMPTY);?>
  <table>
  <?php if (count($wordArray) > 0):?>
  <tr>
  
  <?php foreach ($wordArray as $letter):?>

  <td>
<div style="width: 100px; text-align:center;height:100px; background:green; margin:10px; vertical-align: middle;
line-height: 100px;  ">
<?php echo $letter;?>

  </div>
</td>
  <?php endforeach;?>

</tr>
<?php endif;

foreach ($deadLetters as $letter):?>

<td>
<div style="width: 100px; text-align:center; height:100px; background:gray; margin:10px;vertical-align: middle;
line-height: 100px;  ">
<?php echo $letter;?>
  
  </div>
</td>
  <?php endforeach;?>
</tr>

  </table>
  

</html>
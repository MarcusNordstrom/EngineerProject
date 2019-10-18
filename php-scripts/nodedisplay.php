<!DOCTYPE html>
<html>

  
  <?php 
  require_once 'displaycontroller.php';
  
  $word = getWord();
 
  $wordArray = str_split($word[0]);
  $deadLetters = str_split($word[1]);?>
  <table>
  <tr>
  <?php
  foreach ($wordArray as $letter):?>

  <td>
<div style="width: 100px; text-align:center;height:100px; background:green; margin:10px; vertical-align: middle;
line-height: 100px;  ">
<?php echo $letter;?>

  </div>
</td>
  <?php endforeach;?>
</tr>

<?php
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
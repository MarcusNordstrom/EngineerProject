<!DOCTYPE html>
<html>
<head>

</head>

<body>
    <?php
   

        header("Refresh: 1; URL=resultsdisplay.php"); // Refresh the webpage every second
        require_once 'displaycontroller.php';
        $words = GetApprovedWords();
        $score = GetScore();
    ?>
    <table>
        <tr>

            <th align="left"><?php echo "Ord";?></th>
            <th><?php echo "Resultat";?></th>
</tr>
      <?php for ($x=0; $x< count($words[0]); $x++):?>
      <tr>
        <td width="100px">
          <?php 
          //Show approved words
          echo $words[0][$x];?>
        </td>
        <td>
          <?php 
          //Show points for approved words
          echo $words[1][$x];?>
        </td>
      </tr>
      <?php endfor;?>
    </table>
    <div > 
 
        
      <?php  
      //Show total score
      echo "Summa:       " . $score?>

    </div>
</body>
</html>
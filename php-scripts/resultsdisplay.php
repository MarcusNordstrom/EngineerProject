<!DOCTYPE html>
<html>

    <?php
        require_once 'displaycontroller.php';
        $words = GetApprovedWords();
        $score = GetScore();
    ?>
    <table>
        <tr>

            <th align="left">Ord</th>
            <th>Poäng</th>
</tr>
      <?php for ($x=0; $x< count($words[0]); $x++):?>
      <tr>
        <td width="100px">
          <?php echo $words[0][$x];?>
        </td>
        <td>
          <?php echo $words[1][$x];?>
        </td>
      </tr>
      <?php endfor;?>
    </table>
    <div > 
 
    Totalpoäng:      
      <?php  echo $score?>

    </div>

</html>
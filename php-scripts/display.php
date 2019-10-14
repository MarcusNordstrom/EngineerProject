<?php
$url=$_SERVER['REQUEST_URI'];
header("Refresh: 1; URL=display.php"); // Refresh the webpage every second
?>
<html>
<head>
<title>Arduino Ethernet Database</title>
<style type="text/css">
.table_titles {
padding-right: 20px;
padding-left: 20px;
color: #000;
}
.table_titles {
color: #FFF;
background-color: #0000FF;
}
table {
border: 2px solid #333;
}
body { font-family: "Trebuchet MS", Courier; }
</style>
</head>
<body>
<h1>Arduino Data Logging to Database</h1>
<table border="0" cellspacing="0" cellpadding="4">
<tr>
<td class="table_titles">ID</td>
<!--<td class="table_titles">Date and Time</td>-->
<td class="table_titles">Bokstav</td>
<td class="table_titles">Granne Vänster</td>
<td class="table_titles">Granne Höger</td>
</tr>

<?php
include('connection.php');
include('clear.php');
$result = mysqli_query($con,'SELECT * FROM data ORDER BY id ASC');
// Process every record
$oddrow = true;
while($row = mysqli_fetch_array($result))
{
if ($oddrow)
{
$css_class=' class="table_cells_odd"';
}
else
{
$css_class=' class="table_cells_even"';
}
$oddrow = !$oddrow;
echo "<tr>";
echo "<td '.$css_class.'>" . $row['id'] . "</td>";
#echo "<td '.$css_class.'>" . $row['event'] . "</td>";
echo "<td '.$css_class.'>" . $row['bokstav'] . "</td>";
echo "<td '.$css_class.'>" . $row['vgranne'] . "</td>";
echo "<td '.$css_class.'>" . $row['hgranne'] . "</td>";
echo "</tr>";
}

// Close the connection
mysqli_close($con);
?>
</table>
    <form method="POST">
        <input type="submit" name="nw_update" value="NW_Update"/>
    </form>
</body>
</html>

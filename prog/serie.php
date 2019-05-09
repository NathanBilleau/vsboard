<html>
<head>
<?php
if (isset($_POST['cde1']))
{
system('sudo ./charserie ttyUSB0 9600 1');
}
if (isset($_POST['cde2']))
{
system('sudo ./charserie ttyUSB0 9600 2');
}
if (isset($_POST['cde3']))
{
system('sudo ./charserie ttyUSB0 9600 3');
}
if (isset($_POST['cde4']))
{
system('sudo ./charserie ttyUSB0 9600 4');
}
?>

  <title></title>
</head>
<body>
<form method="post">
  <table
 style="width: 75%; text-align: left; margin-left: auto; margin-right: auto;"
 border="0" cellpadding="2" cellspacing="2">
    <tbody>
      <tr>
        <td style="text-align: center;"><button name="cde1">Commande 1</button></td>
        <td style="text-align: center;"><button name="cde2">Commande 2</button></td>
      </tr>
      <tr>
        <td style="text-align: center;"><button name="cde3">Commande 3</button></td>
        <td style="text-align: center;"><button name="cde4">Commande 4</button></td>
      </tr>
    </tbody>
  </table>
</form>
</body>
</html>

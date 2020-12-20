<?php
include 'conexion.php';

print_r($_POST);

$tomar = $_POST['tomar'];

$sql = "UPDATE Checar SET Tomar = $tomar WHERE IdChecar = 1";
mysqli_query($conexion,$sql);

mysqli_close($conexion);
?>
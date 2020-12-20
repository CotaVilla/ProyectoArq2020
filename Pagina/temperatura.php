<?php
include 'conexion.php';

$localTime = new DateTime('now', new DateTimeZone('America/Tijuana'));
$localTime = $localTime->format('Y-m-d H:i:s');

$temp = $_POST['temp'];
$hum = $_POST['hum'];

$sql ="INSERT INTO medidas (fecha_medida,temp,humedad) VALUES('$localTime',$temp,$hum)";
mysqli_query($conexion,$sql);

mysqli_close($conexion);
?>
<?php
include 'conexion.php';
$sql = "SELECT Tomar FROM Checar WHERE IdChecar = 1";
$resultado = mysqli_query($conexion,$sql);
if (!$resultado) {
    die("No se pudo consultar:" . mysqli_error());
}
else
{
    echo "Valor = ";
    while($row=mysqli_fetch_array($resultado))
    {
        echo $row['Tomar'];
    }

    $sql = "UPDATE Checar SET Tomar = 0 WHERE IdChecar = 1";
    mysqli_query($conexion,$sql);

    mysqli_close($conexion);
}
?>
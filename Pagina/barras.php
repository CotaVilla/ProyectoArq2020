<?php
include 'conexion.php';

$sql="SELECT fecha_medida, temp from medidas order by fecha_medida";
$result=mysqli_query($conexion,$sql);
	$valoresY=array(); //Temperatura
	$valoresX=array(); //Fechas

	while($ver=mysqli_fetch_row($result)) {
		$valoresY[]=$ver[1];
		$valoresX[]=$ver[0];

	}

	$datosX=json_encode($valoresX);
	$datosY=json_encode($valoresY);
	?>

	<div id="graficaBarras"></div>

	<script type="text/javascript">
		function crearCadenaBarras(json){
			var parsed = JSON.parse(json);
			var arr = [];
			for(var x in parsed){
				arr.push(parsed[x]);
			}
			return arr;
		}
	</script>

	<script type="text/javascript">

		datosX=crearCadenaBarras('<?php echo $datosX ?>');
		datosY=crearCadenaBarras('<?php echo $datosY ?>');


		var data = [
		{
			x: datosX,
			y: datosY,
			type: 'bar',
			marker: {
				color: 'rgb (78,127,113)'
			}
		}
		];

		var layout= {
			title: 'Medidas de Temperatura Remota (Version 2)',
			font:{
				family: 'Raleway, sans-serif'
			},
			xaxis: {
				tickangle: -45,
				title: 'Fechas'
			},
			yaxis: {
				title: 'Grados Centrigados'
			},
			bargap:0.05
		};


		Plotly.newPlot('graficaBarras', data, layout);
	</script>
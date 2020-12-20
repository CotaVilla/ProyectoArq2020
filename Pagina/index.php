<!DOCTYPE html>
<html>
<head>
	<title>Graficas temperaturas</title>
	<meta http-equiv="refresh" content="10">
	<link rel="stylesheet" type="text/css" href="Librerias/bootstrap/css/bootstrap.css">
	<script src="Librerias/jquery-3.5.1.min.js"></script>
	<script src="Librerias/plotly-latest.min.js"></script>
</head>
<body>
	<div class="container">
		<div class="row">
			<div class="col-sm-12">
				<div class="panel panel-primary">
					<div class="panel panel-heading">
						GRAFICAS DE TEMPERATURA
					</div>
					<div class="panel panel-body">
						<div class="row">
							<div class="col-sm-6">
								<div id="cargaLineal"></div>
							</div>
							<div class="col-sm-6">
								<div id="cargaBarras"></div>
							</div>
						</div>
					</div>
				</div>
			</div>
		</div>
	</div>
</body>
</html>

<script type="text/javascript">
	$(document).ready(function(){
		$('#cargaLineal').load('lineal.php');
		$('#cargaBarras').load('barras.php');
	});
</script>
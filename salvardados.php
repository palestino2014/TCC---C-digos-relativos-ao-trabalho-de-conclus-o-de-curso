<?php

include ("conecta.php");

	$umidade1 = $_GET['umidade1'];
	$umidade2 = $_GET['umidade2'];
	$umidade3 = $_GET['umidade3'];
        $umidade4 = $_GET['umidade4'];
        $umidade5 = $_GET['umidade5'];
        $umidade6 = $_GET['umidade6'];
        $cmMsec   = $_GET['cmMsec'];
	
	$datahora=date('Y-m-d h:i:s');
    

	$sql_insert = "insert into tabelaarduino (umidade1,umidade2,umidade3,umidade4,umidade5,umidade6,cmMsec,data) values ('$umidade1','$umidade2','$umidade3','$umidade4','$umidade5', '$umidade6','$cmMsec', '$datahora')";
	mysql_query($sql_insert);

		if($sql_insert) 
			{
			echo "Salvo com sucesso";
			} else { 
		echo "Ocorreu um erro";
	}

?>

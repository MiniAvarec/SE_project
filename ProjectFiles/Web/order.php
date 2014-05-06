<?php
	session_start();
	//$con=mysqli_connect("localhost","root","","express_catering");
	$con=mysqli_connect("188.226.183.188","root","root123","express_catering");

	if (mysqli_connect_errno()){
		echo "Failed to connect to MySQL: " . mysqli_connect_error();
	}
	mysqli_set_charset($con,'utf8');   
	$name = $_POST['name'];
	$surname = $_POST['surname'];
	$address = $_POST['address'];	
	$telephone = $_POST['telephone'];
	$change = $_POST['change'];
	$area = $_POST['area'];
	$p = array_values($_SESSION['orders']);
	$orders = "";
	for ($i = 0; $i < sizeof($p); $i++){				 	
		if ($i == sizeof($p) - 1) $orders = $orders.$_SESSION['id'.$p[$i]]['name']."-".$_SESSION['id'.$p[$i]]['amount']."шт"; else
		$orders = $orders.$_SESSION['id'.$p[$i]]['name']."-".$_SESSION['id'.$p[$i]]['amount']."шт ";
 	}
 	$sql = "INSERT INTO `express_catering`.`order` (`id`, `name`, `surname`, `address`, `tel`, `change`, `extra`, `orders`, `total`, `status`) VALUES(NULL,'".$name."','".$surname."','".$address."', '".$telephone."', '".$change."', \"".$area."\", '".$orders."', '".$_SESSION['id0']['price']."',0);"; 	
 	if (!mysqli_query($con,$sql)){
  		die('Error: ' . mysqli_error($con));
  	} 	
  	session_destroy();
  	header("Location: success.php");
?>	
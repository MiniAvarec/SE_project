<?php
	session_start();
	$id = $_POST['id'];
	$price = $_POST['price'];
	$amount = $_POST['amount'];	
	$sign = $_POST['sign'];
/*	$id = $_GET['id'];
	$price = $_GET['price'];
	$amount = $_GET['amount'];	
	$sign = $_GET['sign'];
	
*/		
	$s = 'id'.$id;	
	if (!isset($_SESSION[$s]['amount'])){
		$oldamount = 0;
		$oldprice = 0;			
	}	else {
		$oldamount = $_SESSION[$s]['amount'];
		$oldprice = $_SESSION[$s]['price'];		
	}
	$_SESSION[$s]['amount'] = $amount;
	$_SESSION[$s]['price'] = $price;	
	if ($sign === 'add'){
		$_SESSION['id0']['price'] += $price * $amount - $oldprice * $oldamount;
		if (!isset($_SESSION['orders'])){
			$_SESSION['orders'] = array();
		}
		if (!in_array($id, $_SESSION['orders'])) {

			array_push($_SESSION['orders'], $id);
		}

	} else if ($sign === 'sub'){						
		$_SESSION['id0']['price'] -= $oldprice * $oldamount - $price * $amount;
		if ($amount == 0) {
			if (($key = array_search($id, $_SESSION['orders'])) != false) {
   				unset($_SESSION['orders'][$key]);
			}
		}
	}
	echo $_SESSION['id0']['price'];
	//return $_SESSION['id0']['price'];	
	//session_destroy();
?>
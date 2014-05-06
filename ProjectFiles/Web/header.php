<?php 
session_start();
if (!isset($_SESSION['id0']['price'])) {
  $_SESSION['id0']['price'] = 0;  
}

if (isset($_SESSION['LAST_ACTIVITY']) && (time() - $_SESSION['LAST_ACTIVITY'] > 900)) {    
    session_unset();
    session_destroy();
    session_start();
	if (!isset($_SESSION['id0']['price'])) {
	  	$_SESSION['id0']['price'] = 0;  
	}
}

$_SESSION['LAST_ACTIVITY'] = time();

function echoActiveClassIfRequestMatches($requestUri)
{
    $current_file_name = basename($_SERVER['REQUEST_URI'], ".php");
    if ($current_file_name == $requestUri)
        echo 'class="active"'; else echo 'class="none"';
}

$k = basename($_SERVER['REQUEST_URI'],".php");
//$con=mysqli_connect("localhost","root","","express_catering");
$con=mysqli_connect("188.226.183.188","root","root123","express_catering");

if (mysqli_connect_errno()){
	echo "Failed to connect to MySQL: " . mysqli_connect_error();
}
mysqli_set_charset($con,'utf8');         
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html>
<head>
	<title>Express Cathering</title>
	<script src='js/jquery-1.11.0.min.js' type='text/javascript'></script>	
	<script src='js/jquery.mousewheel.js' type="text/javascript"></script>
	<script src='js/class.horinaja.jquery.js' type='text/javascript'></script>	
	<link rel="stylesheet" href="css/horinaja.css" type="text/css" media="screen" />

	<link rel="stylesheet" type="text/css" href="css/style.css" />		
	<meta http-equiv="Content-Type" content="text/html;charset=UTF-8">
	<script>
		cart = <?php if ($k == 'cart') echo "1"; else echo "0";?>;
		$( document ).ready(function() {
			if (cart == 1) $('#cart').css("visibility","hidden");
			if (parseInt($('#cart a div p').text()) > 2000) {
				$('#submit').prop('disabled', false);
				$("#submit").css("opacity","1");
				$("#submitchecker").css("visibility","hidden");
			} else {
				$('#submit').prop('disabled', true);
				$("#submit").css("opacity","0.3");
				$("#submitchecker").css("visibility","visible");
			}
		});
		$(function () {
			var ids = 0;
			var prices = 0;
			var amounts = 0;
			$('.food-desc img').on('click',function(){							
				$(this).parent().children('.addcart').css("visibility","visible");				
				var $qty=$(this).parent().children('.addcart').find('.orderamount');
		        var currentVal = parseInt($qty.val());		   		        
		        if (!isNaN(currentVal)) {
		        	if(currentVal < 1){
		        	ids = parseInt($(this).closest('.addcart').find('.food-id').val());
		        	prices = parseInt($(this).closest('.addcart').find('.food-price').val());
		        	amounts = currentVal + 1;
		            $qty.val(currentVal + 1);	            		    
					  $.ajax({
					  		type 		:	"POST",
					  		url			: 	"addcart.php",
					  		data 		: 	{ id 	: 	parseInt($(this).parent().children('.addcart').find('.food-id').val()),
					    					price 	: 	parseInt($(this).parent().children('.addcart').find('.food-price').val()),
					    					amount 	: 	(currentVal + 1),
					    					sign 	: 	'add'},			
					    	success		: 	function(data){					    		
					    		$('#cart a div p').text(data + " тг");
					    		$('#cart1').text("Полный заказ: " + data + " тг");
					    		$('#food-sum-id'+ids).text(prices * amounts);
					    		if (parseInt($('#cart a div p').text()) > 2000) {
									$('#submit').prop('disabled', false);
									$("#submit").css("opacity","1");
									$("#submitchecker").css("visibility","hidden");
								} else {
									$('#submit').prop('disabled', true);
									$("#submit").css("opacity","0.3");
									$("#submitchecker").css("visibility","visible");
								}
					    	}
					  });
					}

				  }  				  
			});

		    $('.add').on('click',function(){
		        var $qty=$(this).closest('.addcart').find('.orderamount');
		        var currentVal = parseInt($qty.val());		        
		        if (!isNaN(currentVal)) {
		        	ids = parseInt($(this).closest('.addcart').find('.food-id').val());
		        	prices = parseInt($(this).closest('.addcart').find('.food-price').val());
		        	amounts = currentVal + 1;
		            $qty.val(currentVal + 1);	            		    
					  $.ajax({
					  		type 		:	"POST",
					  		url			: 	"addcart.php",
					  		data 		: 	{ id 	: 	parseInt($(this).closest('.addcart').find('.food-id').val()),
					    					price 	: 	parseInt($(this).closest('.addcart').find('.food-price').val()),
					    					amount 	: 	(currentVal + 1),
					    					sign 	: 	'add'},			
					    	success		: 	function(data){
					    		$('#cart a div p').text(data + " тг");
					    		$('#cart1').text("Полный заказ: " + data + " тг");
					    		$('#food-sum-id'+ids).text(prices * amounts);
					    		if (parseInt($('#cart a div p').text()) > 2000) {
									$('#submit').prop('disabled', false);
									$("#submit").css("opacity","1");
									$("#submitchecker").css("visibility","hidden");
								} else {
									$('#submit').prop('disabled', true);
									$("#submit").css("opacity","0.3");
									$("#submitchecker").css("visibility","visible");
								}
					    	}
					  });
				  }     
		    });
		    $('.minus').on('click',function(){
		        var $qty=$(this).closest('.addcart').find('.orderamount');
		        var currentVal = parseInt($qty.val());
		        if (!isNaN(currentVal) && currentVal > 0) {
		        	ids = parseInt($(this).closest('.addcart').find('.food-id').val());
		        	prices = parseInt($(this).closest('.addcart').find('.food-price').val());	
		        	amounts = currentVal - 1;
		            $qty.val(currentVal - 1);		        
			        $.ajax({
					  		type 		:	"POST",
					  		url			: 	"addcart.php",
					  		data 		: 	{ id 	: 	parseInt($(this).closest('.addcart').find('.food-id').val()),
					    					price 	: 	parseInt($(this).closest('.addcart').find('.food-price').val()),
					    					amount 	: 	(currentVal - 1),
					    					sign 	: 	'sub'},
					    	success		: 	function(data){					    		
					    		$('#cart a div p').text(data + " тг");
					    		$('#cart1').text("Полный заказ: " + data + " тг");						    		
					    		$('#food-sum-id'+ids).text(prices * amounts);
					    		if (parseInt($('#cart a div p').text()) > 2000) {
									$('#submit').prop('disabled', false);
									$("#submit").css("opacity","1");
									$("#submitchecker").css("visibility","hidden");
								} else {
									$('#submit').prop('disabled', true);
									$("#submit").css("opacity","0.3");
									$("#submitchecker").css("visibility","visible");
								}
					    	}
					  }); 
			        if(currentVal == 1 && cart != 1) {
			        	$(this).closest('.addcart').css("visibility","hidden");
			        }
		        }
		    });		   
		});
		function validate(evt) {
		  var theEvent = evt || window.event;
		  var key = theEvent.keyCode || theEvent.which;
		  key = String.fromCharCode( key );
		  var regex = /[0-9]|\./;
		  if( !regex.test(key) ) {
		    theEvent.returnValue = false;
		    if(theEvent.preventDefault) theEvent.preventDefault();
		  }
		}
		function toCheck1(){
			var name = $('#name').val();
      		var surname = $('#surname').val(); 
      		var address = $("#address").val();  		
      		var telephone = $("#telephone").val();

      		if (name == null || name == ""){
  				$("#name").css("border-color","red").css("box-shadow","0 0 10px red");
  				$("#error1").css("visibility","visible");
  			} else {
  				$("#name").removeCss(); 				
  				$("#error1").css("visibility","hidden");
  			}
	      	
			if (surname == null || surname == ""){
  				$("#surname").css("border-color","red").css("box-shadow","0 0 10px red");  	
  				$("#error2").css("visibility","visible");
  			} else {
  				$("#surname").removeCss(); 			
  				$("#error2").css("visibility","hidden");	
  			}

			if (address == null || address == ""){
  				$("#address").css("border-color","red").css("box-shadow","0 0 10px red");  
  				$("#error3").css("visibility","visible");	
  			} else {
  				$("#address").removeCss(); 				
  				$("#error3").css("visibility","hidden");
  			}

  			if (telephone == null || telephone == ""){
  				$("#telephone").css("border-color","red").css("box-shadow","0 0 10px red");  
  				$("#error4").css("visibility","visible");	
  			} else {
  				$("#telephone").removeCss(); 			
  				$("#error4").css("visibility","hidden");
  			} 

		}
	</script> 

	<script> 
		$(document).ready(function(){
		$('#demo').Horinaja({
		capture:'demo',delai:0.3,
		duree:4,pagination:true});
		});
	</script>
</head>
<body>
	<div id="full-wraper">
	<div id="head-banner">
		<a href="index.php">
			<img src="img/logo_top.png" style="width:200px;height:142px;">
		</a>
		<ul>
			<li <?=echoActiveClassIfRequestMatches("menu")?>>
				<a href="menu.php" >Меню</a>
			</li>
			<li <?=echoActiveClassIfRequestMatches("about")?>>
				<a href="about.php">О Компании</a>				
			</li>
			<li <?=echoActiveClassIfRequestMatches("promotions")?>>
				<a href="promotions.php">Акции</a>				
			</li>
			<li <?=echoActiveClassIfRequestMatches("contacts")?>>				
				<a href="contacts.php">Контакты</a>
			</li>
		</ul>	
	</div>
	<div id="cart">
		<a href="cart.php">		
			<div>
				<img src="img/cart.png" height="50px" width="50px" style="float:left;">			
				<p style="float:left">
					<?php 
						echo $_SESSION['id0']['price']." тг";
					?>
				</p>
			</div>	
		</a>		
	</div>
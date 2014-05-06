<?php 
	include("header.php");	
?>
	<div class="top-container">
		<ul>
			<?php
				$result = mysqli_query($con,"SELECT DISTINCT type FROM content ORDER BY id ASC");
                while($row = mysqli_fetch_array($result)){ 	
                	echo '<li>';  
                	if (isset($_GET["type"]) && $_GET["type"] == $row['type']) {
                		echo '<a class="selected-menu" href="?type='.$row['type'].'">'.$row['type']."</a>";	
                	}  else {
                		echo '<a href="?type='.$row['type'].'">'.$row['type']."</a>";	
                	}                	
					echo '</li>';
               	}
             ?>  	
			<!--<li>
				Первое блюдо
			</li>
			<li>
				Второе блюдо
			</li>
			<li>
				Салаты
			</li>
			<li>
				Напитки
			</li>
			-->
		</ul>
	</div>
	<div class="main-container">
		<ul class="food">

		<?php								
			if (!isset($_GET["type"])) $result = mysqli_query($con,"SELECT * FROM content ORDER BY id ASC"); 
			else $result = mysqli_query($con,"SELECT * FROM content WHERE type = '".$_GET["type"]."' ORDER BY id ASC"); 
                while($row = mysqli_fetch_array($result)){ 	
	                	$s = 'id'.$row['id'];
	                	$style = 'style = "visibility:hidden"';
	                	if (!isset($_SESSION[$s]['price']) || !isset($_SESSION[$s]['amount']) ) {
	                		$_SESSION[$s]['price'] = 0;
	                		$_SESSION[$s]['amount'] = 0;
	                	}
	                	if ($_SESSION[$s]['amount'] > 0) $style = 'style = "visibility:visible"';
	                	
	                	echo '<li>';	            
	                	if ( base64_encode( $row['foto'] ) === '') echo '<img src="img/food.jpg" />';  else   	
	                	echo '<img src="data:image/jpeg;base64,' . base64_encode( $row['foto'] ) . '" />';
	                	echo '<div class="food-desc">';
	                	echo '<h3 class="food-name">'.$row['name'].'</h3>';
	                	echo '<h3 class="food-price">'.$row['price'].' тг</h3>';
	                	echo '<img src="img/cart.png" height="50px" width="50px" style="float:left;">';	                	
	                	echo '<div class="addcart" '.$style.' >';
	                	echo '<button type="button" class="minus">-</button>';	                		                
	                	echo '<input class="orderamount" type="text" size="2" value="'.$_SESSION[$s]['amount'].'">';
	                	echo '<input class="food-id" type="text" value="'.$row['id'].'" style="display:none;">';
	                	echo '<input class="food-price" type="text" value="'.$row['price'].'" style="display:none;">';
	                	echo '<button type="button" class="add">+</button>';
	                	echo '</div>';
	                	echo '<div class="ingredients">';
	                	echo '<p>';
	                	$tok = strtok($row['ingredient'], ";");
						while ($tok !== false) {
							echo $tok;
	                		echo '<br/>';						    
						    $tok = strtok(";");
						}
	                	echo '</p>';				
	                	echo '</div>';
						echo '</div>';
						echo '</li>';
	                }
		?>
		<!--
			<li>
				<img src="img/food.jpg">
				<div class="food-desc">
					<h3 class="food-name">DONER</h3>	
					<h3>PRICE:200px</h3>
				</div>			
			</li>
						<li>
				<img src="img/food.jpg">
				<div class="food-desc">
					<h3 class="food-name">DONER</h3>	
					<h3>PRICE:200px</h3>
				</div>			
			</li>

			<li>
				<img src="img/food.jpg">
				<div class="food-desc">
					<h3 class="food-name">DONER</h3>	
					<h3>PRICE:200px</h3>
				</div>			
			</li>

			<li>
				<img src="img/food.jpg">
				<div class="food-desc">
					<h3 class="food-name">DONER</h3>	
					<h3>PRICE:200px</h3>
				</div>			
			</li>
			<li>
				<img src="img/food.jpg">
				<div class="food-desc">
					<h3 class="food-name">DONER</h3>	
					<h3>PRICE:200px</h3>
				</div>			
			</li>
			<li>
				<img src="img/food.jpg">
				<div class="food-desc">
					<h3 class="food-name">DONER</h3>	
					<h3>PRICE:200px</h3>
				</div>			
			</li>
			<li>
				<img src="img/food.jpg">
				<div class="food-desc">
					<h3 class="food-name">DONER</h3>	
					<h3>PRICE:200px</h3>
				</div>			
			</li>
			<li>
				<img src="img/food.jpg">
				<div class="food-desc">
					<h3 class="food-name">DONER</h3>	
					<h3>PRICE:200px</h3>
				</div>			
			</li>
			<li>
				<img src="img/food.jpg">
				<div class="food-desc">
					<h3 class="food-name">DONER</h3>	
					<h3>PRICE:200px</h3>
				</div>			
			</li>
		-->
		</ul>

	</div>
<?php
	include("footer.php");
?>
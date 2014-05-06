<?php 
	include("header.php");	
?>
<div class="main-container">
	
	<div id="demo" class="horinaja">
		<ul>
		<li><img src="img/gallery.png"></li>
		<li><img src="img/gallery.png"></li>	
		<?php
			$result = mysqli_query($con,"SELECT `description`,`foto` FROM gallery ORDER BY id DESC LIMIT 3");
                while($row = mysqli_fetch_array($result)){ 	
                	echo '<li>';                
                	if ( base64_encode( $row['foto'] ) === '') echo '<img src="img/promobig.png" />';  else
	                	echo '<img style="width:800px; height:360px;" src="data:image/jpeg;base64,' . base64_encode( $row['foto'] ) . '" />';	                
                	echo '</li>';
                }
		?>		
		</ul>
	</div>
		
	<!--<div id="gallery">
		<img src="img/gallery.png">
	</div>-->
	<div id="roll-promo">
		<div class="row">
			<p class="rowb">Наши рекомендации</p>
			<a href="menu.php" id="promo-menu">Перейти в меню</a>			
			<ul class="food">

			<?php								
				$result = mysqli_query($con,"SELECT * FROM content ORDER BY id DESC LIMIT 5");
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
	                	echo '<input class="orderamount" type="text" size="2" value="'.$_SESSION[$s]['amount'].'" onkeypress="validate(event)">';
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
		</ul>

		</div>
		
		<div id="promo-roll">			
		</div>		
	</div>	
</div>

<?php 
	include("footer.php");
?>

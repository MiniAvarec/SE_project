<?php 
	include("header.php");	
?>

	<div class="main-container">
		<?php
			$result = mysqli_query($con,"SELECT `description`,`foto` FROM promotion ORDER BY id DESC LIMIT 3");
                while($row = mysqli_fetch_array($result)){ 	
                	echo '<div class="promo-full">';                
                	if ( base64_encode( $row['foto'] ) === '') echo '<img src="img/promobig.png" />';  else
	                	echo '<img  style="width:600px; height:340px; src="data:image/jpeg;base64,' . base64_encode( $row['foto'] ) . '" />';
	                echo '<p>';
	                	echo $row['description'];
	                echo '</p>';
                	echo '</div>';
                }
		?>
		<!--<div class="promo-full">
			<img src="img/promobig.png">
			<p class="description" style="display:block">
				Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod
				tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam,
				quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo
				consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse
				cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non
				proident, sunt in culpa qui officia deserunt mollit anim id est laborum.
			</p>
		</div>
		
		<div class="promo-full">
			<img src="img/promobig.png">
			<p class="description" style="display:block">
				Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod
				tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam,
				quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo
				consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse
				cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non
				proident, sunt in culpa qui officia deserunt mollit anim id est laborum.
			</p>
		</div>
		<div class="promo-full">
			<img src="img/promobig.png">
			<p class="description" style="display:block">
				Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod
				tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam,
				quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo
				consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse
				cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non
				proident, sunt in culpa qui officia deserunt mollit anim id est laborum.
			</p>
		</div>
		<div class="promo-full">
			<img src="img/promobig.png">
			<p class="description" style="display:block">
				Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod
				tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam,
				quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo
				consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse
				cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non
				proident, sunt in culpa qui officia deserunt mollit anim id est laborum.
			</p>
		</div>-->
	</div>

<?php
	include("footer.php");
?>
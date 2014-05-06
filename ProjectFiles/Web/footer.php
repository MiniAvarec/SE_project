	<div class="divider"></div>
	<div id="bot-contacts">
		<div class="mid">
			<p>Телефон доставки в г.Алматы</p>
			<p>+7 (701) <span class="big-mid"> 777-77-77</span></p>
			<p>+7 (701) <span class="big-mid"> 777-77-77</span></p>
		</div>
	</div>
	<div class="divider"></div>
	<div id="promo">
		<div class="row">
			<p class="rowb">Акции</p>
			<a href="promotions.php" class="rowe">Смотреть все</a>			
		</div>
		<?php
			$result = mysqli_query($con,"SELECT `name`,`foto` FROM promotion ORDER BY id DESC LIMIT 3");
                while($row = mysqli_fetch_array($result)){ 	
                	echo '<div class="promo-ban">';
                	if ( base64_encode( $row['foto'] ) === '') echo '<img src="img/food.jpg" />';  else
	                	echo '<img style="width:370px; height:220px;" src="data:image/jpeg;base64,' . base64_encode( $row['foto'] ) . '" />';
	          
                	echo '</div>';
                }                
		?>
<!--		<div class="promo-ban">			
			<img src="img/promosmall.png">
		</div>
		<div class="promo-ban">			
			<img src="img/promosmall.png">
		</div>
		<div class="promo-ban">		
			<img src="img/promosmall.png">	
		</div>-->
	</div>

	<div id="footer">	
		<a href="index.php">
			<img src="img/logo_top.png">
		</a>
		<ul>
			<li>
				<a href="menu.php">Меню</a>
			</li>
			<li>
				<a href="about.php">О Компании</a>				
			</li>			
		</ul>
		<ul>
			<li>
				<a href="promotions.php">Акции</a>				
			</li>
			<li>				
				<a href="contacts.php">Контакты</a>
			</li>
			<li>
				Доставка в г. Алматы: +7 (727) 777-77-77
			</li>	
		</ul>
	</div>
	</div>
	</body>
</html>
<?php
mysqli_close($con);
?>
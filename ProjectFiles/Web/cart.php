<?php 
	include("header.php");		
?>
	<div class="main-container">
		<div id="orders">		
				<?php				
				$ok = 0;				 
				 if (isset($_SESSION['orders'])){
				 	$p = array_values($_SESSION['orders']);
				 	if (sizeof($p) > 0) {
				 		$ok = 1;
				 	}
				 }
				 else
				 	$p = array();
				 if ($ok == 1){
				 echo "<h2>Ваша Корзина</h2>";
				 echo "<table>";				 				 
				 for ($i = 0; $i < sizeof($p); $i++){				 	
				 	$result = mysqli_query($con,"SELECT * FROM content WHERE id=".$p[$i]);
				 	echo '<tr class="food-name">';	                		      
	                while($row = mysqli_fetch_array($result)){ 		                	
	                	echo '<td style="padding-right:500px;">'.$row['name'].'</td>';
	                	$_SESSION['id'.$p[$i]]['name'] = $row['name'];
	                	echo '<td>'.$row['price'].' тг </td>';	  
	                	echo '<td>';
	                	echo '<div class="addcart" style="visibility:visible" >';
	                	echo '<button type="button" class="minus">-</button>';	                		                
	                	echo '<input class="orderamount" type="text" size="2" value="'.$_SESSION['id'.$p[$i]]['amount'].'" onkeypress="validate(event)">';
	                	echo '<input class="food-id" type="text" value="'.$row['id'].'" style="display:none;">';
	                	echo '<input class="food-price" type="text" value="'.$row['price'].'" style="display:none;">';
	                	echo '<button type="button" class="add">+</button>';
	                	echo '</td>';
	                	echo '</div>';

	               	}
	               	echo '<td style="padding-left:130px" id="food-sum-id'.$p[$i].'">'.$_SESSION['id'.$p[$i]]['amount'] * $_SESSION['id'.$p[$i]]['price'].'</td>';
	               	echo '</tr>';
              	 }
              	 echo "<tr> <td colspan='5'><h3 id='cart1' style='text-align:right;'>Полный заказ: ".$_SESSION['id0']['price']." тг</h3></td></tr>";              	 
              	 echo "</table>";
              	}
				?>
				
		</div>
		<div class="divider"></div>
		<div id="conditions">
			<h3 style="font-size:30px">
				Условия доставки
			</h3>
			<p style="font-size:17px;line-height:40px;">
			Минимальная сумма заказа 2000 тг. + бесплатная доставка.<br/>
			Количество ланч-боксов определяется объемом заказа.<br/>
			Бесплатная доставка действует в пределах:<br/>
			Алматы: Бостандыкского, Алмалинского, Медеуского (до малой станицы), Ауэзовского (до ул. б. Момышулы) районов.<br/>
			Стоимость доставки в другие районы города от 700 тг. Доставка в отдаленные районы рассматривается по ситуации, в зависимости от загруженности дорог и количества заказов.<br/>
			Режим работы: ежедневно с 09:00 до 23:00<br/>
			</p>			
		</div>
		<div class="divider"></div>
		<?php
		if ($ok == 1)
		echo '
		<div id="orders-confirm">		
			<form id="form-orders" action="order.php" method="post">
				<table>			
						<tr class="trow">
							<td>
								<input type="text" name="name" id="name" maxlength="20" placeholder="Имя">					
								<span class="important">*</span>						
							</td>	
							<td rowspan="4" style="padding-left:160px;">
								<textarea name="area" id="area" placeholder="Дополнительная информация для доставки"></textarea>				
							</td>							
						</tr>	
						<tr class="trow">
							<td>
								<input type="text" id="surname" name="surname" maxlength="20" placeholder="Фамилия">	
								<span class="important">*</span>										
							</td>	
						</tr>	 
						<tr class="trow">
							<td>
								<input type="text" id="address" name="address" maxlength="20" placeholder="Адрес доставки">					
								<span class="important">*</span>						
							</td>	
						</tr>	
						<tr class="trow">
							<td>
								<input type="tel" id="telephone" name="telephone" maxlength="20" placeholder="Контактный телефон">					
								<span class="important">*</span>						
							</td>	
						</tr class="trow">	
						<tr>
							<td>
								<input type="text" id="change" name="change" maxlength="20" placeholder="С какой суммы приготовить сдачу">					
							</td>							
							<td style="padding-left:160px;">
								<input type="submit" id="submit" value="Заказать">
								<span id="submitchecker" style="color:grey">Заказ меньше 2000тг</span>
							</td>	
						</tr>							
				</table>
			</form>
		</div>';
		?>
	</div>

<?php
	include("footer.php");
?>
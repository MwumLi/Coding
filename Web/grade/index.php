<?php 
include_once("autoload.php");
?>
<!DOCTYPE html>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta name="keywords" content="" />
<meta name="description" content="" />
<title>评分</title>
<link rel="stylesheet" href="css/lrtk.css">
<link rel="stylesheet" href="css/main.css">
<script src="js/hashtabber.js"></script>
<script src="js/jquery.min.js"></script>
</head>
<body>
 <a href="result.php"><button>结果排名</button></a>
<section class="example">
	<section class="hashTabber-sandstone-wrapper">
	<ol class="hashTabber-nav hashTabber-sandstone" data-hashtabber-id="dinosaurs" data-hashtabber-default="pterosaur">
		<h2>所有队伍:</h2>
<?php
$Data = new IndexData();
$rest =  $Data->getPlayerData();
if (is_array($rest)){
	for($i = 0; $i < count($rest); $i++ )
	{
?>
			<li data-hashtabber-pair=<?php echo '"'."competiter".($i+1).'"'; 
				if(isset($_POST['playid'])) {
					if($_POST['playid']==($i+1)) {
						echo 'class="active"';
					}

				} else {
					if($i == 0)
						echo 'class="active"';
				}

?> id="myli">
				<label><?php echo $rest[$i]['play_id']."号--".$rest[$i]['name'];?></label>
				<a href="#dinosaurs=<?php echo 'competiter'.($i+1);?>" >评级</a>
			</li>
<?php
	}
}else{
	echo "<script>alert('数据加载失败!');</script>";
	header("Location: index.php");
} 
?>

	</ol>
	<ol class="hashTabber-data hashTabber-sandstone" data-hashtabber-id="dinosaurs">
<?php
$Data = new IndexData();
if (isset($_POST['submit']))
{
	$dataArray = array('playid' =>$_POST['playid'] ,'judger1'=>$_POST['judger1'],'judger2'=>$_POST['judger2'],'judger3'=>$_POST['judger3'],'judger4'=>$_POST['judger4'],'judger5'=>$_POST['judger5'],'judger6'=>$_POST['judger6'] ,'judger7'=>$_POST['judger7'], 'judger8'=>$_POST['judger8'],'judger9'=>$_POST['judger9']);
	$rest = $Data->saveClassEvaluate($dataArray);
	if ($rest == false)
	{
		echo "<script>alert('数据访问数据库失败');</script>";
		header("Location: index.php");
	} 
}
$playData = $Data->getPlayerData();
if (is_array($playData)){

?>

<?php 
		
			for($z=1; $z<=15; $z++) {
			?>
			<li data-hashtabber-pair="competiter<?php echo $z?>"  
			<?php 
				if(isset($_POST['playid'])) {
					if($_POST['playid']==$z) {
						echo 'class="active"';
					}

				} else {
					if($z == 1)
						echo 'class="active"';
				}
				$sql = "select * from tb_grade where play_id = $z";
				$oper = new OperDB();
				$data = $oper->executeSQL($sql);
				$data = $data[0];
			?>
			>
				<article>
					<h3><?php echo $playData[$z-1]['play_id']."号队伍--".$playData[$z-1]['name'];?></h3>
					<form method="post" action="index.php">
					<p><label>评委1：</label><input name="judger1" type="number" maxlength="" min="0" max="100" value="<?php echo $data['judger1'];?>"></p>
					<p><label>评委2：</label><input name="judger2" type="number" maxlength="" min="0" max="100" value="<?php echo $data['judger2'];?>"></p>
					<p><label>评委3：</label><input name="judger3" type="number" maxlength="" min="0" max="100" value="<?php echo $data['judger3'];?>"></p>
					<p><label>评委4：</label><input name="judger4" type="number" maxlength="" min="0" max="100" value="<?php echo $data['judger4'];?>"></p>
					<p><label>评委5：</label><input name="judger5" type="number" maxlength="" min="0" max="100" value="<?php echo $data['judger5'];?>"></p>
					<p><label>评委6：</label><input name="judger6" type="number" maxlength="" min="0" max="100" value="<?php echo $data['judger6'];?>"></p>
					<p><label>评委7：</label><input name="judger7" type="number" maxlength="" min="0" max="100" value="<?php echo $data['judger7'];?>"></p>
					<p><label>评委8：</label><input name="judger8" type="number" maxlength="" min="0" max="100" value="<?php echo $data['judger8'];?>"></p>
					<p><label>评委9：</label><input name="judger9" type="number" maxlength="" min="0" max="100" value="<?php echo $data['judger9'];?>"></p>
					<input type="hidden" name="playid" value='<?php echo $z?>'>
					  <button type="submit" id="sub" name ="submit">提交</button> <button class="reset" onclick="reset()">重置</button>
					</p>
					</form>
				</article>
			 </li>
		<?php } ?>
<?php
}
?>
	 </ol>

	</section>
</section>
<script>


var tabber = new HashTabber();
tabber.run();
/*
	$(function(){ 

	$( window ).scroll(function() { 
		var hh=$('ol.hashTabber-data.hashTabber-sandstone'); 
		var sctop = $(this).scrollTop();
		if(sctop>50&&sctop<450) 
		{  
			hh.css("marginTop",sctop-50);
		}
		else
			hh.css("marginTop",0);

	});
}); */
</script>

</body>
</html>

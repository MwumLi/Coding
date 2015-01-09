<?php 
    include_once("autoload.php");
?>
<!DOCTYPE html>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta name="keywords" content="" />
<meta name="description" content="" />
<title>结果排名</title>
<link rel="stylesheet" href="css/lrtk.css">
<link rel="stylesheet" href="css/main.css">
<script src="js/hashtabber.js"></script>
<script src="js/jquery.min.js"></script>
<style type="text/css">
#setSection {
width: 100%;
text-align: center;
}
table {
text-align: center;
margin-left: 25%;
}
h2 {
margin-left: -8%;
}
td {
width: 12em;
}
</style>
</head>
<body>
 <a href="index.php"><button>继续评分</button></a>
<section class="example">
	<section class="hashTabber-sandstone-wrapper" id="setSection">
		<h2>最终排名</h2>
<table border="1" cellspacing="20">
<tr>
<th>排名</th>
<th>参赛队伍</th>
<th>平均分</th>
</tr>
<?php
$indexdata = new IndexData();
$sortplayer=$indexdata->sortPlayer();
$k=0;

foreach ($sortplayer as $key => $value) {
	$k++;
	echo "<tr>";
	echo "<td>第".$k."名</td>";
	echo "<td>".$value['name']."</td>";
	echo "<td>".$value['score']."</td>";
	echo "<tr/>";

}

?>
</table>

	</section>
</section>

</body>
</html>

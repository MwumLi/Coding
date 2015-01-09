<?php
// Author: zbqyexingknog
// Creat Date: 2014.8
// Email: zbqyexingkong@163.com
// Github:https://github.com/zbqyxingkong

include_once ("../autoload.php");

class IndexData{
	

	public function __construct(){
		
	}

/**
 *  存储主页面获取数据库grade表中的数据; 
 * @return [type]           true:保存数据成功，false：保存数据失败.
 */
	public function saveClassEvaluate($dataArray){

		$oper = new OperDB();
		$playid = $dataArray['playid'];
		$judger1 = $dataArray['judger1'];
		$judger2 = $dataArray['judger2'];
		$judger3 = $dataArray['judger3'];
		$judger4 = $dataArray['judger4'];
		$judger5 = $dataArray['judger5'];
		$judger6 = $dataArray['judger6'];
		$judger7 = $dataArray['judger7'];
		$judger8 = $dataArray['judger8'];
		$judger9 = $dataArray['judger9'];
		
//		echo  $judger1." | ".$judger2." | ".$judger3." | ".$judger4." | ".$judger5." | ".$judger6." | ".$judger7." | ".$judger8." | ".$judger9." | ".$playid; 
		$sum  = $judger1 + $judger2 + $judger3 + $judger4 + $judger5 + $judger6 + $judger7 + $judger8 + $judger9; 
//		echo " |".$sum;
		$min = $judger1;
		$max = $judger1;
		for($i=2; $i<=9; $i++)	{
			if($min > $dataArray["judger".$i])
				$min = $dataArray["judger".$i];
			if($max < $dataArray["judger".$i])
				$max = $dataArray["judger".$i];
		}

//				echo "<br/>".$min." | ".$max;
		$ave = ($sum-$min-$max)/7;
		$ave = round($ave, 1);
		$sql = "UPDATE tb_grade SET judger1=$judger1, judger2=$judger2,judger3=$judger3,judger4=$judger4,judger5=$judger5,judger6=$judger6,judger7=$judger7,judger8=$judger8,judger9=$judger9,score=$ave where play_id = $playid";
		$ret = $oper->executeSQL($sql);
		// print_r($ret);
		return $ret;
}

	public function getPlayerData(){

		$oper = new OperDB();

		$sql = "select play_id,name from tb_player";
		$ret = $oper->executeSQL($sql);
		return $ret;
	}

	public function sortPlayer(){

		$oper = new OperDB();
		$k = 0;

		$sql = "select * from tb_grade order by score desc";
		$resut = $oper->executeSQL($sql);
		if (is_array($resut)){
			foreach ($resut as $key => $value) {
				$sql = "select * from tb_player where play_id=$value[play_id]";
				$playsut= $oper->executeSQL($sql);
				$sortplayer[$k] = $playsut[0]; 
				$k++;
			}
		}
		for ($i=0; $i < count($sortplayer); $i++) { 
			$sortplayer[$i]['judger1'] = $resut[$i]['judger1'];
			$sortplayer[$i]['judger2'] = $resut[$i]['judger2'];
			$sortplayer[$i]['judger3'] = $resut[$i]['judger3'];
			$sortplayer[$i]['judger4'] = $resut[$i]['judger4'];
			$sortplayer[$i]['judger5'] = $resut[$i]['judger5'];
			$sortplayer[$i]['judger6'] = $resut[$i]['judger6'];
			$sortplayer[$i]['judger7'] = $resut[$i]['judger7'];
			$sortplayer[$i]['judger8'] = $resut[$i]['judger8'];
			$sortplayer[$i]['judger9'] = $resut[$i]['judger9'];
			$sortplayer[$i]['score'] = $resut[$i]['score'];
		}
//		foreach ($sortplayer as $key => $value) {
//			foreach ($value as $keys => $values) {
//				echo $keys."=>".$values;
//			}
//			echo "<br/>";
//		}
		return $sortplayer;
	}

}

?>

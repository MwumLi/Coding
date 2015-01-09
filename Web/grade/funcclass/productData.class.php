<?php
// Author: zbqyexingknog
// Creat Date: 2014.8
// Email: zbqyexingkong@163.com
// Github:https://github.com/zbqyxingkong

include_once("../autoload.php");

define("PAGESIZE",4); //定义每次从数据库中取出4条数据

class productData{
	private $resultData;

	public function __construct(){
		$this->resultData  = false;
	}

	public function getAllCourse($page){
		$oper  = new OperDB();
		// $produc = new DomDocument();
		$classNum = 0;

		$sql = "select count(*) as total from courses order by course_id desc";
		$rest = $oper->executeSQL($sql);
		$message_count = $rest[0]['total'];
		

		$offset  = ($page - 1) * PAGESIZE;//计算偏移量
		if ($offset > $message_count)
		{
			$this->resultData = false;
			return false;
		}

		$sql = "select lecturer_id,name,watch_man,good_man,pic_path,pic_name from courses  order by course_id limit  $offset,".PAGESIZE;
		$ret = $oper->executeSQL($sql);

		if (is_array($ret)){
			// print_r($ret);
			foreach ($ret as $key => $value) {
				$sql = "select name from lecturers where lecturer_id = $value[lecturer_id]" ;
				$lectName = $oper->executeSQL($sql);
				if (is_array($lectName)){
					 $this->resultData[$classNum]['lectName'] = $lectName[0]['name'];
					 $this->resultData[$classNum]['classname'] = $value['name'];
					 $this->resultData[$classNum]['watch_man'] = $value['watch_man'];
					 $this->resultData[$classNum]['good_man'] = $value['good_man'];
					 $this->resultData[$classNum]['pic_path'] = ($value['pic_path']."/".$value['pic_name']);
					 $classNum++;
				}
			}
		}else{
			$this->resultData = false;	
		}

	}

	public function getResult()
	{
		return $this->resultData;
	}
}


//  $produc = new productData();
//         $produc->getAllCourse(1);
//         $rest = $produc->getResult();
            

// if (is_array($rest))
// {
// 	print_r($rest);
// }

?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
	<title>Use varible</title>
</head>
<body>
<?php
 //Get some information about server and script 
$file = $_SERVER['SCRIPT_FILENAME'];
$name = $_SERVER['SCRIPT_NAME'];
$user = $_SERVER['HTTP_USER_AGENT'];
$server = $_SERVER['SERVER_SOFTWARE'];
echo "<p>long name: $file</p>";
echo "<p>short name: $name</p>";
echo "<p>user: $user</p>";
echo "<p>server: $server</p>";
if (isset($file)) {
	echo "true";
} else {
	echo "false";
}
$var = "";


     // 结果为 false，因为 $var 已设置
     if (isset($var)) { 
		 echo '$var is  set at all';
		 if(empty($var))
			 echo "empty";
		 else
			 echo "no";
	 } else
		 echo "hehe";
echo "<br />";
$arr = array('I'=>'liluo', 'He'=>'xnbc', 'She'=>'Pan');
$str = implode('  **', $arr);
echo $str;
?>

</body>
</html>


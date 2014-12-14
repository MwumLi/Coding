<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
	<title>Use constants</title>
</head>
<body>
<?php 
define ('TODAY', 'Sat Oct 25 2014');
echo '<p>Today is '.TODAY.'<br /> This server is running version <b>'.PHP_VERSION.'</b> of PHP on the <b>'.PHP_OS.'</b> operating system.</p>';
?>

</body>
</html>

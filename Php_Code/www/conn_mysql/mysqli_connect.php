<?php 

// Set the database access infotmation as constants
DEFINE ('DB_HOST', 'localhost');
DEFINE ('DB_USER', 'root');
DEFINE ('DB_PASS', 'woaini');
DEFINE ('DB_NAME', 'sitename');

//Make the connection
$dbc = @mysqli_connect (DB_HOST, DB_USER, DB_PASS, DB_NAME) or 
	die ('Could not connect to MYSQL: '. mysqli_error() );

// Set the encoding...
mysqli_query($dbc, 'set names utf8');

?>

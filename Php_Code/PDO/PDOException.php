<?php
$PHP_USER="root";
$PASS="woaini";
try { 
  $db_conn = new PDO('mysql:host=localhost;dbname=recipes', $PHP_USER, $PASS);
} catch (PDOException $e) {
  echo "Could not connect to database";
}
echo "connect";
?>

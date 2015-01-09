<?php  

$page_title = 'Register';
include ('includes/header.html');
if ($_SERVER['REQUEST_METHOD'] == 'POST') {

	//connect database
	require ('./mysqli_connect.php');

	$errors = array(); // Initialize an error array.

	// check for a first name
	if (empty($_POST['first_name'])) {
		$errors[] = 'You forget to enter your first name.';
	} else {

		$fn = mysqli_real_escape_string($dbc, trim($_POST['first_name']));
	}

	// Check for a last name
	if (empty($_POST['last_name'])) {
		$errors[] = 'You forget to enter your last name.';
	} else {
		$ln = mysqli_real_escape_string($dbc, trim($_POST['last_name']));
	}

	// Check for an email address
	if (empty($_POST['email'])) {
		$errors[] = 'You forgot to enter your email address';
	} else {
		$e = mysqli_real_escape_string($dbc, trim($_POST['email']));
		$q = "select user_id from users where email='$e';";
		$r = mysqli_query($dbc, $q);
		$num = mysqli_num_rows($r);

		if ($num > 0) {
			$errors[] = 'Email is registered.';
		}
	}
	
	// Check for a password and match against the confirmed password  
	if (!empty($_POST['pass1'])) {
		if ($_POST['pass1'] != $_POST['pass2']) {
			$errors[] = 'Your password dis not match the confirmed password.';
		} else {
			$p = mysqli_real_escape_string($dbc, trim($_POST['pass1']));
		} 
	} else {
		$errors[] = 'You forget to enter your password.';
	}

	echo "<br />Hehe<br />";
	if (empty($errors)) {

		$q = "INSERT INTO  users (first_name, last_name, email, pass, registration_date) values ('$fn', '$ln', '$e', SHA1('$p'), NOW() )";
		//Run the query
		$r = @mysqli_query ($dbc, $q);
		if ($r) {
			echo '<h1>Thank you!</h1>
		<p>You are now registered. In Chapter 12 you will actually be able to log in!</p><p><br /></p>';
		} else {
			echo '<p>' . mysqli_error($dbc) . '<br /><br />Query: ' . $q . '</p>';
		} // End of if ($r) IF.
		mysqli_close($dbc);
		include ('includes/footer.html');
		exit();
	} else {
		
		echo '<h1>Error!</h1>
			<p class="error">The following error(s) occurred:<br />';
		foreach ($errors as $msg) {
			echo " - $msg<br />\n";
		}
		echo '</p><p>Please try again.</p><p><br /></p>';
	}
	mysqli_close($dbc);
}
?>
<h1>Register</h1>
<form action="register.php" method="post">
	<p>First Name: <input type="text" name="first_name" size="15" maxlength="20" value="<?php if (isset($_POST['first_name'])) echo $_POST['first_name']; ?>" /></p>
	<p>Last Name: <input type="text" name="last_name" size="15" maxlength="40" value="<?php if (isset($_POST['last_name'])) echo $_POST['last_name']; ?>" /></p>
	<p>Email Address: <input type="text" name="email" size="20" maxlength="60" value="<?php if (isset($_POST['email'])) echo $_POST['email']; ?>"  /> </p>
	<p>Password: <input type="password" name="pass1" size="10" maxlength="20" value="<?php if (isset($_POST['pass1'])) echo $_POST['pass1']; ?>"  /></p>
	<p>Confirm Password: <input type="password" name="pass2" size="10" maxlength="20" value="<?php if (isset($_POST['pass2'])) echo $_POST['pass2']; ?>"  /></p>
	<p><input type="submit" name="submit" value="Register" /></p>
</form>

<?php include ('includes/footer.html'); ?>

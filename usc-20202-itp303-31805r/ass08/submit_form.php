<?php
	function missing_POST($key) {
		return !isset($_POST['fname']) || empty($_POST['fname']);
	}

	# Form submission messages.
	## Submission time.
	date_default_timezone_set('America/Los_Angeles');
	$time = 'This form was submitted on ' . date('l, F j, Y') . ' at ' . date('h:i:s A') . '.';

	## Full name.
	$name = (
		missing_POST('fname') || missing_POST('lname')
		? '<div class="text-danger">Not provided.</div>'
		: $_POST['fname'] . ' ' . $_POST['lname']
	);
	
	## Phone number match.
	$phone = (
		missing_POST('phone') || missing_POST('phone-confirm')
		? '<div class="text-danger">Not provided.</div>'
		: (
			$_POST['phone'] != $_POST['phone-confirm']
			? '<div class="text-danger">Phone numbers do not match.</div>'
			: '<div class="text-success">Phone numbers match.</div>' . $_POST['phone']
		)
	);
	
	## Order.
	$order = (
		missing_POST('order')
		? '<div class="text-danger">Not provided.</div>'
		: $_POST['order']
	);
	
	## Size.
	$size = (
		missing_POST('size')
		? '<div class="text-danger">Not provided.</div>'
		: $_POST['size']
	);
	
	## Flavor shot(s).
	$flavors = (
		missing_POST('flavor')
		? 'None.'
		: implode(' ', $_POST['flavor'])
	);
?>
<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title>Confirmation</title>
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css">
</head>
<body>
	<div class="container">
		<div class="row">
			<h1 class="col-12 mt-5 mb-3">Order Confirmation</h1>
		</div> <!-- .row -->
	</div> <!-- .container -->
	
	<div class="container">
		<div class="row mt-3">
			<div>
				<!-- Change this to date/time that this was submitted. -->
				<?=$time?>
				
			</div>
		</div>

		<div class="row mt-4">
			<div class="col-4 text-right">Full Name:</div>
			<div class="col-8">
				<!-- PHP Output Here -->
				<?=$name?>
				
			</div>
		</div> <!-- .row -->

		<div class="row mt-3">
			<div class="col-4 text-right">Phone Number Match:</div>
			<div class="col-8">
				<!-- PHP Output Here -->
				<?=$phone?>
				
			</div>
		</div> <!-- .row -->

		<div class="row mt-3">
			<div class="col-4 text-right">Order:</div>
			<div class="col-8">
				<!-- PHP Output Here -->
				<?=$order?>
				
			</div>
		</div> <!-- .row -->
		<div class="row mt-3">
			<div class="col-4 text-right">Size:</div>
			<div class="col-8">
				<!-- PHP Output Here -->
				<?=$size?>
				
			</div>
		</div> <!-- .row -->

		<div class="row mt-3">
			<div class="col-4 text-right">Flavor shot(s): </div>
			<div class="col-8">
				<!-- PHP Output Here -->
				<?=$flavors?>
				
			</div>
		</div> <!-- .row -->

		<div class="row mt-4 mb-4">
			<a href="form.php" role="button" class="btn btn-primary">Back to Form</a>
		</div> <!-- .row -->

	</div> <!-- .container -->

</body>
</html>
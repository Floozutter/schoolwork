<?php
	function attempt() {
		// Guarantee dvd_title_id exists.
		$dvd_title_id = $_GET['dvd_title_id'];
		if (!isset($dvd_title_id) || empty($dvd_title_id)) {
			return '<div class="text-danger font-italic">Missing dvd_title_id!</div>';
		}
		
		// Connect to database.
		$mysqli = new mysqli(
			'303.itpwebdev.com',
			'dchoi933_uwu',
			'0x4BE71AF2459CF83899EC9DC2CB60E22AC4B3047E0211034BBABE9D174C069DD6',
			'dchoi933_dvd_db'
		);
		if ($mysqli->connect_errno) {
			return '<div class="text-danger font-italic">Connect error!</div>';
		}
		
		// Query.
		$query = "DELETE FROM dvd_titles WHERE dvd_title_id = $dvd_title_id;";
		$results = $mysqli->query($query);
		if (!$results) {
			return '<div class="text-danger font-italic">Query error! ' . $query . '</div>';
		}
	
		// Return success message.
		return '<div class="text-success"><span class="font-italic">' . $dvd_title_id . '</span> was successfully deleted.</div>';
	}
	
	$msg = attempt();
?>
<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title>Delete a DVD | DVD Database</title>
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css">
</head>
<body>
	<ol class="breadcrumb">
		<li class="breadcrumb-item"><a href="index.php">Home</a></li>
		<li class="breadcrumb-item"><a href="search_form.php">Search</a></li>
		<li class="breadcrumb-item"><a href="search_results.php">Results</a></li>
		<li class="breadcrumb-item active">Delete</li>
	</ol>
	<div class="container">
		<div class="row">
			<h1 class="col-12 mt-4">Delete a DVD</h1>
		</div> <!-- .row -->
	</div> <!-- .container -->
	<div class="container">
		<div class="row mt-4">
			<div class="col-12">
				<?=$msg?>

			</div> <!-- .col -->
		</div> <!-- .row -->
		<div class="row mt-4 mb-4">
			<div class="col-12">
				<a href="search_results.php" role="button" class="btn btn-primary">Back to Search Results</a>
			</div> <!-- .col -->
		</div> <!-- .row -->
	</div> <!-- .container -->
</body>
</html>
<?php
	function missing_POST($key) {
		return !isset($_POST[$key]) || empty($_POST[$key]);
	}
	function null_fallback_POST($key) {
		return (
			missing_POST($key)
			? 'NULL'
			: $_POST[$key]
		);
	}
	function null_fallback_quoted_POST($key) {
		return (
			missing_POST($key)
			? 'NULL'
			: '\'' . $_POST[$key] . '\''
		);
	}
	
	function attempt() {
		// Guarantee title exists.
		if (missing_POST('title')) {
			return '<div class="text-danger font-italic">Missing title!</div>';
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
		
		// Get POST values.
		$title = null_fallback_quoted_POST('title');
		$release_date = null_fallback_quoted_POST('release_date');
		$award = null_fallback_quoted_POST('award');
		$label_id = null_fallback_POST('label_id');
		$sound_id = null_fallback_POST('sound_id');
		$genre_id = null_fallback_POST('genre_id');
		$rating_id = null_fallback_POST('rating_id');
		$format_id = null_fallback_POST('format_id');
		
		// Query.
		$query = (
			' INSERT INTO dvd_titles (' .
			' 	title,' .
			' 	release_date,' .
			' 	award,' .
			' 	label_id,' .
			' 	sound_id,' .
			' 	genre_id,' .
			' 	rating_id,' .
			' 	format_id' .
			' ) VALUES (' .
			" 	$title," .
			" 	$release_date," .
			" 	$award," .
			" 	$label_id," .
			" 	$sound_id," .
			" 	$genre_id," .
			" 	$rating_id," .
			" 	$format_id" .
			' );'
		);
		$results = $mysqli->query($query);
		if (!$results) {
			return '<div class="text-danger font-italic">Query error! ' . $query . '</div>';
		}
		
		// Return success message.
		return '<div class="text-success"><span class="font-italic">' . $title . '</span> was successfully added.</div>';
	}
	
	$msg = attempt();
?>
<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title>Add Confirmation | DVD Database</title>
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css">
</head>
<body>
	<ol class="breadcrumb">
		<li class="breadcrumb-item"><a href="index.php">Home</a></li>
		<li class="breadcrumb-item"><a href="add_form.php">Add</a></li>
		<li class="breadcrumb-item active">Confirmation</li>
	</ol>
	<div class="container">
		<div class="row">
			<h1 class="col-12 mt-4">Add a DVD</h1>
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
				<a href="add_form.php" role="button" class="btn btn-primary">Back to Add Form</a>
			</div> <!-- .col -->
		</div> <!-- .row -->
	</div> <!-- .container -->
</body>
</html>
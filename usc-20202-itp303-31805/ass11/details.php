<?php
	function panic($errtype, $errno, $errmsg) {
		echo 'OOPSIE WOOPSIE!! Uwu We made a fucky wucky!! A wittle fucko boingo! The code monkeys at our headquarters are working VEWY HAWD to fix this!', '</br>';
		echo "$errtype $errno: $errmsg";
		exit;
	}
	
	function exists_GET($key) {
		return isset($_GET[$key]) && !empty($_GET[$key]);
	}
	
	function format_for_null($str) {
		return (empty($str) ? '<span class="font-italic">NULL</span>' : $str);
	}
	
	if (exists_GET('dvd_title_id')) {
		// Connect to database.
		$mysqli = new mysqli(
			'303.itpwebdev.com',
			'dchoi933_uwu',
			'0x4BE71AF2459CF83899EC9DC2CB60E22AC4B3047E0211034BBABE9D174C069DD6',
			'dchoi933_dvd_db'
		);
		if ($mysqli->connect_errno) { panic('MySQL Connection Error', $mysqli->connect_errno, $mysqli->connect_error); }

		// Query.
		$results = $mysqli->query(
			' SELECT' .
			' 	dvd_titles.dvd_title_id,' .
			' 	dvd_titles.title,' .
			' 	dvd_titles.release_date,' .
			' 	dvd_titles.award,' .
			' 	genres.genre,' .
			' 	ratings.rating,' .
			' 	labels.label,' .
			' 	formats.format,' .
			' 	sounds.sound' .
			' FROM' .
			' 	dvd_titles' .
			' 	LEFT JOIN genres' .
			' 		ON dvd_titles.genre_id = genres.genre_id' .
			' 	LEFT JOIN ratings' .
			' 		ON dvd_titles.rating_id = ratings.rating_id' .
			' 	LEFT JOIN labels' .
			' 		ON dvd_titles.label_id = labels.label_id' .
			' 	LEFT JOIN formats' .
			' 		ON dvd_titles.format_id = formats.format_id' .
			' 	LEFT JOIN sounds' .
			' 		ON dvd_titles.sound_id = sounds.sound_id' .
			' WHERE dvd_titles.dvd_title_id = ' . $_GET['dvd_title_id'] . ';'
		);
		if (!$results) { panic('MySQL Query Error', $mysqli->errno, $mysqli->error); }
		
		// Get associative array for first match. (Hopefully, the only match.)
		$dvd = $results->fetch_assoc();
		
		// Close connection.
		$mysqli->close();
	} else {
		$err = 'No dvd_title_id given!';
	}
?>
<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title>Details | DVD Database</title>
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css">
</head>
<body>
	<ol class="breadcrumb">
		<li class="breadcrumb-item"><a href="index.php">Home</a></li>
		<li class="breadcrumb-item"><a href="search_form.php">Search</a></li>
		<li class="breadcrumb-item"><a href="search_results.php">Results</a></li>
		<li class="breadcrumb-item active">Details</li>
	</ol>

	<div class="container">
		<div class="row">
			<h1 class="col-12 mt-4">DVD Details</h1>
		</div> <!-- .row -->
	</div> <!-- .container -->

	<div class="container">
		<div class="row mt-4">
			<div class="col-12">
				<div class="text-danger font-italic">
					<?=$err?>
				</div>
				<table class="table table-responsive">
					<tr>
						<th class="text-right">Title:</th>
						<td><?=format_for_null($dvd['title'])?></td>
					</tr>
					<tr>
						<th class="text-right">Release Date:</th>
						<td><?=format_for_null($dvd['release_date'])?></td>
					</tr>
					<tr>
						<th class="text-right">Genre:</th>
						<td><?=format_for_null($dvd['genre'])?></td>
					</tr>
					<tr>
						<th class="text-right">Label:</th>
						<td><?=format_for_null($dvd['label'])?></td>
					</tr>
					<tr>
						<th class="text-right">Rating:</th>
						<td><?=format_for_null($dvd['rating'])?></td>
					</tr>
					<tr>
						<th class="text-right">Sound:</th>
						<td><?=format_for_null($dvd['sound'])?></td>
					</tr>
					<tr>
						<th class="text-right">Format:</th>
						<td><?=format_for_null($dvd['format'])?></td>
					</tr>
					<tr>
						<th class="text-right">Award:</th>
						<td><?=format_for_null($dvd['award'])?></td>
					</tr>
				</table>
			</div> <!-- .col -->
		</div> <!-- .row -->
		<div class="row mt-4 mb-4">
			<div class="col-12">
				<a href="search_results.php" role="button" class="btn btn-primary">Back to Search Results</a>
				<a href="edit_form.php?dvd_title_id=<?=$dvd['dvd_title_id']?>" class="btn btn-warning">Edit This DVD</a>
			</div> <!-- .col -->
		</div> <!-- .row -->
	</div> <!-- .container -->
</body>
</html>
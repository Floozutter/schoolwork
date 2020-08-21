<?php
	function panic($errtype, $errno, $errmsg) {
		echo 'OOPSIE WOOPSIE!! Uwu We made a fucky wucky!! A wittle fucko boingo! The code monkeys at our headquarters are working VEWY HAWD to fix this!', '</br>';
		echo "$errtype $errno: $errmsg";
		exit;
	}
	
	function exists_GET($key) {
		return isset($_GET[$key]) && !empty($_GET[$key]);
	}
	
	function print_results($mysqli_result) {
		while ($row = $mysqli_result->fetch_assoc()) {
			echo '<tr>';
			echo 	'<td><a href="./details.php?dvd_title_id=' . $row['dvd_title_id'] . '">' . $row['title'] . '</a></td>';
			echo 	'<td>' . $row['release_date'] . '</td>';
			echo 	'<td>' . $row['genre'] . '</td>';
			echo 	'<td>' . $row['rating'] . '</td>';
			echo '</tr>';
		}
	}
	
	// Connect to database.
	$mysqli = new mysqli(
		'303.itpwebdev.com',
		'dchoi933_uwu',
		'0x4BE71AF2459CF83899EC9DC2CB60E22AC4B3047E0211034BBABE9D174C069DD6',
		'dchoi933_dvd_db'
	);
	if ($mysqli->connect_errno) { panic('MySQL Connection Error', $mysqli->connect_errno, $mysqli->connect_error); }

	// Build SQL query.
	$query = (
		' SELECT' .
		' 	dvd_titles.dvd_title_id,' .
		' 	dvd_titles.title,' .
		' 	dvd_titles.release_date,' .
		' 	genres.genre,' .
		' 	ratings.rating' .
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
		' WHERE 1 = 1'
	);
	// Example GET data:
	// ?title=alien&genre=19&rating=7&label=124&format=8&sound=3&award=any&release_date_from=2010-01-01&release_date_to=2020-06-26
	if (exists_GET('title')) {
		$query = $query . " AND (dvd_titles.title LIKE '%{$_GET['title']}%')";
	}
	if (exists_GET('genre')) {
		$query = $query . " AND (dvd_titles.genre_id = {$_GET['genre']})";
	}
	if (exists_GET('rating')) {
		$query = $query . " AND (dvd_titles.rating_id = {$_GET['rating']})";
	}
	if (exists_GET('label')) {
		$query = $query . " AND (dvd_titles.label_id = {$_GET['label']})";
	}
	if (exists_GET('format')) {
		$query = $query . " AND (dvd_titles.format_id = {$_GET['format']})";
	}
	if (exists_GET('sound')) {
		$query = $query . " AND (dvd_titles.sound_id = {$_GET['sound']})";
	}
	if (exists_GET('award')) {
		if ($_GET['award'] == 'yes') {
			$query = $query . " AND (dvd_titles.award IS NOT NULL)";
		} elseif ($_GET['award'] == 'no') {
			$query = $query . " AND (dvd_titles.award IS NULL)";
		}
	}
	if (exists_GET('release_date_from') && exists_GET('release_date_to')) {
		$query = $query . " AND (dvd_titles.release_date BETWEEN '{$_GET['release_date_from']}' AND '{$_GET['release_date_to']}')";
	}
	$query = $query . ';';
	
	// Get results.
	$results = $mysqli->query($query);
	if (!$results) { panic('MySQL Query Error', $mysqli->errno, $mysqli->error); }
	
	// Close connection.
	$mysqli->close();
?>
<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title>DVD Search Results</title>
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css">
</head>
<body>
	<ol class="breadcrumb">
		<li class="breadcrumb-item"><a href="search_form.php">Search</a></li>
		<li class="breadcrumb-item active">Results</li>
	</ol>
	<div class="container-fluid">
		<div class="row">
			<h1 class="col-12 mt-4">DVD Search Results</h1>
		</div> <!-- .row -->
	</div> <!-- .container-fluid -->
	<div class="container-fluid">
		<div class="row mb-4">
			<div class="col-12 mt-4">
				<a href="search_form.php" role="button" class="btn btn-primary">Back to Form</a>
			</div> <!-- .col -->
		</div> <!-- .row -->
		<div class="row">
			<div class="col-12">
				Showing <?=$results->num_rows?> result(s).
			</div> <!-- .col -->
			<div class="col-12">
				<table class="table table-hover table-responsive mt-4">
					<thead>
						<tr>
							<th>DVD Title</th>
							<th>Release Date</th>
							<th>Genre</th>
							<th>Rating</th>
						</tr>
					</thead>
					<tbody>
						<?php print_results($results); ?>
						
					</tbody>
				</table>
			</div> <!-- .col -->
		</div> <!-- .row -->
		<div class="row mt-4 mb-4">
			<div class="col-12">
				<a href="search_form.php" role="button" class="btn btn-primary">Back to Form</a>
			</div> <!-- .col -->
		</div> <!-- .row -->
	</div> <!-- .container-fluid -->
</body>
</html>
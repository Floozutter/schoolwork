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
			echo 	'<td>' . $row['date'] . '</td>';
			echo 	'<td>' . $row['day'] . '</td>';
			echo 	'<td>' . $row['home_team'] . '</td>';
			echo 	'<td>' . $row['away_team'] . '</td>';
			echo 	'<td>' . $row['venue'] . '</td>';
			echo '</tr>';
		}
	}
	
	// Connect to database.
	$mysqli = new mysqli(
		'303.itpwebdev.com',
		'dchoi933_uwu',
		'0x4BE71AF2459CF83899EC9DC2CB60E22AC4B3047E0211034BBABE9D174C069DD6',
		'dchoi933_football_schedule_db'
	);
	if ($mysqli->connect_errno) { panic('MySQL Connection Error', $mysqli->connect_errno, $mysqli->connect_error); }

	// Build SQL query.
	$query = (
		' SELECT' .
		' 	schedule.date,' .
		' 	days.day,' .
		' 	home_teams.team AS home_team,' .
		' 	away_teams.team AS away_team,' .
		' 	venues.venue' .
		' FROM' .
		' 	schedule' .
		' 	LEFT JOIN days' .
		' 		ON schedule.day_id = days.id' .
		' 	LEFT JOIN teams as home_teams' .
		' 		ON schedule.home_team_id = home_teams.id' .
		' 	LEFT JOIN teams as away_teams' .
		' 		ON schedule.away_team_id = away_teams.id' .
		' 	LEFT JOIN venues' .
		' 		ON schedule.venue_id = venues.id' .
		' WHERE 1 = 1'
	);
	if (exists_GET('team_id')) {
		$query = $query . " AND (schedule.home_team_id = {$_GET['team_id']} OR schedule.away_team_id = {$_GET['team_id']})";
	}
	if (exists_GET('venue_id')) {
		$query = $query . " AND (schedule.venue_id = {$_GET['venue_id']})";
	}
	if (exists_GET('day_id')) {
		$query = $query . " AND (schedule.day_id = {$_GET['day_id']})";
	}
	$query = $query . ';';
	
	// Get results.
	$results = $mysqli->query($query);
	if (!$results) { panic('MySQL Query Error', $mysqli->errno, $mysqli->error); }
	
	// Close connection.
	$mysqli->close();
?>
<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title>Football Database Search Results</title>
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css">
</head>
<body>
	<div class="container">
		<div class="row">
			<h1 class="col-12 mt-4">Football Schedule Search Results</h1>
		</div> <!-- .row -->
	</div> <!-- .container -->
	<div class="container">
		<div class="row mb-4">
			<div class="col-12 mt-4">
				<a href="search_form.php" role="button" class="btn btn-primary">Back to Form</a>
			</div> <!-- .col -->
		</div> <!-- .row -->
		<div class="row">
			<div class="col-12">
				<!-- TODO: Replace '1' with actual number of results -->
				Showing <?=$results->num_rows?> result(s).
			</div> <!-- .col -->
			<div class="col-12">
				<table class="table table-hover table-responsive mt-4">
					<thead>
						<tr>
							<th>Date</th>
							<th>Day</th>
							<th>Home Team</th>
							<th>Away Team</th>
							<th>Venue</th>
						</tr>
					</thead>
					<tbody>
						<!-- TODO: Loop through DB results and output them here. Modify or remove hard-coded output below. -->
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
	</div> <!-- .container -->
</body>
</html>
<?php
	function panic($errtype, $errno, $errmsg) {
		echo 'OOPSIE WOOPSIE!! Uwu We made a fucky wucky!! A wittle fucko boingo! The code monkeys at our headquarters are working VEWY HAWD to fix this!', '</br>';
		echo "$errtype $errno: $errmsg";
		exit;
	}
	
	function print_options($mysqli_result, $val_key, $text_key) {
		while ($row = $mysqli_result->fetch_assoc()) {
			echo '<option value="' . $row[$val_key] . '">';
			echo $row[$text_key];
			echo '</option>';
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
	
	// Query teams.
	$teams = $mysqli->query('SELECT * FROM teams;');
	if (!$teams) { panic('MySQL Query Error', $mysqli->errno, $mysqli->error); }
	
	// Query venues.
	$venues = $mysqli->query('SELECT * FROM venues;');
	if (!$venues) { panic('MySQL Query Error', $mysqli->errno, $mysqli->error); }

	// Query days.
	$days = $mysqli->query('SELECT * FROM days;');
	if (!$days) { panic('MySQL Query Error', $mysqli->errno, $mysqli->error); }
	
	// Close connection.
	$mysqli->close();
?>
<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title>Football Schedule Search Form</title>
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css">
</head>
<body>
	<div class="container">
		<div class="row">
			<h1 class="col-12 mt-4 mb-4">Football Schedule Search Form</h1>
		</div> <!-- .row -->
	</div> <!-- .container -->
	<div class="container">
		<form action="search_results.php" method="GET">
			<div class="form-group row">
				<label for="team" class="col-sm-3 col-form-label text-sm-right">Team:</label>
				<div class="col-sm-9">
					<select name="team_id" id="team" class="form-control">
						<option value="" selected>-- All --</option>
						<?php print_options($teams, 'id', 'team'); ?>

					</select>
				</div>
			</div> <!-- .form-group -->
			<div class="form-group row">
				<label for="venue" class="col-sm-3 col-form-label text-sm-right">Venue:</label>
				<div class="col-sm-9">
					<select name="venue_id" id="venue" class="form-control">
						<option value="" selected>-- All --</option>
						<?php print_options($venues, 'id', 'venue'); ?>

					</select>
				</div>
			</div> <!-- .form-group -->
			<div class="form-group row">
				<label for="day" class="col-sm-3 col-form-label text-sm-right">Day:</label>
				<div class="col-sm-9">
					<select name="day_id" id="day" class="form-control">
						<option value="" selected>-- All --</option>
						<?php print_options($days, 'id', 'day'); ?>

					</select>
				</div>
			</div> <!-- .form-group -->
			<div class="form-group row">
				<div class="col-sm-3"></div>
				<div class="col-sm-9 mt-2">
					<button type="submit" class="btn btn-primary">Search</button>
					<button type="reset" class="btn btn-light">Reset</button>
				</div>
			</div> <!-- .form-group -->
		</form>
	</div> <!-- .container -->
</body>
</html>
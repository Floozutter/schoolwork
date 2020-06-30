<?php
	function panic($errtype, $errno, $errmsg) {
		echo 'OOPSIE WOOPSIE!! Uwu We made a fucky wucky!! A wittle fucko boingo! The code monkeys at our headquarters are working VEWY HAWD to fix this!', '</br>';
		echo "$errtype $errno: $errmsg";
		exit;
	}
	
	function print_options($mysqli_result, $val_key, $text_key, $defaults) {
		while ($row = $mysqli_result->fetch_assoc()) {
			echo '<option value="' . $row[$val_key] . '"' . ($row[$val_key] == $defaults[$val_key] ? 'selected' : '') . '>';
			echo $row[$text_key];
			echo '</option>';
		}
	}		
	
	// Guarantee dvd_title_id.
	if (!isset($_GET['dvd_title_id']) || empty($_GET['dvd_title_id'])) { panic('Missing Data', '?', 'Missing dvd_title_id!'); }
	
	// Connect to database.
	$mysqli = new mysqli(
		'303.itpwebdev.com',
		'dchoi933_uwu',
		'0x4BE71AF2459CF83899EC9DC2CB60E22AC4B3047E0211034BBABE9D174C069DD6',
		'dchoi933_dvd_db'
	);
	if ($mysqli->connect_errno) { panic('MySQL Connection Error', $mysqli->connect_errno, $mysqli->connect_error); }

	// Query using dvd_title_id.
	$query = 'SELECT * FROM dvd_titles WHERE dvd_title_id = ' . $_GET['dvd_title_id'] . ';';
	$results = $mysqli->query($query);
	if (!$results) { panic('MySQL Query Error', $mysqli->errno, $mysqli->error); }
	
	// Get associative array for first match. (Hopefully, the only match.)
	$dvd = $results->fetch_assoc();
	if (!$dvd) { panic('Value Error', '?', 'DVD not found!'); }
	
	// Query genres.
	$genres = $mysqli->query('SELECT * FROM genres');
	if (!$genres) { panic('MySQL Query Error', $mysqli->errno, $mysqli->error); }
	
	// Query ratings.
	$ratings = $mysqli->query('SELECT * FROM ratings');
	if (!$ratings) { panic('MySQL Query Error', $mysqli->errno, $mysqli->error); }
	
	// Query labels.
	$labels = $mysqli->query('SELECT * FROM labels');
	if (!$labels) { panic('MySQL Query Error', $mysqli->errno, $mysqli->error); }
	
	// Query formats.
	$formats = $mysqli->query('SELECT * FROM formats');
	if (!$formats) { panic('MySQL Query Error', $mysqli->errno, $mysqli->error); }
	
	// Query sounds.
	$sounds = $mysqli->query('SELECT * FROM sounds');
	if (!$sounds) { panic('MySQL Query Error', $mysqli->errno, $mysqli->error); }
	
	// Close connection.
	$mysqli->close();
?>

<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title>Edit Form | DVD Database</title>
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css">
	<style>
		.form-check-label {
			padding-top: calc(.5rem - 1px * 2);
			padding-bottom: calc(.5rem - 1px * 2);
			margin-bottom: 0;
		}
	</style>
</head>
<body>
	<ol class="breadcrumb">
		<li class="breadcrumb-item"><a href="index.php">Home</a></li>
		<li class="breadcrumb-item"><a href="search_form.php">Search</a></li>
		<li class="breadcrumb-item"><a href="search_results.php">Results</a></li>
		<li class="breadcrumb-item"><a href="details.php?dvd_title_id=<?php echo $_GET['dvd_title_id']; ?>">Details</a></li>
		<li class="breadcrumb-item active">Edit</li>
	</ol>

	<div class="container">
		<div class="row">
			<h1 class="col-12 mt-4 mb-4">Edit a DVD</h1>
		</div> <!-- .row -->
	</div> <!-- .container -->

	<div class="container">
		<form action="edit_confirmation.php" method="POST">
			<input type="hidden" id="dvd_title_id-id" name="dvd_title_id" value="<?=$_GET['dvd_title_id']?>">
			<div class="form-group row">
				<label for="title-id" class="col-sm-3 col-form-label text-sm-right">Title: <span class="text-danger">*</span></label>
				<div class="col-sm-9">
					<input type="text" class="form-control" id="title-id" name="title" value="<?=$dvd['title']?>">
				</div>
			</div> <!-- .form-group -->

			<div class="form-group row">
				<label for="release-date-id" class="col-sm-3 col-form-label text-sm-right">Release Date:</label>
				<div class="col-sm-9">
					<input type="date" class="form-control" id="release-date-id" name="release_date" value="<?=$dvd['release_date']?>">
				</div>
			</div> <!-- .form-group -->

			<div class="form-group row">
				<label for="label-id" class="col-sm-3 col-form-label text-sm-right">Label:</label>
				<div class="col-sm-9">
					<select name="label_id" id="label-id" class="form-control">
						<option value="">-- Select One --</option>
						<?php print_options($labels, 'label_id', 'label', $dvd); ?>

					</select>
				</div>
			</div> <!-- .form-group -->

			<div class="form-group row">
				<label for="sound-id" class="col-sm-3 col-form-label text-sm-right">Sound:</label>
				<div class="col-sm-9">
					<select name="sound_id" id="sound-id" class="form-control">
						<option value="">-- Select One --</option>
						<?php print_options($sounds, 'sound_id', 'sound', $dvd); ?>

					</select>
				</div>
			</div> <!-- .form-group -->

			<div class="form-group row">
				<label for="genre-id" class="col-sm-3 col-form-label text-sm-right">Genre:</label>
				<div class="col-sm-9">
					<select name="genre_id" id="genre-id" class="form-control">
						<option value="">-- Select One --</option>
						<?php print_options($genres, 'genre_id', 'genre', $dvd); ?>

					</select>
				</div>
			</div> <!-- .form-group -->

			<div class="form-group row">
				<label for="rating-id" class="col-sm-3 col-form-label text-sm-right">Rating:</label>
				<div class="col-sm-9">
					<select name="rating_id" id="rating-id" class="form-control">
						<option value="">-- Select One --</option>
						<?php print_options($ratings, 'rating_id', 'rating', $dvd); ?>

					</select>
				</div>
			</div> <!-- .form-group -->

			<div class="form-group row">
				<label for="format-id" class="col-sm-3 col-form-label text-sm-right">Format:</label>
				<div class="col-sm-9">
					<select name="format_id" id="format-id" class="form-control">
						<option value="">-- Select One --</option>
						<?php print_options($formats, 'format_id', 'format', $dvd); ?>
						
					</select>
				</div>
			</div> <!-- .form-group -->

			<div class="form-group row">
				<label for="award-id" class="col-sm-3 col-form-label text-sm-right">Award:</label>
				<div class="col-sm-9">
					<textarea name="award" id="award-id" class="form-control"><?=$dvd['award']?></textarea>
				</div>
			</div> <!-- .form-group -->

			<div class="form-group row">
				<div class="ml-auto col-sm-9">
					<span class="text-danger font-italic">* Required</span>
				</div>
			</div> <!-- .form-group -->

			<div class="form-group row">
				<div class="col-sm-3"></div>
				<div class="col-sm-9 mt-2">
					<button type="submit" class="btn btn-primary">Submit</button>
					<button type="reset" class="btn btn-light">Reset</button>
				</div>
			</div> <!-- .form-group -->
		</form>
	</div> <!-- .container -->
</body>
</html>
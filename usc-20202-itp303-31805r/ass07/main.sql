-- Song database SELECTs. (4)

--- 1. Display albums that have the letters "on" somewhere in the album title.
--- Sort results in alphabetical order by album title.
SELECT *
FROM albums
WHERE title LIKE '%on%'
ORDER BY title;

--- 2. Same as (1.), but only show album title and artist name (no artist_id)
--- columns.
SELECT albums.title, artists.name
FROM albums
LEFT JOIN artists
	ON albums.artist_id = artists.artist_id
WHERE albums.title LIKE '%on%'
ORDER BY albums.title;

--- 3. Display tracks that have "AAC audio file" format. Only show track name
--- (alias: track_name), composer, media type name (alias: media_type), and
--- unit_price columns. Use media_type_id column for comparison instead of
--- media type name.
SELECT
	tracks.name AS track_name,
	tracks.composer,
	media_types.name AS media_type,
	tracks.unit_price
FROM tracks
LEFT JOIN media_types
	ON tracks.media_type_id = media_types.media_type_id
WHERE tracks.media_type_id = 5
ORDER BY track_name;

--- 4. Display R&B/Soul and Jazz tracks that have a composer (not NULL).
--- Sort results in reverse-alphabetical order by track name. Only show track
--- ID, track name (alias: track_name), composer, milliseconds, and genre name
--- (alias: genre_name) columns. Use genre_id column for comparison instead of
--- genre name.
SELECT
	tracks.track_id,
	tracks.name AS track_name,
	tracks.composer,
	tracks.milliseconds,
	genres.name AS genre_name
FROM tracks
LEFT JOIN genres
	ON tracks.genre_id = genres.genre_id
WHERE
	(tracks.composer IS NOT NULL) AND
	(tracks.genre_id = 2 OR tracks.genre_id = 14)
ORDER BY track_name DESC;
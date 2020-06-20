-- 1. Create a view mpeg_tracks that displays all tracks with MPEG audio
-- format. Display track name (track_name), artist name (artist_name),
-- composer, album title (album_title), and media type (media_type). Sort
-- results in alphabetical order by track name.
CREATE VIEW mpeg_tracks AS
SELECT
	tracks.name AS track_name,
	artists.name AS artist_name,
	tracks.composer,
	albums.title AS album_title,
	media_types.name AS media_type
FROM
	tracks
	LEFT JOIN albums
		ON tracks.album_id = albums.album_id
	LEFT JOIN artists
		ON albums.artist_id = artists.artist_id
	LEFT JOIN media_types
		ON tracks.media_type_id = media_types.media_type_id
WHERE tracks.media_type_id = 1
ORDER BY track_name;
SELECT * FROM mpeg_tracks;

-- 2. Add a track below to the database:
--   1. Track Title: The Ocean
--   2. Album: The Song Remains the Same (Disc 1)
--   3. Artist: Led Zeppelin
--   4. Media Type: MPEG audio file
--   5. Genre: Rock
--   6. Composer: John Bonham, John Paul Jones, Robert Plant
--   7. Milliseconds: 248000
--   8. Bytes: 7990000
--   9. Unit Price: 0.99

-- 3. Make the following changes to the track added above in (2.):
--   1. New Bytes: 8998765
--   2. New Unit Price: 1.99

-- 4. Delete track "20 Flight Rock" by BackBeat (artist) from the database.

-- 5. Display how many tracks there are for each album. Show album ID, album
-- title, (album_title), and track count (track_count).
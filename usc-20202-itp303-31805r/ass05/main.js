function ajax(callback, url) {
	const req = new XMLHttpRequest();
	req.onreadystatechange = function() {
		if (this.readyState == 4) {
			if (this.status == 200) {
				callback(this.responseText);
			} else {
				console.error("XHR error!");
			}
		}
	}
	req.open("GET", url);
	req.send();
}

function addResult(imgsrc, title, date, rating, votecount, overview) {
	console.log(title);
	// Create column.
	const col = document.createElement("div");
	col.classList.add("result", "col-6", "col-sm-4", "col-md-3", "my-10", "text-center");
	// Create and append image.
	const imgbox = document.createElement("div");
	imgbox.classList.add("imgbox");
	const img = document.createElement("img");
	img.classList.add("img-fluid", "rounded");
	img.setAttribute("src", imgsrc);
	img.setAttribute("alt", title);
	imgbox.appendChild(img);
	const hoverbox = document.createElement("div");
	hoverbox.classList.add("hoverbox");
	const hoverspan = document.createElement("span");
	hoverspan.classList.add("hoverspan");
	hoverspan.textContent = `Rating: ${rating}, Vote Count: ${votecount}`;
	const paragraph = document.createElement("p");
	paragraph.textContent = overview;
	hoverspan.appendChild(paragraph);
	hoverbox.appendChild(hoverspan);
	imgbox.appendChild(hoverbox);
	col.appendChild(imgbox);
	// Create and append title.
	const titleElement = document.createElement("h4");
	titleElement.textContent = title;
	col.appendChild(titleElement);
	// Create and append date.
	const dateElement = document.createElement("h5");
	dateElement.textContent = date;
	col.appendChild(dateElement);
	// Append column to row.
	const row = document.querySelector("#results .row");
	row.appendChild(col);
}

function clearResults() {
	const row = document.querySelector("#results .row");
	while (row.firstChild) { row.removeChild(row.lastChild); }
}

function displayResults(response) {
	const data = JSON.parse(response);
	clearResults();
	data.results.forEach(function (result) {
		let imgsrc = result.poster_path;
		if (imgsrc == null) {
			imgsrc = "https://via.placeholder.com/400x600"
		} else {
			imgsrc = `https://image.tmdb.org/t/p/w300${imgsrc}`
		}
		addResult(
			imgsrc,
			result.title,
			result.release_date,
			result.vote_average,
			result.vote_count,
			result.overview.substring(0, 200) + "..."
		);
	});
}

function searchListener(event) {
	const searchField = document.querySelector("#searchField");
	const query = searchField.value;
	if (!query) {
		ajax(
			displayResults,
			`https://api.themoviedb.org/3/movie/now_playing?language=en-US&page=1&api_key=${APIKEY}`
		);
		return;
	}
	ajax(
		displayResults,
		`https://api.themoviedb.org/3/search/movie?language=en-US&page=1&query=${query}&api_key=${APIKEY}`
	);
}

function startup() {
	if (typeof APIKEY === "undefined") {
		console.error("Failed to load TMDb API key!");
	}
	
	const searchButton = document.querySelector("#searchButton");
	searchButton.addEventListener("click", searchListener);
	
	searchListener();
}

window.addEventListener("load", startup);
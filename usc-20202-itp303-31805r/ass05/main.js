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

function addResult(title, date, imgsrc) {
	// Create column.
	const col = document.createElement("div");
	col.classList.add("col-6", "col-sm-4", "col-md-3", "text-center");
	// Create and append image.
	const img = document.createElement("img");
	img.classList.add("img-fluid", "rounded");
	img.setAttribute("src", imgsrc);
	img.setAttribute("alt", title);
	col.appendChild(img);
	// Create and append title.
	const titleElement = document.createElement("h2");
	titleElement.textContent = title;
	col.appendChild(titleElement);
	// Create and append date.
	const dateElement = document.createElement("h3");
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
		addResult(
			result.title,
			result.release_data,
			`https://image.tmdb.org/t/p/w300${result.poster_path}`
		);
	});
}

function startup() {
	if (typeof APIKEY === "undefined") {
		console.error("Failed to load TMDb API key!");
	}
	
	ajax(displayResults, `https://api.themoviedb.org/3/movie/now_playing?language=en-US&page=1&api_key=${APIKEY}`);
}

window.addEventListener("load", startup);
function addResult(title, date, imgsrc) {
	// Create column.
	let col = document.createElement("div");
	col.classList.add("col-6", "col-sm-4", "col-md-3", "text-center");
	// Create and append image.
	let img = document.createElement("img");
	img.classList.add("img-fluid", "rounded");
	img.setAttribute("src", imgsrc);
	img.setAttribute("alt", title);
	col.appendChild(img);
	// Create and append title.
	let titleElement = document.createElement("h2");
	titleElement.textContent = title;
	col.appendChild(titleElement);
	// Create and append date.
	let dateElement = document.createElement("h3");
	dateElement.textContent = date;
	col.appendChild(dateElement);
	// Append column to row.
	let row = document.querySelector("#results .row");
	row.appendChild(col);
}

function clearResults() {
	let row = document.querySelector("#results .row");
	while (row.firstChild) { row.removeChild(row.lastChild); }
}

function startup() {
	if (typeof APIKEY === "undefined") {
		console.error("Failed to load TMDb API key!");
	}
	
	for (let i = 0; i < 2; i++) {
		addResult("GLaDOS", "????-??-??", "https://upload.wikimedia.org/wikipedia/en/b/bf/Glados.png");
	}
	clearResults();
	for (let i = 0; i < 5; i++) {
		addResult("GLaDOS", "????-??-??", "https://upload.wikimedia.org/wikipedia/en/b/bf/Glados.png");
	}
}

window.addEventListener("load", startup);
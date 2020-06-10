function setWeather(data) {
	const obs = data.data[0];  // First returned observation.
	$("#weather-report").text(
		`${obs.temp}\u2109, feels like ${obs.app_temp}\u2109`
	);
}

function addItem(text) {
	const item = $("<li></li>");
	item.append(
		$("<span></span>")
			.addClass("close")
			.text("X")
			.click(function() {
				$(this).closest("li").remove();
			})
	);
	item.append($("<span></span>").text(" - " + text));
	$("#todo ul").append(item);
}

function startup() {
	// Get weather from API.
	$.get(
		`https://api.weatherbit.io/v2.0/current?city=Los Angeles,CA&units=I&key=${APIKEY}`,
		setWeather
	);
	
	// Add listener to To-Do List button.
	$("#todo-button").click(function() {
		addItem($("#todo-field").val());
	});
	
	// Add example To-Do List items.
	addItem("Study for ITP 303 midterm");
	addItem("Buy USC shirt from bookstore");
	addItem("Go to Nayeon's office hours");
}

$(document).ready(startup);
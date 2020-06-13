function setWeather(city) {
	console.log(city);
	$.get(
		`https://api.weatherbit.io/v2.0/current?city=${city}&units=I&key=${APIKEY}`,
		function(data) {
			const obs = data.data[0];  // First returned observation.
			$("#weather-report").text(
				`${obs.temp}\u00B0F, feels like ${obs.app_temp}\u00B0F`
			);
		}
	)
}
function addItem(text) {
	const item = $("<li></li>");
	item.append(
		$("<span></span>")
			.addClass("close")
			.text("\u2B1C")
			.click(function() {
				$(this).closest("li").fadeOut(200, function() {
					$(this).remove();
				});
			})
	);
	item.click(function() {
		$(this).toggleClass("crossed");
	});
	item.append($("<span></span>").text(" " + text));
	$("#todo ul").append(item);
}

function startup() {
	// Add listeners.
	const addingListener = function() { addItem($("#todo-field").val()); }
	$("#todo-button").click(addingListener);
	$("#todo-field").on("keypress", function(e) {
		if (e.which === 13) { addingListener(); }
	});
	$("#city").change(function() {
		setWeather($(this).options[$(this).selectedIndex].value);
	});
	
	// Set weather using default city selection.
	setWeather("Los Angeles,CA");
	
	// Add example To-Do List items.
	addItem("Study for ITP 303 midterm");
	addItem("Buy USC shirt from bookstore");
	addItem("Go to Nayeon's office hours");
}

$(document).ready(startup);
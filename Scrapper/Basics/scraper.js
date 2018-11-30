// Declare needed packages
var request = require('request');
var cheerio = require('cheerio');

var titles = [];

url = 'http://www.timesoccer.com/football-highlights';

// The structure of our request call
// The first parameter is our URL
// The callback function takes 3 parameters, an error, response status code and the html
request(url, function(error,res, body){
	//Safety check for no errors
	if(!error){
		// Next, we'll utilize the cheerio library on the returned html which will essentially give us jQuery functionality
		var $ = cheerio.load(body);
		// We'll use the unique header class as a starting point.
		$("entry-title td-module-title", "wpb_wrapper").each(function(){
			// Let's store the data we filter into a variable so we can easily see what's going on.
			var data = $(this).children().last().text();
			console.log("1");
			console.log(data);
			titles.push(data);
		})
		
	}
})
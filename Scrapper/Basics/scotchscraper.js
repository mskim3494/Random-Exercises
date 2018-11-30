// Declare needed packages
var express = require('express');
var fs = require('fs');
var request = require('request');
var cheerio = require('cheerio');
var app = express();

// All the webscraping happens here
app.get('/scrape', function(req,res){
	// find URL
	url = 'http://www.imdb.com/title/tt1229340/';
	
	// The structure of our request call
    // The first parameter is our URL
    // The callback function takes 3 parameters, an error, response status code and the html
	request(url, function(error,response, html){
		//Safety check for no errors
		if(!error){
			// Next, we'll utilize the cheerio library on the returned html which will essentially give us jQuery functionality
			var $ = cheerio.load(html);
			// Define the variables we're going to capture
			var title, release, rating;
			var json = { title : "", release : "", rating : ""};
			
			// We'll use the unique header class as a starting point.
			$('.header').filter(function(){
				// Let's store the data we filter into a variable so we can easily see what's going on.
				var data = $(this);
				// Title rests within the first child element of the header tag. 
				// Utilizing jQuery we can easily navigate and get the text by writing the following code:
				title = data.children().first().text();
				// Store title in the json object
				json.title = title;
				// Do this for the other variables
				release = data.children().last().children().text();
				json.release = release;
			})
			// Since the rating is in a different section of the DOM, we'll have to write a new jQuery filter to extract this information.
			$('.star-box-giga-star').filter(function(){
				var data = $(this);
				rating = data.text();
				json.rating = rating;
			})
		}
		
		fs.writeFile('output.json', JSON.stringify(json,null, 4), function(err){
			console.log('File successfully written! - check for output.json file');
		})
		res.send('Check your console!')
	})
})

app.listen('8081')
console.log('Magic happens on port 8081');
exports = module.exports = app;
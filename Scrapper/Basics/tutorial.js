var request = require('request');

request('http://www.google.com', fun);

var fun = function(error, response, body){
	console.log('error:', error); // Print the error if one occurred
  console.log('statusCode:', response && response.statusCode); // Print the response status code if a response was received
  console.log('body:', body); // Print the HTML for the Google homepage.
}

adding(1,2, add3);
var adding = function(one, two, func){
	return one + two;
}

var add3 = function(one){
	return one + 3;
}
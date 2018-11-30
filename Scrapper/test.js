var request = require('request');


// up to v3 is the access point to the googleapi, 
// then are the parameters devided by &, 
// at the end the key is the api key that you get for your project
var url = 'https://www.googleapis.com/youtube/v3/search?part=snippet&q=nodejs&type=video&key=AIzaSyA2wjyrreUvfcgrtejt649orBa-c5zIHK0';
request(url, function(error, res, body){
    if(!error){
        var data = JSON.parse(body);
        // need to look at the JSON closely... it's understanding classes
        for (var i=0; i < data.items.length; i++){
            console.log(data.items[i].snippet.title);
        }
    }
});
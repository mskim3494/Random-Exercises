// Your use of the YouTube API must comply with the Terms of Service:
// https://developers.google.com/youtube/terms

var gapi = require('gapi');

// Helper function to display JavaScript value on HTML page.
function showResponse(response) {
  var responseString = JSON.stringify(response, '', 2);
  document.getElementById('response').innerHTML += responseString;
}

// Called automatically when JavaScript client library is loaded.
function onClientLoad() {
  gapi.client.load('youtube', 'v3', onYouTubeApiLoad);
}

// Called automatically when YouTube API interface is loaded (see line 9).
function onYouTubeApiLoad() {
  // This API key is intended for use only in this lesson.
  // See https://goo.gl/PdPA1 to get a key for your own applications.
  gapi.client.setApiKey('AIzaSyA2wjyrreUvfcgrtejt649orBa-c5zIHK0');

  search();
}

function search() {
  // Use the JavaScript client library to create a search.list() API call.
  var request = gapi.client.youtube.search.list({
      part: 'snippet',
      q: 'nodejs',
  });
  
  // Send the request to the API server,
  // and invoke onSearchRepsonse() with the response.
  request.execute(onSearchResponse);
}

// Called automatically with the response of the YouTube API request.
function onSearchResponse(response) {
  showResponse(response);
  console.log(response);
}

// https://www.googleapis.com/auth/youtube/v3/search?part=snippet&q=nodejs&type=video&key=AIzaSyA2wjyrreUvfcgrtejt649orBa-c5zIHK0
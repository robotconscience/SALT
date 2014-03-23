var tembooAuth = require("./auth/auth_temboo").tAuth
	, tsession = require("temboo/core/temboosession")
	, session = new tsession.TembooSession(tembooAuth.user, tembooAuth.app, tembooAuth.key)
	, Spacebrew = require("./Spacebrew.js").Spacebrew
  	, request = require('request')
  	, fs = require('fs');

// SPACEBREW OBJECT
var sb;

/** Map of current results */
// TODO: we should save this to disk in case of crash
var currentResults = {};

var YouTube = require("temboo/Library/YouTube/Search");

var searchChoreo = new YouTube.ListSearchResults(session);

// Instantiate and populate the input set for the choreo
var searchInputs = searchChoreo.newInputSet();

// Set credential to use for execution
searchInputs.setCredential("youtube");

var currentTerm = ";"

/**
 * Calls YouTube search via Temboo for a specified term
 * @param  {String} term what to search for!
 * @param  {Function} resultHandler Function to be called on results. 
 *                                  Make sure to bind your scope if using 'this!!!'
 * @param 	{Function} errorHandler Function to be called on error
 */
var searchYouTube = function ( term, resultHandler, errorHandler ){
	searchInputs.set_Query(term);
	searchInputs.set_MaxResults("50"); // 50 is the max!
	searchInputs.set_Order("date");

	currentTerm = term;

	// Run the choreo, specifying success and error callback handlers
	searchChoreo.execute(
	    searchInputs,
	    resultHandler,
	    errorHandler
	);
}


var onSearchResults = function(results){
	//console.log(results.get_Response());
	//
	// send raw results
	sb.send("results", "string", results.get_Response());
	
	var resultObj = JSON.parse(results.get_Response());

	try {
		// right now, only saving latest!
		fs.writeFile("results.json", JSON.stringify(resultObj, null, 4), function(err) {
		    if(err) {
		      console.log(err);
		    } else {
		    }
		}); 
	} catch (e){
		console.log( e );
	}

	// loop through 'items' array

	var numNewResults = 0;

	for ( var i=0; i<resultObj["items"].length; i++){
		// check for result in map
		if ( resultObj.items[i].id.videoId in currentResults){
			// result exists. silencio
		} else {
			// add to map, increment new results
			numNewResults++;
			currentResults[resultObj.items[i].id.videoId] = resultObj.items[i];
		}	
	}
	console.log("New YouTube videos for "+currentTerm+" : " +numNewResults);
	sb.send("new_results", "range", numNewResults);
}

var onSearchError = function (error){
	console.log(error.type); 
	console.log(error.message);
}

/** */
var main = function( host ) {
	sb = new Spacebrew.Client(host, "youtube_searcher", "");
	sb.addPublish("results", "string", "" );
	sb.addPublish("new_results", "range", "" );
	sb.addSubscribe("search", "string");
	sb.connect();

	sb.onStringMessage = function(name, value){
		if ( name == "search"){
			searchYouTube(value, onSearchResults, onSearchError);
		}
	}

	// set interval to search every 2 minutes 
	setInterval(
		function(){
			searchYouTube("water", onSearchResults, onSearchError);
		}, 2 * 60 * 1000 );

	searchYouTube("water", onSearchResults, onSearchError);
}

// process command line args
// usage:
// node app.js spacebrewserver
// ex: node app.js localhost
if ( process.argv.length >= 2 ){
	process.argv.forEach(function (val, index, array) {
		//index 2 will be our host
		// 0 = node, 1 = app.js
		if (index == 2 ){
			main(val);
		}
	});

} else {
	/** Run the app with the spacebrew sandbox */
	main("sandbox.spacebrew.cc");

}
#!/usr/bin/env node
var fs = require('fs');
var addon = require('./build/Release/addon');
var gzconnection = new addon.GZNode();
var materialScriptsJson = {};

if (process.argv.length < 2)
{
	console.log(' Missing argument: material path.');
}
else
{
	materialScriptsJson = gzconnection.loadMaterialScripts(process.argv[2]);

	fs.writeFile("material.json", materialScriptsJson , function(err) {
	    if(err) {
	        return console.log(err);
	    }

	    console.log("material json file was saved!");
	}); 
}


var bubbles = require('../src/bubbles.js');

/*
 * GET home page.
 */
exports.index = function(req, res){
	var random = Math.floor((Math.random()*bubbles.list.total)+0);
	console.log(random);

	if (random == bubbles.list.incom) {
		console.log('incom');
	} else if (random == bubbles.list.twitter) {
		console.log('twitter');
	} else if (random == bubbles.list.asta) {
		console.log('asta');
	};

  res.render('index', { title: 'Express' });
};



exports.incom = function(req, res){
  res.render('incom', { title: 'incom'});
};

exports.asta = function(req, res){
  res.render('asta', { title: 'asta'});
};

exports.twitter = function(req, res){
  res.render('twitter', { title: 'twitter'});
};

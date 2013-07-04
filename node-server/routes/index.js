
var utils = require('../src/utils.js');
var bubbles = require('../src/bubbles.js');
var incom = require('../src/incom.js');
var asta = require('../src/asta.js');
var twitter = require('../src/twitter.js');
var zitate = require('../src/zitate.js');
var names = require('../src/names.js');


/*
----------------------------------------------------------------------
template render stuff
----------------------------------------------------------------------
*/

function incomRender(res) {
  res.render('incom', incom.getData());
}

function astaRender(res) {
  res.render('asta', asta.getData());
}

function twitterRender(res) {
  res.render('twitter', twitter.getData());
}

function namesRender(res) {
  res.render('names', names.getData());
  console.log(names.getData().type);
}

function zitateRender(res) {
  res.render('zitate', zitate.getData());
}


/*
----------------------------------------------------------------------
response stuff
----------------------------------------------------------------------
*/

exports.index = function(req, res){
  var random = utils.getRandom(0, bubbles.types.total);
  console.log(random);

  if (random == bubbles.types.incom) {
    incomRender(res);
  } else if (random == bubbles.types.twitter) {
    twitterRender(res);
  } else if (random == bubbles.types.asta) {
    astaRender(res);
  } else if (random == bubbles.types.names) {
    namesRender(res);
  } else if (random == bubbles.types.zitate) {
    zitateRender(res);
  }
};

exports.incom = function(req, res){
  incomRender(res);
};

exports.asta = function(req, res){
  astaRender(res);
};

exports.twitter = function(req, res){
  twitterRender(res);
};

exports.names = function(req, res){
  namesRender(res);
};

exports.zitate = function(req, res){
  zitateRender(res);
};

var utils = require('../src/utils.js');
var bubbles = require('../src/bubbles.js');
var incom = require('../src/incom.js');
var asta = require('../src/asta.js');
var twitter = require('../src/twitter.js');
var zitate = require('../src/zitate.js');


/*
----------------------------------------------------------------------
template render stuff
----------------------------------------------------------------------
*/

function incomRender(res) {
  data = incom.getData();

  res.render('incom',
    {
      text: data.text,
      datetime: data.datetime
    }
  );
}

function astaRender(res) {
  data = asta.getData();

  res.render('asta',
    {
      text: data.text,
      datetime: data.datetime
    }
  );
}

function twitterRender(res) {
  data = twitter.getData();

  res.render('twitter',
    {
      text: data.text,
      author: data.author,
      time: data.time
    }
  );
}

function namesRender(res) {
  data = zitate.getData();

  res.render('names', {
      type: data.type,
      text: data.text
    }
  );
}

function zitateRender(res) {
  data = zitate.getData();

  res.render('zitate', {
      type: data.type,
      text: data.text
    }
  );
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

var utils = require('../src/utils.js');
var bubbles = require('../src/bubbles.js');
var incom = require('../src/incom.js');
var asta = require('../src/asta.js');


/*
----------------------------------------------------------------------
template render stuff
----------------------------------------------------------------------
*/

function incomRender(res) {
  data = incom.getData();

  res.render('incom',
    {
      title: data.text,
      datetime: data.datetime
    }
  );
}

function astaRender(res) {
  data = asta.getData();

  res.render('asta',
    {
      title: data.text,
      datetime: data.datetime
    }
  );
}

function twitterRender(res) {
  data = '';

  res.render('twitter',
    {
      title: data.text,
      datetime: data.datetime
    }
  );
}

function namesRender(res) {
  data = '';

  res.render('names',
    {
      title: data.text,
      datetime: data.datetime
    }
  );
}

function zitateRender(res) {
  data = '';

  res.render('zitate',
    {
      title: data.text,
      datetime: data.datetime
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
    astaRender(res);
  } else if (random == bubbles.types.asta) {
    twitterRender(res);
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
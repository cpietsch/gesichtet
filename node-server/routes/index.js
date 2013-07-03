
var bubbles = require('../src/bubbles.js');

/*
 * GET home page.
 */
exports.index = function(req, res){
  var random = Math.floor((Math.random()*bubbles.types.total)+0);
  console.log(random);

  if (random == bubbles.types.incom) {
    res.render('incom', { title: 'incom' });
  } else if (random == bubbles.types.twitter) {
    res.render('asta', { title: 'asta' });
  } else if (random == bubbles.types.asta) {
    res.render('twitter', { title: 'twitter' });
  }

};



exports.incom = function(req, res){
  res.render('incom',
    {
      title: 'Wie jetzt, keine Werkschau? Ist ja scheiße.',
      datetime: 'vor 15 Minuten, Kein Kommentar'
    }
  );
};

exports.asta = function(req, res){
  res.render('asta',
    {
      title: 'asta'
    }
  );
};

exports.twitter = function(req, res){
  res.render('twitter',
    {
      title: 'twitter'
    }
  );
};

exports.names = function(req, res){
  res.render('names',
    {
      title: 'names'
    }
  );
};

exports.zitate = function(req, res){
  res.render('zitate',
    {
      title: 'zitate'
    }
  );
};
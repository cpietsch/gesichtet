/**
 * Names bubble
 */

var utils = require('./utils.js');
var data = require('../../data/names.json');


exports.getData = function getData() {
  // die totale menge im array
  var totalMessages = data.zitate.length;

  // ein random wert für die abfrage aus dem array
  var random = utils.getRandom(0, totalMessages-1);
  //console.log(random);

  return data.messages[random];
};

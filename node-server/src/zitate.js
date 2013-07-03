/**
 * Zitate bubble
 */

var utils = require('./utils.js');
var data = require('../../data/zitate.json');


exports.getData = function getData() {
  // die totale menge im array
  var totalMessages = data.zitate.length;

  // ein random wert für die abfrage aus dem array
  var random = utils.getRandom(0, totalMessages-1);
  //console.log(random);

  // object welces returnt werden soll
  var tmpData = {
    type: data.zitate[random].type,
    text: data.zitate[random].text
  };
  //console.log(tmpData.type);
  //console.log(tmpData.text);

  return tmpData;
};

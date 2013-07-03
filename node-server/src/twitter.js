/**
 * Twitter bubble
 */

var utils = require('./utils.js');
var data = require('../../data/twitter.json');


exports.getData = function getData() {
  // die totale menge im array
  var totalMessages = data.messages.length;

  // ein random wert für die abfrage aus dem array
  var random = utils.getRandom(0, totalMessages-1);
  //console.log(random);

  // object welces returnt werden soll
  var tmpData = {
    author: data.messages[random].author,
    text: data.messages[random].text,
    time: data.messages[random].time
  };
  console.log(tmpData.text);
  console.log(tmpData.time);
  console.log(tmpData.author);

  return tmpData;
};

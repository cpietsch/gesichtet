
/**
 * return a random integer
 */
exports.getRandom = function getRandom(start, stop) {
  var random = Math.floor((Math.random()*stop)+start);
  //console.log(random);

  return random;
 }

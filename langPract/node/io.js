
var fs = require('fs');
var array = fs.readFileSync(process.argv[2]).toString().split('\n');
console.log(array.length-1);


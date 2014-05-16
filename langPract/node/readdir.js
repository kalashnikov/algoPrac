
var list = [];
var fs   = require('fs');
var path = require('path');
fs.readdir(process.argv[2], function (err, data) {
      if (err) throw err;
      data.forEach( function(f) {
          if (path.extname(f||"").split('.').pop()==process.argv[3]) {
              console.log(f);
          }
      });
});

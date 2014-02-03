module.exports = function rdir (dir, ext, callback) {

    var list = [];
    var fs   = require('fs');
    var path = require('path');
    fs.readdir(dir, function (err, data) {
        if (err)
        return callback(err) // early return

        // Using filter for array data filtering 
        data = data.filter(function (file) {
            return path.extname(file) === '.' + ext
        })


        // Normal forEach method to traverse array for filtering
//        data.forEach( function(f) {
//            if (path.extname(f||"").split('.').pop()==ext) {
//                list.push(f);
//            }
//        });

        // all went well, call callback with `null` for the error argument
        callback(null, data)
    })
}


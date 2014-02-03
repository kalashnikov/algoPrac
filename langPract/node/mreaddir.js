var my = require('./mrd');

my( process.argv[2], process.argv[3], function(err,data){
    data.forEach( function(f) {
        console.log(f);
    });
});

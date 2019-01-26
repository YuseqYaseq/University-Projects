const async = require('async');

function printAsync(s, cb) {
   var delay = Math.floor((Math.random()*1000)+500);
   setTimeout(function() {
       console.log(s);
       if (cb) cb();
   }, delay);
}


function myFirstFunction(callback) {
    printAsync("1", callback);
}
function mySecondFunction(callback) {
    printAsync("2", callback);
}
function myLastFunction(callback) {
    printAsync("3", callback);
}

function loop(n) {
    if(n > 0) {
        async.waterfall([
            myFirstFunction,
            mySecondFunction,
            myLastFunction,
        ], function (err, result) {
            loop(n-1);
        });
    } else {
        console.log("done!");
    }
}

loop(3);

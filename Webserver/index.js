var http = require('http');
var fs = require('fs');

var file = fs.readFile('test.txt', function(err,data){
  if (err){
    throw err;
  }
  else {
    http.createServer(function(req,res) {
      res.write(data);
      res.end();
    }).listen(8080);
  }
});

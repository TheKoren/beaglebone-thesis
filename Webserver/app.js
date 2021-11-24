const express = require('express')
const app = express()
const port = 9000

app.use(express.static('.'))

app.get('/', function(req, res) {
  res.sendFile(__dirname + '/index.html')
})
app.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`)
})

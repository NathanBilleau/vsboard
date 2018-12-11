const express = require('express')
const bodyParser = require('body-parser')
const term = require('child_process').exec

const app = express()

const port = 5555

app.use(express.static('front'))

app.use(bodyParser.json())
app.use(bodyParser.urlencoded({
  extended: true
}))



app.get('/', (req, res) => {
  res.renderFile('front/index.html')
})



app.post('/text', (req, res) => {
  let text = req.body.text
  console.log(text)

  // term('')
})



.listen(port, () => {
  console.log('http://localhost:' + port)
})

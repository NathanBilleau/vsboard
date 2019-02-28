
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
  var text = req.body.text
  text += '\n'
  console.log(text)

  term('sudo ./message ttyUSB0 9600 $ ' + text + '')
})



.listen(port, () => {
  console.log('http://localhost:' + port)
})

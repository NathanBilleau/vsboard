var button = document.getElementById('submitButton')
var textSubmited = document.getElementById('textSubmited')


button.onclick = () => {
  var text = document.getElementById('inputText').value
  window.axios.post('/text', {text: text})

  textSubmited.innerHTML = text
  document.getElementById('inputText').value = ''
}

var button = document.getElementById('submitButton')

button.onclick = () => {
  var text = document.getElementById('inputText').value
  window.axios.post('/text', {text: text})
}

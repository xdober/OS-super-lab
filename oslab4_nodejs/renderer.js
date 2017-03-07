const ipcRenderer = require('electron').ipcRenderer;
console.log(ipcRenderer.sendSync('synchronous-message', 'ping')); // prints "pong"

ipcRenderer.on('asynchronous-reply', function(event, arg) {
  console.log(arg); // prints "pong"
  document.getElementById("cpuusage").innerHTML = arg;
});
ipcRenderer.send('asynchronous-message', 'ping2');

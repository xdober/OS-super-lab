var memFs = require('fs');
function createMemValue() {
  var oTemp      = new Object;
  oTemp.total    = 0;
  oTemp.avalable = 0;
  oTemp.usage    = 0;
  return oTemp;
}
var memValue  = createMemValue();
function memStringToValue(memValue, datain) {
    var arrStringMem = datain.split("\n");
    var memStringTotal = arrStringMem[0].split(/ +/);
    var memStringAvaib = arrStringMem[2].split(/ +/);
    memValue.total = Number(memStringTotal[1]);
    memValue.avalable = Number(memStringAvaib[1]);
    memValue.usage = ((memValue.total - memValue.avalable)/memValue.total)*100.0;
    memValue.usage = memValue.usage.toFixed(3);
}
function calMem() {
    setInterval(function(){
        memFs.readFile('/proc/meminfo', "utf-8", (err, data) => {
            memStringToValue(memValue, data);
        });
        document.getElementById("memusage").innerHTML = memValue.usage;
        document.getElementById("memtotal").innerHTML = memValue.total;
        document.getElementById("memava").innerHTML = memValue.avalable;
    },1000);
}

calMem();

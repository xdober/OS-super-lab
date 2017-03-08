
//calculate CPU usage
var cpuFs = require('fs');
function createCpuValue() {
  var oTemp    = new Object;
  oTemp.user   = 0;
  oTemp.nice   = 0;
  oTemp.system = 0;
  oTemp.idle   = 0;
  oTemp.total  = 0;
  return oTemp;
}
var cpuValue=[], cpuusage = 0;
cpuValue[0] = createCpuValue();
cpuValue[1] = createCpuValue();
function cpuStringToValue(cpuValue, datain) {
    var arrStringCPU = datain.split(/ +/);
    cpuValue.user   = Number(arrStringCPU[1]);
    cpuValue.nice   = Number(arrStringCPU[2]);
    cpuValue.system = Number(arrStringCPU[3]);
    cpuValue.idle   = Number(arrStringCPU[4]);
    cpuValue.total  = cpuValue.user + cpuValue.nice + cpuValue.system + cpuValue.idle;
}
function calCPU() {
    var i = 0;
    setInterval(function(){
        cpuFs.readFile('/proc/stat', "utf-8", (err, data) => {
            cpuStringToValue(cpuValue[i], data);
            i = i + 1;
            i = i%2;
        });
        cpuusage = (cpuValue[1].total != cpuValue[0].total) ? (1 - (cpuValue[1].idle - cpuValue[0].idle)/(cpuValue[1].total - cpuValue[0].total))*100.0 : 0;
        document.getElementById("cpuusage").innerHTML = cpuusage;
    },1000);

}
//calculate CPU usage end
calCPU();

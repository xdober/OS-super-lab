var cpufs = require('fs');
function cpuStringToValueInfo(datain) {
    var arrStringCPU = datain.split("\n");
    var arrinfo = arrStringCPU[4].split(":");
    var cpuValueInfo = arrinfo[1];
    return cpuValueInfo;
}
var cpuValueInfo;
function calCPUinfo() {
    setInterval(function(){
        cpufs.readFile('/proc/cpuinfo', "utf-8", (err, data) => {
            cpuValueInfo = cpuStringToValueInfo(data);
        });
        document.getElementById("cpuinfo").innerHTML = cpuValueInfo;
    },1000);
}
calCPUinfo();

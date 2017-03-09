var prgFs = require('fs');
var count = 0, prgValueInfo = [], sortflag = 1;
function creatPrgObj() {
    var oTemp = new Object;
    oTemp.pName = "name";
    oTemp.mem = 0;
    oTemp.pid = 0;
    oTemp.statu = "S";
    return oTemp;
}
function prgToValue(datain) {//info from file to an object
    var arrStringPrg = datain.split(/ +/);
    var prgValue = creatPrgObj();
    prgValue.pName = arrStringPrg[1];
    prgValue.pName = prgValue.pName.slice(1,-1);//delete brackets
    prgValue.pid = Number(arrStringPrg[0]);
    prgValue.mem = Number(arrStringPrg[22])/1024;
    prgValue.statu = arrStringPrg[2];
    return prgValue;
}
function opendir() {
    const nameArry = prgFs.readdirSync('/proc/');
    return nameArry;
}
function openfile(nameArry) {
     var reg = new RegExp("^[0-9]*$");
     nameArry.forEach(function(itemName, index) {
         if (reg.test(itemName)) {
            const fileContent = prgFs.readFileSync('/proc/'+itemName+'/stat', "utf-8");
            prgValueInfo[count] = prgToValue(fileContent);
            count += 1;
         }
     });
}

function calPrg() {
    var nameArry = []
    setInterval(function() {
        nameArry.splice(0,nameArry.length);
        nameArry = opendir();
        count = 0;
        prgValueInfo.splice(0,prgValueInfo.length);
        openfile(nameArry);
        prgValueInfo.sort(by(sortflag?"mem":"pid"));
        updateDOM();
    }, 1000);
}
function updateDOM() {
    $("div").remove(".new");
    prgValueInfo.forEach(function(item,index) {
        //var table = document.getElementById("prgInfoTable");
        var textMem = $('<div class = "col-xs-3 new"></div>').text(item.mem);
        var textStatus = $('<div class = "col-xs-3 new"></div>').text(item.statu);
        var textPID = $('<div class = "col-xs-3 new"></div>').text(item.pid);
        var textName = $('<div class = "col-xs-3 new"></div>').text(item.pName);
        //var prgItem = $('<div clsss = "tab-row"></div>').text(textName, textPID, textStatus, textMem);
        $("#tab-title").after(textMem);
        $("#tab-title").after(textStatus);
        $("#tab-title").after(textPID);
        $("#tab-title").after(textName);
    });
    var ppiidd = document.getElementById("pid");
    ppiidd.onclick = function() {
        sortflag = 0;
    }
    var mmeemm = document.getElementById("mem");
    mmeemm.onclick = function() {
        sortflag = 1;
    }
}
calPrg();
var by = function(name){
    return function(o, p){
        var a, b;
        if (typeof o === "object" && typeof p === "object" && o && p) {
            a = o[name];
            b = p[name];
            if (a === b) {
                return 0;
            }
            if (typeof a === typeof b) {
                return a < b ? -1 : 1;
            }
            return typeof a < typeof b ? -1 : 1;
        }
        else {
            throw ("error");
        }
    }
}

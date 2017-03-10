var prgFs = require('fs');
var count = 0, prgValueInfo = [], sortSelect = "mem", UorD = 0, UorD1 = 0, UorD2 = 0, UorD3 = 0, UorD4 = 0;
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

var by = function(name, upordown){
    return function(o, p){
        var a, b;
        if (typeof o === "object" && typeof p === "object" && o && p) {
            a = o[name];
            b = p[name];
            if (a === b) {
                return 0;
            }
            if (typeof a === typeof b) {
                if (upordown == 0) {
                    return a < b ? -1 : 1;
                } else {
                    return a > b ? -1 : 1;
                }
            }
            if (upordown == 0) {
                return typeof a < typeof b ? -1 : 1;
            }
            else {
                return typeof a > typeof b ? -1 : 1;
            }
        }
        else {
            throw ("error");
        }
    }
}

function calPrg() {
    var nameArry = []
    setInterval(function() {
        nameArry.splice(0,nameArry.length);
        nameArry = opendir();
        count = 0;
        prgValueInfo.splice(0,prgValueInfo.length);
        openfile(nameArry);
        prgValueInfo.sort(by(sortSelect, UorD));
        updateDOM();
    }, 1000);
    setTimeout("setBtnCik()",1000);
}
function updateDOM() {
    $("li").remove(".new");
    prgValueInfo.forEach(function(item,index) {
        var textMem = $('<div class = "col-xs-3 new"></div>').text(item.mem);
        var textStatus = $('<div class = "col-xs-3 new"></div>').text(item.statu);
        var textPID = $('<div class = "col-xs-3 new"></div>').text(item.pid);
        var textName = $('<div class = "col-xs-3 new"></div>').text(item.pName);
        var clrflt = $('<div class = "clear-float"></div>');

        var newli = $('<li class = "new"></li>').append(textName, textPID, textStatus, textMem, clrflt);
        $("#prgInfoTable").append(newli);
    });
    var ppiidd = document.getElementById("pid");
    ppiidd.onclick = function() {
        sortSelect = "pid";
        UorD1 = !UorD1;
        UorD = UorD1;
    }
    var mmeemm = document.getElementById("mem");
    mmeemm.onclick = function() {
        sortSelect = "mem";
        UorD2 = !UorD2;
        UorD = UorD2;
    }
    var nnaame = document.getElementById("pName");
    nnaame.onclick = function() {
        sortSelect = "pName";
        UorD3 = !UorD3;
        UorD = UorD3;
    }
    var ssttatu = document.getElementById("stu");
    ssttatu.onclick = function() {
        sortSelect = "statu";
        UorD4 = !UorD4;
        UorD = UorD4;
    }
}
calPrg();

var exec = require('child_process').exec;
var cmd0 = "kill ", cmd, pidd;
function setBtnCik() {
    var buttn = document.getElementById("btn")
    buttn.onclick= killProcess;
}
function killProcess() {
    pidd = document.getElementById("inpt");
    if (pidd.value=="") {
        alert("please input the pid");
        return;
    }
    cmd = cmd0 + pidd.value;
    exec(cmd,{encoding:'utf8'},function (err,stdout,stderr){
        if (err){
            console.log(err);
            return;
        }
    });
}

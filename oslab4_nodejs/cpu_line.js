function strokCpu() {
    var canv = document.getElementById("cpuCanvas");
    var context = canv.getContext("2d");
    context.beginPath();
    var usg = document.getElementById("cpuusage").innerHTML, count = 0, width = 510;
    context.moveTo(10,300);
    var objj = document.getElementById("canvasContener2");
    setInterval(function() {
        usg = document.getElementById("cpuusage").innerHTML;
        context.lineTo(count + 10 ,300-usg*3);
        if (count > 490) {
            objj.style.overflow = "auto";
            objj.scrollLeft += 10;
        }
        count = count + 10;
        context.strokeStyle = "#4285f4";
        context.stroke();
    },1000);
}
function strokAxis() {
    var canv = document.getElementById("axis");
    var context = canv.getContext("2d");
    context.beginPath();
    context.moveTo(10,300);
    context.lineTo(10,0);
    context.lineTo(5,5);
    context.moveTo(10,0);
    context.lineTo(15,5);
    context.moveTo(10,300);
    context.lineTo(490,300);
    context.lineTo(485,305);
    context.moveTo(490,300);
    context.lineTo(485,295);
    context.font = "bold 16px";
    context.fillStyle = "#555";
    context.fillText("usage %", 15, 10);
    context.fillText("time", 480, 290);
    var i = 0;
    while (i<100) {
        context.fillText(100-10*i, 0, 30*i);
        i = i + 1;
    }
    context.strokeStyle = "#555";
    context.stroke();
    var usg = document.getElementById("cpuusage").innerHTML, count = 0;
}
strokAxis();
strokCpu();

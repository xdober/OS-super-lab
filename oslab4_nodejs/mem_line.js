function strokArc() {
    var canv = document.getElementById("memCanvas");
    var context = canv.getContext("2d");
    context.translate(250,150);
    context.beginPath();
    setInterval(function() {
        context.clearRect(-200,-150,400,300);
        context.arc(0,0,100,0,360);
        context.fillStyle="#eeeeee";
        context.fill();
        var angu = document.getElementById("memusage").innerHTML;
        angu = Number(angu)/100*2*Math.PI;
        context.beginPath();
        context.arc(0,0,100,0,angu);
        context.lineTo(0,0);
        context.lineTo(100,0);
        context.fillStyle="#34a853";
        context.fill();
    console.log(angu);
    }, 1000);
}
strokArc();
function draw() {
    var angu = document.getElementById("memusage");
    angu = Number(angu)/100*2*Math.PI;
    context.arc(0,0,100,0,angu);
    context.lineTo(0,0);
    context.lineTo(100,0);
    context.fillStyle="#34a853";
//    context.stroke();
    context.fill();
}

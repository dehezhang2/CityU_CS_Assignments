function getItems(x){
  switch (x) {
    case 1:
    document.querySelector("#drink1").style.backgroundColor="orange";
    document.querySelector("#dessert1").style.backgroundColor="orange";
    document.getElementById("sushi1").style.backgroundColor = "white";
    var s=getMenuItems("sushi");
    var i=0;
    document.getElementById("neirong").innerHTML="";
    for(i=0;i<s.length;i++){
      var yi=document.createElement("DIV");
      var er=document.createElement("IMG");
      var san=document.createElement("P");
      var si=document.createElement("INPUT");
      var wu=document.createElement("BUTTON");
      var liu=document.createTextNode("add");
      yi.setAttribute("class","neirong");
      yi.setAttribute("id",s[i].code);
      er.setAttribute("src","../img/"+s[i].photo);
      si.setAttribute("type","number");
      si.setAttribute("value","0");
      wu.setAttribute("type","button");
      wu.setAttribute("id",s[i].desc);
      document.getElementById("neirong").appendChild(yi);
      yi.appendChild(er);
      yi.appendChild(san);
      san.appendChild(si);
      san.appendChild(wu);
      wu.appendChild(liu);

      var anniu=document.getElementsByTagName("BUTTON")
      anniu[i].i= i;
      anniu[i].addEventListener("click",function(){myOrder(this.i);});
    };


    break;

    case 2:
    document.querySelector("#sushi1").style.backgroundColor="orange";
    document.querySelector("#dessert1").style.backgroundColor="orange";
    document.getElementById("drink1").style.backgroundColor = "white";
    var d=getMenuItems("drink");
    document.getElementById("neirong").innerHTML="";
    for(i=0;i<d.length;i++){
      var yi=document.createElement("DIV");
      var er=document.createElement("IMG");
      var san=document.createElement("P");
      var si=document.createElement("INPUT");
      var wu=document.createElement("BUTTON");
      var liu=document.createTextNode("add");
      yi.setAttribute("class","neirong");
      yi.setAttribute("id",d[i].code);
      er.setAttribute("src","../img/"+d[i].photo);
      si.setAttribute("type","number");
      si.setAttribute("value","0");
      wu.setAttribute("type","button");
      wu.setAttribute("id",d[i].desc);
      document.getElementById("neirong").appendChild(yi);
      yi.appendChild(er);
      yi.appendChild(san);
      san.appendChild(si);
      san.appendChild(wu);
      wu.appendChild(liu);
      var anniu=document.getElementsByTagName("BUTTON")
      anniu[i].i= i;
      anniu[i].addEventListener("click",function(){myOrder(this.i);});
    };
    break;

    case 3:
    document.querySelector("#sushi1").style.backgroundColor="orange";
    document.querySelector("#drink1").style.backgroundColor="orange";
    document.getElementById("dessert1").style.backgroundColor="white";
    var f=getMenuItems("dessert");
    document.getElementById("neirong").innerHTML="";
    for(i=0;i<f.length;i++){
      var yi=document.createElement("DIV");
      var er=document.createElement("IMG");
      var san=document.createElement("P");
      var si=document.createElement("INPUT");
      var wu=document.createElement("BUTTON");
      var liu=document.createTextNode("add");
      yi.setAttribute("class","neirong");
      yi.setAttribute("id",f[i].code);
      er.setAttribute("src","../img/"+f[i].photo);
      si.setAttribute("type","number");
      si.setAttribute("value","0");
      wu.setAttribute("type","button");
      wu.setAttribute("id",f[i].desc);
      document.getElementById("neirong").appendChild(yi);
      yi.appendChild(er);
      yi.appendChild(san);
      san.appendChild(si);
      san.appendChild(wu);
      wu.appendChild(liu);
      var anniu=document.getElementsByTagName("BUTTON")
      anniu[i].i= i;
      anniu[i].addEventListener("click",function(){myOrder(this.i);});
    };
    break;
  };
};

function myOrder(m){
var anniu=document.getElementsByTagName("BUTTON");
var id=anniu[m].attributes["id"].value;
var kuang=document.getElementsByTagName("INPUT");
var input=kuang[m].value;
var one=document.createElement("TR");
var two=document.createElement("TD");
var three=document.createElement("TD");
var four=document.createTextNode(id);
var five=document.createTextNode(input);
document.getElementById("biaoge").appendChild(one);
one.appendChild(two);
one.appendChild(three);
two.appendChild(four);
three.appendChild(five);
recal(input);
};


function recal(n){
  var nn= Number(n)+Number(document.getElementById("total").num);
  document.getElementById("total").innerHTML=nn;
  document.getElementById("total").num=nn;
};

function init(){
  getItems(1);
  document.getElementById("total").num=0;
  recal(0);
  document.querySelector("#undo").addEventListener("click", function(){return shanchu()});
  hide(1);
};

function shanchu(){
  var lc=document.getElementById("biaoge").lastChild;
  var td=lc.lastChild.childNodes[0].nodeValue;
  recal(-td);
  document.getElementById("biaoge").removeChild(lc);
  return false;
};

function hide(step){
 if(step%2==0){
  document.querySelector("#nav h2").style.display="none";
  var navh3=document.querySelectorAll("#nav p");
  for(i=0;i<navh3.length;i++){
  navh3[i].style.display="none";
  };
  document.querySelector("#nav").style.width="1%";
  document.querySelector("#nav").style.height="5%";
  document.querySelector("#nav").style.transition="height 1s ,width 1s,";
  document.querySelector("#nav").addEventListener("click",function(){hide(1)});
}
 else{
   document.querySelector("#nav h2").style.display="inline";
   var navh3=document.querySelectorAll("#nav p");
   for(i=0;i<navh3.length;i++){
   navh3[i].style.display="block";
   };
   document.querySelector("#nav").style.width="10%";
   document.querySelector("#nav").style.height="25%";
   document.querySelector("#nav").style.transition="height 1s ,width 1s";
   document.querySelector("#nav").addEventListener("click",function(){hide(0)});
 };
}

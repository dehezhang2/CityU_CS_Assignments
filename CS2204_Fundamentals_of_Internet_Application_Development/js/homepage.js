
function cycleMyMessage(i){
var message=[
    "BREAKFAST TIME SPECIAL OFFER - $155 SUSHI SET 12 PIECES",
    "LUNCH TIME SPECIAL OFFER - $188 SUSHI SET 12 PIECES",
    "DINNER TIME SPECIAL OFFER - $998 SUSHI SET 40 PIECES"
  ];
var u=message[i]
document.getElementById("message").innerHTML = u;
 ni=(i+1)%3;
setTimeout("cycleMyMessage(ni)",3000);
};

function checkReservation(){
var x=document.getElementById("time").value,
    y=document.getElementById("number").value,
    z=document.getElementById("category").value;
    x=x.replace(/ /g, "")
    y=y.replace(/ /g, "")
if(x==""||y==""||x=="DD/MM/YYYY"){
  document.getElementById("error").innerHTML="Data not completed, please re-enter!";
}
else{
  reserve(x,z,y)
  if(reserve(x,z,y)==true){
  document.getElementById("error").innerHTML="Reservation done. Thank you."
  }
  else{
    document.getElementById("error").innerHTML="No table is available for the date and time."
  };
};
   return false;
}

function showInfo(k){
  for(i=0;i<dongxi.length;i++){
    dongxi[i].style.display="none"
  };
 dongxi[k].style.display="block";
};

function cycleMyVideo(t) {
    var mp4 = ["http://courses.cs.cityu.edu.hk/cs2204/barbecue.mp4", "http://courses.cs.cityu.edu.hk/cs2204/cakemaking-s.mp4"],
      ogg = ["http://courses.cs.cityu.edu.hk/cs2204/barbecue.ogg", "http://courses.cs.cityu.edu.hk/cs2204/cakemaking-s.ogg"];
    var source = document.getElementsByTagName("SOURCE");
    source[0].setAttribute("src", mp4[t]); document.getElementById("v").load();
    source[1].setAttribute("src", ogg[t]); document.getElementById("v").load();
    t++;
    t %= 2;
    document.querySelector("#v").addEventListener("ended",function(){cycleMyVideo(t)});
}

function init(){
 cycleMyMessage(Math.floor(Math.random()*3));
 showInfo(0);
 hide(1);
 cycleMyVideo(0);
}

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

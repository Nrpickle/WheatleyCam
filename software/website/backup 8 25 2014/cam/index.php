<?php
//Nick McComb
//[mccombn@onid.orst.edu]
//April 2014
?>


<!DOCTYPE html>
<html>
<head>
<link href="data:image/x-icon;base64,AAABAAEAEBAAAAAAAABoBAAAFgAAACgAAAAQAAAAIAAAAAEAIAAAAAAAAAQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAICAgAsMjP+AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACwoNPygsLf8AAAAAJysrXQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHCEg/xETEv4xMS37KiwqigECAAEAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAJCQjsNTs9/zk6OP87PDj/bXd5/2Fra/8+QUD/NDMrSgAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAyMi/+PTw6/z4+O/+Bi4z/Oz06/ywuK/9JTUz/PkA8/zw/Pf9eYmHaAAAAAAAAAAAAAAAAAAAAABEVFMKYoaL/NDUy/yEjIf8jJCL/Pj89/296e/85Ojj/DxAR/xccHP9LUFD/QEE7/xQVFgAAAAAAAAAAAAAAAAAwNTUjMTIw/zY2NP8xMzD/Ojs6/zQ2M/8dHx7/6VYj/+1GH/8ZGxv/LjUz/3eChf+Ik5f/AAAAAAAAAAAAAAAAWF9eii4yMv83ODb/OTo4/x8eG/8dHxz/WyAN//z7e//8/LD/wkYf/wMDA/+IlJX/TVNU/wAAAAAAAAAAAAAAAFplZutQWFj/UVZU/0BDQf9ESUj/QkA5/xgPDf/4fjT//Pp1/8pHH/8cHh7/anV2/1liYv8xOTn/DhEPYAAAAABHUFDmICMj/2Bqa/9haGf/REdG/0REQf9KTEr/EQcF/1YZCv+fq63/W2Ji/7G/wv9/jJD/AAAAAAAAAABCSkvfBgcJAAAAAP8lKSj/a3d5/3N+f/85QUH/ZGts/4KNjv+Om57/scHE/3KAhP86QUD/tsnO/wAAAABtcnHBAAAAAAAAAAAOERLoHSIj/2l2ef+NnJ//jZ6g/1ZgYf9MU1L/hJCR/4SRk//P5er/2vD3/wAAAAAYGhv/AAAAAAAAAAAAAAAAAAAAAAUFBP9OWVv/rMbM/7PM0P+WqK3/rsbN/5moq//8/v7/+fv7/7fP1WBSWFr+AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADw8N/563vP/q/v7/xePr/7jR2f+KnKH/4/3+/xMVFfZrdHY4AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAyPT0FxuXv/x0gIP+wy9L/pK2uKFVaWf4AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAhISEBPEJF60lRVDsAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA/78AAP7/AAD4fwAA4D8AAMAPAAAADwAAgAcAAAAHAAAAAwAAAAYAAIAFAACACwAAwBcAAOAfAAD4vwAA/v8AAA==" rel="icon" type="image/x-icon" />
<title>WheatleyCam</title>
<script src="http://code.jquery.com/jquery-latest.min.js"
        type="text/javascript"></script>
<script>

//Program variables
imageDelay = 50; //Image Delay in milliseconds


//end Program Variables

counter = 0;

status1 = 1;
firstZero = 0;


camPos = 1; //Camera position (initially Jul 2014 1-3)
			//TODO: Note, this might need to be changed so that it maintains the last position, so that people who load the web page and change something else don't change this value, but that might be made moot because of a possible queueing system

tiltAngle = 90;    //Default tilt/rotate angles,
rotateAngleValue = 90;  //TODO: same as above

			
function init()
{
	document.getElementById('rotateAngle').value = 0;
	document.getElementById('tiltAngle').value = 0;
}

var project = "WheatleyCam";

function clickTheButton()
{
	if(window.status1 == 1) {
		document.getElementById("status1").value= "Change to 1";
		window.status1 = 0;
	}
	else {
		document.getElementById("status1").value= "Change to 0";
		window.status1 = 1;
	}
	document.getElementById("status1").innerHTML=("Change to " + Math.abs(window.status1-1));
	updateFile();
}

function increaseStatus1()
{
	window.status1 = window.status1 + 1;
	document.getElementById("status1Disp").innerHTML=("Status 1: " + window.status1);
	updateFile();
}

function decrementStatus1(){
	window.status1 = window.status1 - 1;
	document.getElementById("status1Disp").innerHTML=("Status 1: " + window.status1);
	updateFile();
}

function pos1(){
	window.camPos = 1;
	document.getElementById("status1Disp").innerHTML=("Camera to Position 1");
	updateFile();
}

function pos2(){
	window.camPos = 2;
	document.getElementById("status1Disp").innerHTML=("Camera to Position 2");
	updateFile();
}

function pos3(){
	window.camPos = 3;
	document.getElementById("status1Disp").innerHTML=("Camera to Position 3");
	updateFile();
}

function submitAngles(){
	window.rotateAngle = document.getElementById('rotateAngle').value;
	document.getElementById('status1Disp').innerHTML=('Hello!');
	updateFile(); 
}

function increaseRotateAngle(){
	if(Number(document.getElementById('rotateAngle').value) < 40)
		window.rotateAngleValue = document.getElementById('rotateAngle').value = Number(document.getElementById('rotateAngle').value) + 10;
	updateFile();
}

function decreaseRotateAngle(){
	if(Number(document.getElementById('rotateAngle').value) > -40)
		window.rotateAngleValue = document.getElementById('rotateAngle').value = Number(document.getElementById('rotateAngle').value) - 10;
	updateFile();
}

function increaseTiltAngle(){
	if(Number(document.getElementById('tiltAngle').value) < 0)
		window.tiltAngleValue = document.getElementById('tiltAngle').value = Number(document.getElementById('tiltAngle').value) + 10;
	updateFile();
}

function decreaseTiltAngle(){
	if(Number(document.getElementById('tiltAngle').value) > -90)
		window.tiltAngleValue = document.getElementById('tiltAngle').value = Number(document.getElementById('tiltAngle').value) - 10;
	updateFile();
}


//Runs an AJAX script to use the writeToFile.php script to update the data file
function updateFile(){
	var xmlhttp;
	if (window.XMLHttpRequest)
	  { // code for IE7+, Firefox, Chrome, Opera, Safari
		xmlhttp=new XMLHttpRequest();
	  }
	else
	  { // code for IE6, IE5 
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	  }
	  
	xmlhttp.onreadystatechange=function()  //Handle retur
	  {
	  if (xmlhttp.readyState==4 && xmlhttp.status==200)
		{
		document.getElementById("myDiv").innerHTML="Text written to file!";
		//xmlhttp.responseText; 
		
		}
	  }
	  
	  var finalString;
	  finalString = "writeToFile.php";
	  finalString = finalString.concat("?projectName=");
	  finalString = finalString.concat(window.project);
	  finalString = finalString.concat("&status1=");
	  finalString = finalString.concat(window.status1);
	  finalString = finalString.concat("&camPos=");
	  finalString = finalString.concat(window.camPos);
	  finalString = finalString.concat("&rotateAngle=");
	  finalString = finalString.concat(document.getElementById('rotateAngle').value);
	  finalString = finalString.concat("&tiltAngle=");
	  finalString = finalString.concat(document.getElementById('tiltAngle').value);
	
	xmlhttp.open("GET",finalString,true);
	xmlhttp.send();  

}




//Code to refresh image
//Refreshes the image 
var reimg
window.onload=function () {
  reimg=document.getElementById('loadImage');
  setInterval(function () {
  
	console.log("Checking time: " + checkTime());
	if(checkTime() == 0 && window.firstZero == 0){
		window.firstZero = 1;
		console.error("Loading Image");
		$("#loadImage").attr("src", "http://www.nrpickle.net/wheatleycam/webcam.jpeg?"+d.getTime());
	}
	else if (checkTime() == 0 && window.firstZero == 1){
		window.firstZero = 0;
	}
    //reimg.src=reimg.src.replace(/\?.*/,function () { return '?'+new Date() })
	
	//console.log("Centiseconds: " + checkTime());
  }, window.imageDelay);
}




//Returns a number between 1 and 99, representing centiseconds
function checkTime() {
	d = new Date();
	return Math.floor((Math.floor((d.getTime() / 10)) % 100)/10);
}

function changeImage() {
	document.getElementById('webcamImage').src = document.getElementById('loadImage').src;
	//document.getElementById("myDiv").innerHTML="Hello from Image! " + counter;
	d = new Date();
	document.getElementById("myDiv").innerHTML="Hello from Image! At time:" + (Math.floor((d.getTime() / 10)) %100);
	counter = counter + 1;
	//alert(document.getElementById('webcamImage').getResponseHeader("Content-Length"));
}

/*
    $(document).ready(function() {
       window.setInterval("refreshCamera();", 1000); // one second interval
    });

    var url = 'http://www.nrpickle.net/wheatleycam/webcam.jpeg?refresh=';
    var forcerefresh = 0;

    function refreshCamera()
    {
       forcerefresh = forcerefresh + 1;
       $('#webcamImage').attr('src',url + forcerefresh);

	}
*/
//end refresh



</script>

<style>
button {
	font-size:24px;
}

#rotateAngleHeader {
	font-size:24px;
}
#rotateAngle {
	background-color:white;
	height: 30px;
	width: 50px;
	text-align:center;
	font-size:20px;
}
#rotateAngleForm {
	border:1px solid red;
	float: left;
	width:130px;
	padding:5px;
}

#tiltAngleHeader {
	font-size:24px;
}
#tiltAngle {
	background-color:white;
	height: 30px;
	width: 50px;
	font-size:20px;
	text-align:center;
}
#tiltAngleForm {
	border:1px solid red;
	float: right;
	width:130px;
	padding:5px;
}

#controlPanel {
	width:400px;
	/* height:467px; */
	border: 1px solid black;
	padding:10px
}
</style>
</head>
<body onload="init();">


<h2><span id="myDiv">Nothing changed yet</span></h2>
<h2><span id="status1Disp">1</span></h2>
<br>
<button id="status1" type="button" onclick="clickTheButton()">Change to 0</button>
<button id="statusDec" type="button" onclick="decrementStatus1()">Decrement Status 1 </button>
<button id="statusInc" type="button" onclick="increaseStatus1()">Increment Status 1</button>
<br>

<a href="data.txt">data</a>
<br><br>

<h2>Control Panel</h2>
<div id="controlPanel">
	<div style="width:383px;height:10px;"> <!-- Holds and centers the buttons -->

		<button id="pos1" type="button" onclick="pos1()">Position 1</button>
		<button id="pos2" type="button" onclick="pos2()">Position 2</button>
		<button id="pos3" type="button" onclick="pos3()">Position 3</button>
		
		<br><br>

		<form id="rotateAngleForm">
			<span id="rotateAngleHeader">Rotate Angle</span><br>
			<button type="button" onclick="decreaseRotateAngle()">-</button>
			<input id="rotateAngle" type="text" placeholder="0" name="rotateAngle" disabled="disabled">
			<button type="button" onclick="increaseRotateAngle()">+</button>
		</form>


		<form id="tiltAngleForm">
			<span id="tiltAngleHeader">Tilt Angle</span><br>
			<button type="button" onclick="decreaseTiltAngle()">-</button>
			<input id="tiltAngle" type="text" placeholder="0" name="tiltAngle" disabled="disabled">
			<button type="button" onclick="increaseTiltAngle()">+</button>
		</form>

	</div>

	<br><br><br><br><br><br><br> <!-- Hooray for hacks! (both on this line and the next couple) -->
	<img id="webcamImage" src="http://www.nrpickle.net/wheatleycam/webcam.jpeg" style="width:400px">
	<img id="loadImage" src="http://www.nrpickle.net/wheatleycam/webcam.jpeg" style="display:none;">


</div>


<script>

$("#loadImage").load(function() {
    changeImage();
});

</script>

</body>
</html>
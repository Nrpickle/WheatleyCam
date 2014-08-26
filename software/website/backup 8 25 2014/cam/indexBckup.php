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
var imageDelay;
imageDelay = 1000; //Image Delay in milliseconds


//end Program Variables

var counter;
counter = 0;

var status1;
status1 = 1;

var project = "WheatleyCam";

function clickTheButton()
{
	if(window.status1 == 1) {
		window.status1 = 0;
	}
	else {
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
	  finalString = finalString.concat("?project=");
	  finalString = finalString.concat(window.project);
	  finalString = finalString.concat("&status1=");
	  finalString = finalString.concat(window.status1);
	
	xmlhttp.open("GET",finalString,true);
	xmlhttp.send();  

}


//Code to refresh image
var reimg
window.onload=function () {
  reimg=document.getElementById('loadImage');
  setInterval(function () {
//d = new Date();
	//while((Math.floor((d.getTime() / 10)) %100) != 0)
	//{ console.log("Infinite loop! "); }   //CURRENT: Infinite Loop to wait until ready
	//waitfor(checkTime, 0, 1, 0, 'image', function() { console.log('Load image!'); });
	console.log(checkTime());
	$("#loadImage").attr("src", "http://www.nrpickle.net/wheatleycam/webcam.jpg?"+d.getTime());
    //reimg.src=reimg.src.replace(/\?.*/,function () { return '?'+new Date() })
	
	//console.log("Centiseconds: " + checkTime());
	
  }, window.imageDelay);
}




//Returns a number between 1 and 99, representing centiseconds
function checkTime() {
	d = new Date();
	return Math.floor((d.getTime() / 10)) % 100;
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

    var url = 'http://www.nrpickle.net/wheatleycam/webcam.jpg?refresh=';
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
</style>
</head>
<body>

<h2><span id="myDiv">Nothing changed yet</span></h2>
<h2><span id="status1Disp">1</span></h2>
<br>
<button id="status1" type="button" onclick="clickTheButton()">Change to 0</button>
<button id="statusDec" type="button" onclick="decrementStatus1()">Decrement Status 1 </button>
<button id="statusInc" type="button" onclick="increaseStatus1()">Increment Status 1</button>
<br>
<a href="data.txt">data</a>

<br><br>
<img id="webcamImage" src="http://www.nrpickle.net/wheatleycam/webcam.jpg" style="width:400px">
<img id="loadImage" src="http://www.nrpickle.net/wheatleycam/webcam.jpg" style="display:none;">


<script>

$("#loadImage").load(function() {
    changeImage();
});

</script>

</body>
</html>
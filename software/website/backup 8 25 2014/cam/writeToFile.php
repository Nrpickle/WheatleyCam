<?php 
function writeOne($filename, $project, $status1, $camPos){
	$file = fopen( $filename, "w" );
	if( $file == false )
	{
	   echo ( "Error in opening new file" );
	   exit();
	}
	// "Starting at line ten... input variable names.
	
	
	$header = "Wheatley Cam data file \nWritten by Nick McComb for OSURC [mccombn@onid.orst.edu] \nThe first 10 lines of the file are reserved for documentation \nAll references to lines are (index 0) \nLine: \n";
	//10:projectName,11:status,12:camPos
	$i = 10;
	$t = 0;
	$keys = array_keys($_GET);	
	foreach($keys as $k){ 
		$header = $header . (string) $i . ":" . $k; 
		if($k != end($keys)){
			$header = $header . ",";
			$t++;
		}
		
		$i = $i + 1;
	}
	
	$header = $header . "\n\n\n\n\n";
	
	// add header to final str, add variables to str, break up var with new lines
	(string) $vals = array_values($_GET);
	$tempVar;
	foreach($vals as $v){
		echo $v;
		echo "<br>";
		$tempVar = $tempVar . $v . "\n";
		//echo $tempVar;
	}
	$final = $header . $tempVar;
	fwrite( $file, $final );
	chmod( $filename , 0775); //Has the web server change the permissions
	fclose( $file );	
	
	return $final;
}

function checkFile($filename) {
	if( file_exists( $filename ) ) 
	{
	  $filesize = filesize ( $filename );
	  $msg = "File created with name $filename ";
	  $msg .= "containing $filesize bytes";
	  echo ($msg);
	}
	else
	{
	  echo ("File $filename does not exist");
	}
}

//TODO: Move these two into the writeOne() function (also, change it's name)
$project=$_REQUEST["project"];
$status1 = $_REQUEST["status1"];
$camPos = $_REQUEST["camPos"];


$final = writeOne("data.txt", $project, $status1, $camPos);

//echo ;
echo "Wrote '$final' to the file!";

?>
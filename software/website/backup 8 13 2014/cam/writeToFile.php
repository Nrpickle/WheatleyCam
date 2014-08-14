<?php 
function writeOne($filename, $project, $status1, $camPos){
	$file = fopen( $filename, "w" );
	if( $file == false )
	{
	   echo ( "Error in opening new file" );
	   exit();
	}
	
	$header = "Wheatley Cam data file \nWritten by Nick McComb for OSURC [mccombn@onid.orst.edu] \nThe first 10 lines of the file are reserved for documentation \nAll references to lines are (index 0) \nLine 10: Project Name, Line 11: Current status, Line 12: Camera Position \n10:projectName,11:status,12:camPos\n \n \n \n \n";
	$final = $header . $project . "\n" . $status1  . "\n" . $camPos;
	
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
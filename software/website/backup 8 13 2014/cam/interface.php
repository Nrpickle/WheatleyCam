<?php 
function writeOne($filename, $text){
	$file = fopen( $filename, "a");
	if( $file == false )
	{
	   echo ( "Error in opening new file" );
	   exit();
	}
	fwrite( $file, $text );
	chmod( $filename, 0775); //Has the web server change the permissions
	fclose( $file );	

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

writeOne("test.txt", "Woo! Go robots! \n");
?>

<html>
<head>
	<title>WheatleyCam test file</title>
</head>

<body>

<?php


checkFile("test.txt");

?>

</body>

</html>

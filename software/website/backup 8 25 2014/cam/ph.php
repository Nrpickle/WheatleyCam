<?php
//writefile.php
file_put_contents("testFile.html", "Hello\nWorld!\n");
header("Location: testFile.html");
?>

<html>
<head>
	<title>Test Page</title>
</head>

<body>
	This is an example wile writing page.
</body>
</html>
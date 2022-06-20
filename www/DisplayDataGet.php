<!DOCTYPE html>
<html>
<head>
    <link rel="stylesheet" href="../css/PagesStyle.css"> 
</head>
<body>

<h2>Info Submitted !!</h2>
<h3>Your First Name: </h3> 
    <?php
    if(isset($_GET['fname']))
        echo $_GET['fname'];
    ?>
<h3>Your Last Name: </h3>
    <?php
    if(isset($_GET['lname']))
        echo $_GET['lname'];
    ?>
<!--
<h2>REQUEST_METHOD: </h2> <?php echo $_SERVER["REQUEST_METHOD"]; ?>
<h2>CONTENT_LENGTH: </h2> <?php echo $_SERVER["CONTENT_LENGTH"]; ?>
<h2>CONTENT_TYPE: </h2> <?php echo $_SERVER["CONTENT_TYPE"]; ?>
<h2>GATEWAY_INTERFACE: </h2> <?php echo $_SERVER["GATEWAY_INTERFACE"]; ?>
<h2>SERVER_NAME: </h2> <?php echo $_SERVER["SERVER_NAME"]; ?>
<h2>SERVER_PORT: </h2> <?php echo $_SERVER["SERVER_PORT"]; ?>
<h2>SERVER_PROTOCOL: </h2> <?php echo $_SERVER["SERVER_PROTOCOL"]; ?>
<h2>QUERY STRING: </h2> <?php echo $_SERVER["QUERY_STRING"]; ?>
<h2>PATH_INFO: </h2> <?php echo $_SERVER["PATH_INFO"]; ?>
<h2>PATH_TRANSLATED: </h2> <?php echo $_SERVER["PATH_TRANSLATED"]; ?>
-->
</body>
</html>
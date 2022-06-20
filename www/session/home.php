<?php
session_start();
?>
<!DOCTYPE html>
<html>
<body>


<?php
if (isset($_POST['username']) and isset($_POST['password'])) {
    $_SESSION['username'] = $_POST['username'];
    $_SESSION['password'] = $_POST['password'];
}
if (isset($_SESSION['username']) and isset($_SESSION['password'])) {
    echo '<h2>Welcome ' . $_SESSION['username'] . '</h2>';
    echo '<a href="logout.php">Logout</a>';
} else {
    echo '<h2>Please login</h2>';
    echo '<a href="login.php">Login</a>';
}   
?> 

</body>
</html>
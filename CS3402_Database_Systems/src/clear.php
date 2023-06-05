
<html>
<body>
<?php include 'src.php';
/*
HOST: ora11g.cs.cityu.edu.hk
PORT: 1522
SERVICE_NAME: orcl.cs.cityu.edu.hk
*/
    $conn = connectServer(); 
    clearAll($conn);
    oci_close($conn);
?>
<p>All the seats are available now, and all user information are deleted!</p>
<a href="../main.php">back</a>
</body>
</html>

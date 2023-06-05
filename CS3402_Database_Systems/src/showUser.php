<html>
<body>
<?php include 'src.php';
/*
HOST: ora11g.cs.cityu.edu.hk
PORT: 1522
SERVICE_NAME: orcl.cs.cityu.edu.hk
*/
    $conn = connectServer(); 
    showUser($conn);
    oci_close($conn);
?>
<br><a href="../main.php">back</a>
</body>
</html>

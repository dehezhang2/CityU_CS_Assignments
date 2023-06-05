<html>
<body>
<?php include 'src.php';
/*
HOST: ora11g.cs.cityu.edu.hk
PORT: 1522
SERVICE_NAME: orcl.cs.cityu.edu.hk
*/

    $conn = connectServer();
    $ticketnum = $_GET["ticketnum"];
    $house = $_GET["house"];
    $name = $_GET["name"];
    $email = $_GET["email"];
    if($_GET["name"]!='null'&&$_GET["name"]!=null&&$_GET["email"]!='null'&&$_GET["email"]!=null&&$ticketnum!='null'&&$ticketnum!=null) {
        print "Welcome, ".$_GET["name"]."!<br>\n";
        print "Your email address is: ".$_GET["email"].".<br>\n"; 
        print "Your order is: Order ".$ticketnum." tickets in House ".$house."<br>\n";
    }
    else {
        print "Please fill all the information to make an order!<br>\n";
    }
    showTable($conn, $house); 
    // Close the Oracle connection
    oci_close($conn);
?>

</body>
</html>

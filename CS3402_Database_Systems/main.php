<html>
<body>
<script>
function display_house(house, email, ticketnum, name) {
    var ifr = document.querySelector("iframe.display");
    ifr.src = 'src/display.php?house='+house
            +'&ticketnum='+ticketnum
            +'&email='+email
            +'&name='+name;
}
</script>

<form action="" method="get">
    House:<br> 
    <select name="house" id="house" onchange="display_house(this.value,'null','null','null')">
        <option value="A">A</option>
        <option value="B">B</option>
        <option value="C">C</option>
        <option value="D">D</option>
        <option value="E">E</option>
    </select>
    <br>
    Ticket number (between 1 and 10):<br> 
    <input type="number" name="ticketnum" min="1" max="10"> <br>
    Name:<br> <input type="text" name="name"><br>
    E-mail:<br> <input type="text" name="email"><br>
    <input type="submit">
   </form>
<iframe class="display" width=600 height=400></iframe>

<?php include 'src/src.php';
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
    if($house >= 'A'&&$house <= 'E'&&$ticketnum>=1&&$ticketnum<=10&&$email!=null&&$name!=null)
        orderSeat($conn, $house, $ticketnum, $name, $email); 
    if($house >= 'A'&&$house <= 'E'){
        print "<script>display_house('".$house
            ."', '".$email
            ."', '".$ticketnum
            ."', '".$name
            ."')</script>\n";
    }
    else{
         print "<script>display_house('A', 'null', 'null', 'null')</script>\n";
    }
    // Close the Oracle connection
    oci_close($conn);
?>
<br><a href="src/clear.php">If the seat is not initailized as all available, click me!</a>
<br><a href="src/showUser.php">If you want to look at the list of users, click me!</a>
</body>
</html>

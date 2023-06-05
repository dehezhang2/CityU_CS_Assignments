<html>
<body>
<?php

    function connectServer(){
        $conn = oci_connect("dehezhang2", "55199998", "//ora11g.cs.cityu.edu.hk:1522/orcl.cs.cityu.edu.hk");
        if (!$conn) {
            $m = oci_error();
            echo $m['message'], "\n";
            exit;
        }
        return $conn;
    }

    function runSql($conn, $cmd){
        $stid = oci_parse($conn, $cmd);
        if (!$stid) {
            $e = oci_error($conn);
            trigger_error(htmlentities($e['message'], ENT_QUOTES), E_USER_ERROR);
        }

        // Perform the logic of the query
        $r = oci_execute($stid);
        if (!$r) {
            $e = oci_error($stid);
            trigger_error(htmlentities($e['message'], ENT_QUOTES), E_USER_ERROR);
        }
        //print $cmd.'\n<br>';
        return $stid;
    }

    function showTable($conn, $houseid) {
        print "House ".$houseid."<br>\n";
        $stid = runSql($conn, 'SELECT * FROM SEAT 
                               WHERE HID=\''.$houseid.'\'
                               ORDER BY RID, CID');
        // Fetch the results of the query
        print "<table border='1' style='text-align: center;'>\n";
        $i = 0;
        while ($seat = oci_fetch_array($stid, OCI_ASSOC+OCI_RETURN_NULLS)) {
            if($i%10==0){
                if($i!=0) print "</tr>\n";
                print "<tr>\n";
                print "<td>".$seat['RID']."</td>\n";
            }

            if($seat['UNAME']!=null){
                print "<td style='background-color: red; width: 50px; height: 50px'>
                      ".$seat['RID'].$seat['CID']."<br>".$seat['UNAME']." </td>\n";
            } else {
                print "<td style='background-color: green; width: 50px; height: 50px'>                
                      ".$seat['RID'].$seat['CID']." </td>\n";

            }
            $i++;
        }
        print "<tr>\n";
        for($i = -1; $i < 10; $i++){
            if($i<0){
                print "<td></td>\n";
            }
            else{
                print "<td>".$i."</td>\n";
            }
        }
        print "</tr>\n</table>\n";   
    }


    function clearAll($conn){
        runSql($conn, 'UPDATE SEAT SET UNAME = NULL');
        runSql($conn, 'DELETE FROM CLIENT');
    }

    function orderSeat($conn, $houseid, $seatNum, $name, $email){
        print "<br>Result: ";
        if($seatNum > 0 && $seatNum <= 10){
            $rows = array("A", "B", "C", "D", "E");
            for($i = 0; $i < 5; $i++){
                $stid = runSql($conn, 'SELECT * FROM SEAT 
                                       WHERE HID=\''.$houseid.'\'
                                       AND RID =\''.$rows[$i].'\'
                                       ORDER BY RID');
                $cnt = 0;
                $start = -1;
                while ($seat = oci_fetch_array($stid, OCI_ASSOC+OCI_RETURN_NULLS)){
                    if($seat["UNAME"]==null){
                        if($cnt==0) $start = $seat['CID'];
                        $cnt++;
                    }
                }
                if($cnt >= $seatNum){
                    $j = 0;
                    for( ;$j<$seatNum; $j++){
                        runSql($conn, 'UPDATE SEAT
                                       SET UNAME =\''.$name.'\'
                                       WHERE HID=\''.$houseid.'\'
                                       AND RID = \''.$rows[$i].'\'
                                       AND CID = '.($j + $start));
                    }
                    $stid = runSql($conn, "SELECT * FROM CLIENT WHERE EMAIL = '".$email."'");
                    $first = oci_fetch_array($stid, OCI_ASSOC+OCI_RETURN_NULLS);
                    if($first["NAME"] == null){
                        runSql($conn, "INSERT INTO CLIENT
                                   VALUES('".$name."','".$email."')");
                    }
                    print "The order is successful. The ";
                    if($seatNum == 1){
                        print "ticket is ".$rows[$i].$start."<br>";
                    } elseif($seatNum == 2){
                        print "tickets are ".$rows[$i].$start." and ".$rows[$i].($start + 1)."<br>";
                    } else{
                        print "tickets are ".$rows[$i].$start." to ".$rows[$i].($start + $seatNum - 1)."<br>";
                    }
                    return;
                }
            }

        }
        print "The order is NOT successful!<br>";
    }

    function showUser($conn){
        $stid = runSql($conn,"SELECT * FROM CLIENT");
        print "<table border='1'>\n";
        print "<thead><tr><th>User name</th><th>Email(primary key)</th></tr></thead>";
        while ($row = oci_fetch_array($stid, OCI_ASSOC+OCI_RETURN_NULLS)) {
            print "<tr>\n";
            foreach ($row as $item) {
                print "    <td>" . ($item !== null ? htmlentities($item, ENT_QUOTES) : "&nbsp;") . "</td>\n";
            }
            print "</tr>\n";
        }
        print "</table>\n";
    }
    

?>

</body>
</html>

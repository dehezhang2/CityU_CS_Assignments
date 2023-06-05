<?php
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
    $conn = oci_connect("dehezhang2", "55199998", "//ora11g.cs.cityu.edu.hk:1522/orcl.cs.cityu.edu.hk");
    if (!$conn) {
       $m = oci_error();
       echo $m['message'], "\n";
       exit;
    }
    else {
       print "Connected to Oracle!<br>\n";
    }
    $id = array("A", "B", "C", "D", "E");
    for($i = 0; $i < 5 ; $i++){
        for($j = 0; $j < 5; $j++){
            for($k = 0; $k < 10; $k++){
                runsql($conn, "INSERT INTO SEAT
                               VALUES('".$id[$i]."', '".$id[$j]."', ".$k.", '&UNAME')");


            }
        }
    } 

?>

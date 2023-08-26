<?php

include("modele/User.php");
$user = new User();
    if(isset($_POST['log_data'])){
        addLogValue($_POST['log_data']);
        http_response_code(200);
    }else{
        http_response_code(400);
    }

function addLogValue($value) {
    $filename = "log.txt";
    $temp_file = "";
    if (!file_exists($filename)) {
        // file does not exist, create it in temp folder
        $temp_dir = sys_get_temp_dir();
        echo "Saved at $temp_dir/$filename";
        $temp_file = "$temp_dir/$filename";
    }

    $timestamp = date("Y-m-d H:i:s");
    $line = "$timestamp,$value\n";
    file_put_contents($temp_file, $line, FILE_APPEND);
}
      
?>
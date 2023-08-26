<?php
header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Headers: *');
header('Content-Type: application/json; charset=utf-8');
header('Access-Control-Allow-Methods: PUT , GET , POST');
include("modele/User.php");
include("tools/twilio.php");
$user = new User();
$MAX_Gaz = 400;
$MIN_Flame = 420;

    function getParameters()
     {
          $filename = "params.txt";
          // $temp_dir = sys_get_temp_dir();
          // $temp_file = "$temp_dir/$filename";

          // Read the content of the file
          $content = file_get_contents($filename);

          if ($content !== false) {
               $params = json_decode($content);
               return $params;
          } else {
               return false;
          }
     }
    if(isset($_GET['flame']) 
    && isset($_GET['gaz']) 
    && isset($_GET['detectionCount'])   //To detect if the alert went longer enough
    && isset($_GET['TurnAlert'])){      //To send SMS or not
        // Flame Sensor Module
        $flameValue = $_GET['flame'];
        // Gaz Sensor Module
        $GazValue = $_GET['gaz'];
        // detectionCount
        $detectionCount = $_GET['detectionCount'];
        // TurnAlert
        $TurnAlert = $_GET['TurnAlert'];



        echo "flame is at ".$_GET['flame']."\n";
        echo "gaz is at".$_GET['gaz']."\n";
        $user->SendData($_GET['flame'],$_GET['gaz']);

        // !DETECT FIRE OR GAZ -> SEND SMS
        if($detectionCount>2 && !strcasecmp($TurnAlert,"On")){
            if (($GazValue >= $MAX_Gaz) || ($flameValue < $MIN_Flame)) {
                // Emergency Phone number
                $params = getParameters();
                if($params){
                    $msg = (($flameValue < $MIN_Flame))?"Flame":"Gaz";
                    $phone = $params->phone;
                    sendMessage("URGENT ALERT: $msg detected at your property",$phone);
                }else{
                    echo "\nNO phone number found";
                }
            }
        }
        http_response_code(200);

    }else{
        echo "Nothing";
        http_response_code(400);
    }
?>
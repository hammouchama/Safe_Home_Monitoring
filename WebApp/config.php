<?php
header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Headers: *');
header('Content-Type: application/json; charset=utf-8');
header('Access-Control-Allow-Methods: PUT , GET , POST');
include("modele/User.php");
$user = new User();

    /* * *
     *  SET PARAMS TO FILE
     * * */
    
    if(isset($_POST)){
        $tmp_params = [];
        if(isset($_POST['phone']))
            $tmp_params['phone'] = $_POST['phone'];
    
        if(isset($_POST['EspIP']))
            $tmp_params['EspIP'] = $_POST['EspIP'];
    
        if(!empty($tmp_params)){
            setParameters($tmp_params);
            http_response_code(200);
        }else{
            http_response_code(400);
        }
    } 


    function setParameters($params) {
        $filename = "params.txt";
        
        
        $content = json_encode($params);

        // Write the content to the file
        file_put_contents($filename, $content);
    }

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

      
?>
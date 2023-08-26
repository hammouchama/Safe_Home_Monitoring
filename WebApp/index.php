<?php
header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Headers: *');
header('Access-Control-Allow-Methods: PUT , GET , POST');
?>

<!DOCTYPE html>
<html lang="en">

<head>
     <meta charset="UTF-8">
     <meta http-equiv="X-UA-Compatible" content="IE=edge">
     <meta name="viewport" content="width=device-width, initial-scale=1.0">
     <title>Chart Gaz & Flame</title>
     <link rel="stylesheet" href="css/alert.css">
     <link rel="stylesheet" href="css/style.css">
     <script src="https://cdnjs.cloudflare.com/ajax/libs/moment.js/2.29.1/moment.min.js"></script>
     <script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.9.4/Chart.min.js"></script>
     <script src="https://unpkg.com/axios/dist/axios.min.js"></script>
     <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.4/jquery.min.js"></script>

<body>
     <?php

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
     $res = getParameters();
     ?>

<header>
     <div class="Logo">
          <div class="title">SafeHome Monitoring</div>
          <div class="desc">Gas and Flame Detection for a Secure Home</div>
     </div>
</header>
     <div class="chart center-div" style="box-shadow: 2px 2px 5px #999;">
          <canvas id="myChart"></canvas>
          <br>
          <hr>
          <br>
          <div style="display:flex; justify-content: space-between;">
          <!-- display:flex;flex-direction: column;gap: 10px; -->
               <button  id="restart" class="button-1">Restart</button>
                    
               <button  id="desctive" class="button-2">Deactivate</button>
               <button  id="active" class="button-3">Activate</button>
          </div>
          <br>
          <hr>
          <br>
          <div class="status">
               <h2>Status: <span id="connected">-----------</span></h2>
               <p>IP: <?= $res->EspIP ?></p>
               <p>Phone for alert : <?= $res->phone ?></p>
               <p id="alertStatus">Alert status : <?= $res->statu ?></p>
               <p>
                    <a id="configLink" class="hidden" href="http://<?= $res->EspIP ?>">Access to config</a>
               </p>
               
          </div>

          <div class="blok">
               <input type="text" class="diss" id="statu" value="<?= $res->statu ?>">
               <input type="text" id="ip" value="<?= $res->EspIP ?>">
          </div>
     </div>

     <script src="js/alert.js"></script>
     <script src="js/script.js"></script>
</body>

</html>
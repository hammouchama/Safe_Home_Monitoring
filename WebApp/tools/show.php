<?php
header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Headers: *');
header('Content-Type: application/json; charset=utf-8');
header('Access-Control-Allow-Methods: PUT , GET , POST');
include("../modele/User.php");
$user = new User();
echo json_encode($user->dataDisply());
?>
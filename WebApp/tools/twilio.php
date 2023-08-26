<?php
require 'vendor/autoload.php';
use Twilio\Rest\Client;

function sendMessage($msg,$tel){
    // Your Account SID and Auth Token from twilio.com/console
    // To set up environmental variables, see http://twil.io/secure
    $account_sid = 'AC0fd2b4bb2c37713179b76a51fa69ffb1';
    $auth_token = 'fa7bc8ad5c1155d1171fb4f2529d05e2';
    // In production, these should be environment variables. E.g.:
    // $auth_token = $_ENV["TWILIO_AUTH_TOKEN"]

    // A Twilio number you own with SMS capabilities
    $twilio_number = "+12542847539";

    $client = new Client($account_sid, $auth_token);
    $message = $client->messages->create(
        // Where to send a text message (your cell phone?)
        $tel,
        array(
            'from' => $twilio_number,
            'body' => $msg
        )
    );

    if($message){
        echo "message sent";
    }else{
        echo "Ta Roo7";
    }
}
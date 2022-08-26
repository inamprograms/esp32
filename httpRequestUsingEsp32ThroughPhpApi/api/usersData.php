<?php
if ($_SERVER['REQUEST_METHOD'] == 'POST')
{
    $json_data = file_get_contents('php://input');
    $decoded_data = json_decode($json_data);

    $cnic = $decoded_data->cnic;
    $temp = $decoded_data->temp;
    $hum = $decoded_data->hum;
    $ledStatus = $decoded_data->ledStatus;
    $btnStatus = $decoded_data->btnStatus;

    $con = mysqli_connect("localhost", "root", "", "esp_data") or die(mysql_error());
    // Selecing database
    // $db = mysqli_select_db($con, "esp_data") or die("not selected");

  
    $result = mysqli_query($con, "INSERT INTO room1(temperature,humidity,led_status,btn_status,user_cnic) VALUES($temp,$hum,$ledStatus,$btnStatus,$cnic )") or die("not inserting");
    if ($result) 
    {
        http_response_code(201);
        echo ("insert have been sucessfull");
    } 
    else 
    {
        echo ("insert have been unsucessfull");
    }

}
else if($_SERVER['REQUEST_METHOD'] == 'PUT')
{
    $json_data = file_get_contents('php://input');
    $decoded_data = json_decode($json_data);

    $cnic = $decoded_data->cnic;
    $temp = $decoded_data->temp;
    $hum = $decoded_data->hum;
    $ledStatus = $decoded_data->ledStatus;
    $btnStatus = $decoded_data->btnStatus;
    
    $con = mysqli_connect("localhost","root", "", "esp_data") or die(mysql_error());
    $result = mysqli_query($con, "UPDATE room1 SET temperature = $temp , humidity = $hum ,led_status = $ledStatus, btn_status = $btnStatus WHERE user_cnic = $cnic");
    if($result) 
    {
        echo "Room data Updated";}
    else 
    { 
        echo "update unsuccessful";
    }
}
else if($_SERVER['REQUEST_METHOD'] == 'PATCH')
{
    $json_data = file_get_contents('php://input');
    $decoded_data = json_decode($json_data);

    $cnic = $decoded_data->cnic;
    $ledStatus = $decoded_data->ledStatus;

    $con = mysqli_connect("localhost", "root","" , "esp_data") or die(mysql_error());

    $result = mysqli_query($con, "UPDATE room1 SET led_status = $ledStatus WHERE user_cnic = $cnic");

    if ($result) {
        echo "Status updated.";
    }
    else
    {
        echo "Status not updated";
    }

}
else if($_SERVER['REQUEST_METHOD'] == 'GET')
{
    $cnic =  $_GET['cnic'];
    $response = array();
    $responseData["totalData"] = array();
    
    $con = mysqli_connect("localhost","root","","esp_data")or die(mysql_error());

    $result = mysqli_query($con, "SELECT * FROM room1 WHERE user_cnic = $cnic ");

    while ($row = mysqli_fetch_array($result)) {
        $response['cnic'] = $row['user_cnic']; 
        $response['temp'] = $row['temperature']; 
        $response['hum'] = $row['humidity']; 
        $response['ledStatus'] = $row['led_status']; 
        $response['btnStatus'] = $row['btn_status']; 
        array_push($responseData["totalData"], $response);
        
    }
    echo json_encode($responseData);

}
else if($_SERVER['REQUEST_METHOD'] == 'DELETE')
{
    $json_data = file_get_contents('php://input');
    $decoded_data = json_decode($json_data);
    
    // $cnic =  $_GET['cnic'];
    $cnic = $decoded_data->cnic;

    $con =  mysqli_connect("localhost", "root", "" , "esp_data") or die(mysql_error());
    $result = mysqli_query($con, "DELETE FROM room1 WHERE user_cnic = $cnic");

    if($result){
        echo "data deleted successfully";
    }
    else{
        echo "data deletion unsuccessful";
    }

}
else
{
    http_response_code(400);
    echo json_encode(array("status 404", "message" => "No products found."));
}


/*
    DUMMY PAYLOAD
    {
        "cnic" : 12345678910,
        "temp" : 12,
        "hum" : 13,
        "ledStatus" : 1,
        "btnStatus" : 1
    }
*/
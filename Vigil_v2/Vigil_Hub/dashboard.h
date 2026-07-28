#ifndef DASHBOARD_H
#define DASHBOARD_H


const char dashboardHTML[] PROGMEM = R"rawliteral(

<!DOCTYPE html>

<html>

<head>

<title>Vigil Dashboard</title>

<meta name="viewport" content="width=device-width, initial-scale=1">

<style>

body
{
    font-family: Arial;
    text-align:center;
    background:#111;
    color:white;
}


.card
{
    margin:40px auto;
    padding:30px;
    width:80%;
    max-width:400px;
    background:#222;
    border-radius:15px;
}


#state
{
    font-size:40px;
}


#confidence
{
    font-size:25px;
}

</style>


</head>


<body>


<div class="card">

<h1>Vigil</h1>

<div id="state">
Loading...
</div>


<div id="confidence">
</div>

<div id="connection">
</div>


</div>



<script>


async function updateStatus()
{

    try
    {

        let response = await fetch('/status');

        let data = await response.json();


        let stateBox = document.getElementById("state");
let confidenceBox = document.getElementById("confidence");
let connectionBox = document.getElementById("connection");


stateBox.innerHTML = data.state;

confidenceBox.innerHTML =
    "Confidence: " + data.confidence + "%";


connectionBox.innerHTML =
    data.connected ? "Sensor ONLINE" : "Sensor OFFLINE";



if(data.state == "OCCUPIED")
{
    stateBox.style.color = "red";
}

else if(data.state == "EMPTY")
{
    stateBox.style.color = "lime";
}

else if(data.state == "NO_SIGNAL")
{
    stateBox.style.color = "gray";
}

else
{
    stateBox.style.color = "yellow";
}


    }

    catch(error)
    {

        document.getElementById("state").innerHTML =
            "OFFLINE";

    }

}


setInterval(
    updateStatus,
    1000
);


updateStatus();


</script>


</body>

</html>


)rawliteral";


#endif
# include <Arduino.h>
# include <ESP8266WiFi.h>
# include <appliance.h>
# include <pirSensor.h>

// Wifi server credentials
const char *ssid = "WDI_Server2";
const char *password = "macbook1";

// Pins of vibration sensor of appliances
const int washerOnSensorPin = 14;
const int washerFinishedSensorPin = 4;
const int dryerCombinedSensorPin = 5; 

// Appliances
Appliance washer(washerOnSensorPin, washerFinishedSensorPin);
Appliance dryer(dryerCombinedSensorPin);

// query which contains the BOOLEAN values which light should be on
String dataString = "";


// --------------- definition of methods(functions) ------------------------


void appendDataString(Appliance appliance){
  if (appliance.isRunning()){
    dataString += "1";  // appliance running
    dataString += "0";  // appliance not finished
  }
  else if (appliance.isFinished()){
    dataString += "0";  // appliance not running
    dataString += "1";  // appliance finished
  }
  else {
    dataString += "0";
    dataString += "0";
  }
}

void connectedSignIndicator(){
  WiFiClient client;
  const char * host = "192.168.4.1";
  const int httpPort = 80;
  String url = "/data/?sensor_reading=1111";
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
  }
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
              "Host: " + host + "\r\n" +
              "Connection: close\r\n\r\n");
}


// ---------------------- START OF PROGRAM -----------------------

void setup() {
  Serial.begin(9600);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  // once client connects to server (sign) all lights turn on for 1 sec.
  connectedSignIndicator();
  delay(1000);
}


void loop() {
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const char * host = "192.168.4.1";
  const int httpPort = 80;

  client.setTimeout(1000);
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
  }


  // This is the order in which LED instructions are send. 
  // [WasherIsRunning, WasherIsFinished, DryerIsRunning, DryerIsFinished]
  dataString = "";

  washer.turnedOnSensor.measure();
  washer.finishedSensor.measure();
  dryer.combinedSensor.measure();

  // appends information about washer first e.g "01" (washer not running, washer finished)
  // then information about dryer e.g. "00" (dryer not running, dryer not finsihed)
  appendDataString(washer);
  appendDataString(dryer);
  
  // create a URI for the request. Something like /data/?sensor_reading=
  //                               [WasherIsRunning, WasherIsFinished, DryerIsRunning, DryerIsFinished]
  String url = "/data/";
  url += "?sensor_reading=";
  url += dataString;

  // send data string to server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                "Host: " + host + "\r\n" +
                "Connection: close\r\n\r\n");


  // Debug print statements (how does the debugger work for external hardware????)

    // Serial.println("Washer:");
    // Serial.println(washer.turnedOnSensor.lightOn());
    // Serial.println(washer.finishedSensor.lightOn());
    // Serial.println(washer.isRunning());
    // Serial.println(washer.isFinished());
    // Serial.println("Dryer");
    // Serial.println(dryer.combinedSensor.lightOn());
    // Serial.println(dryer.combinedSensor.lightBlinking());
    // Serial.println(dryer.isRunning());
    // Serial.println(dryer.isFinished());
    // Serial.println(dataString);
    // Serial.println("");

    Serial.println("Washer:");
    Serial.println(washer.turnedOnSensor.read());
    Serial.println(washer.finishedSensor.read());
    Serial.println("Dryer");
    Serial.println(dryer.combinedSensor.read());
    
    Serial.println(dataString);
    Serial.println("");

  delay(500);
}


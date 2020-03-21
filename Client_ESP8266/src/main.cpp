# include <Arduino.h>
# include <ESP8266WiFi.h>
# include <vibrationSensor.h>


// TODO implement Neotimer 10sec stand in front of washer or dryer

const char *ssid = "WDI_Server2";
const char *password = "macbook1";


String dataString = "";
String lastSendDataString = "";

VibrationSensor washer(5);

int newData(String oldDataString){
  if (oldDataString != lastSendDataString){
    return true;
  }
}

void appendDataString(VibrationSensor appliance){
  if (appliance.isRunning()){
    dataString += "1";
  }
  else{
    dataString += "0";
  }
}


void setup() {
  Serial.begin(9600);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void loop() {
  // This is the order in which LED instructions are send.
  dataString = "";

  washer.measure();
  // TODO dryer.measure();

  appendDataString(washer);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const char * host = "192.168.4.1";
  const int httpPort = 80;

  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // create a URI for the request. Something like /data/?sensor_reading=
  //                                         [ledWorking, ledFinished, ledWorking, ledFinished]
  String url = "/data/";
  url += "?sensor_reading=";
  url += dataString;

  // This will send the request to the server
  if (newData(dataString)){
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                "Host: " + host + "\r\n" +
                "Connection: close\r\n\r\n");
    lastSendDataString = dataString;
  }

  
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  // Debug print statements  
  Serial.println(washer.read());
  Serial.println(washer.countHighs());
  Serial.println(url);
  Serial.println("");
  
  delay(1000);
}
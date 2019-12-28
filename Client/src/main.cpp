# include <Arduino.h>
# include <ESP8266WiFi.h>
# include <ldr.h>


const char *ssid = "WDI_Server2";
const char *password = "macbook1";

String dataString = "";        // value read from LDR's

Ldr greenLdr(A0);


void appendDataString(Ldr pin){
  if (pin.ledIsOn()){
    dataString += "1";
  }
  else{
    dataString += "0";
  }
}


void setup() {
  Serial.begin(115200);
  delay(10);

  // Explicitly set the ESP8266 to be a WiFi-client
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

}

void loop() {

  dataString = "";
  appendDataString(greenLdr);


  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const char * host = "192.168.4.1";
  const int httpPort = 80;

  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request. Something like /data/?sensor_reading=123
  String url = "/data/";
  url += "?sensor_reading=";
  url += dataString;


  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    Serial.println("While Triggered");
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  Serial.println(dataString);
  Serial.println(url);

  delay(500);
}
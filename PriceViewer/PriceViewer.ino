#include <ESP8266WiFi.h>
 
const char* ssid     = "Rapture";
const char* password = "ichosetheimpossible...";
 
const char* host = "api.thingspeak.com";
 
int value = 1; 
 
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
  
}//end setup
  
void loop() {
  if(Serial.read() == 'r'){
    makeRequest();    
  }
} //- See more at: http://www.esp8266.com/viewtopic.php?f=29&t=2912#sthash.Bq0SDsM9.dpuf


void makeRequest(){
  WiFiClient Client;
  const int httpPort = 80;
  if (!Client.connect(host, httpPort)) {
    Serial.println("Connection failed");
    return;
  }
  
  // We now create a URI for the request
  String url = "/apps/thinghttp/send_request?api_key=HIRBUTDRIRD8AMQ1";
  
  
  // This will send the request to the server
 Client.print(String("GET ") + url + "&headers=false" + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  delay(1000);
  String lines;  // Read all the lines of the reply from server and print them to Serial
  while(Client.available()){
    
  lines += Client.readStringUntil('\r');
  
 }

 lines = lines.substring(424, 438);
  Serial.println(lines);
  
  }


#include <TFT_eSPI.h> // Graphics and font library for ILI9341 driver chip
#include <SPI.h>

#define TFT_GREY 0x5AEB // New colour

TFT_eSPI tft = TFT_eSPI(); 
#include <ESP8266WiFi.h>
String LastPrice;
String LastTime;
String Time;
String Price;
const char* ssid     = "Rapture";
const char* password = "ichosetheimpossible...";
 
const char* host = "api.thingspeak.com";
 
int value = 1; 
 
void setup() {
  tft.init();
  tft.setCursor(0, 0, 0);
  //tft.setRotation(1);
// Fill screen with grey so we can see the effect of printing with and without 
  // a background colour defined
  tft.fillScreen(TFT_BLACK);
  Serial.begin(9600);
  delay(10);
 
  // We start by connecting to a WiFi network
  tft.setTextColor(TFT_GREEN);
  tft.setTextFont(1);
  tft.print("Connecting to "); tft.println(ssid);
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
  tft.println("WiFi connected");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  tft.print("IP address: "); tft.println(WiFi.localIP());
  Serial.println(WiFi.localIP());
  
}//end setup
  
void loop() {
  
    updatePrice();
    updateTime();
    screenPrice(Price);
    screenTime(Time);   
  //delay(1000);
} //- See more at: http://www.esp8266.com/viewtopic.php?f=29&t=2912#sthash.Bq0SDsM9.dpuf


void updatePrice(){
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
  delay(1500);
  String lines;  // Read all the lines of the reply from server and print them to Serial
  while(Client.available()){
    
  lines += Client.readStringUntil('\r');
  
 }

 lines = lines.substring(427, 433);
  if (lines == NULL){screenPrice(LastPrice);}
  else{Price = lines; LastPrice = lines;}
  Serial.println(lines);
  
  
  }






 void screenPrice(String price){
  tft.setCursor(20, 95, 0);
  tft.fillScreen(TFT_BLACK);
  
  tft.setTextColor(TFT_GREEN); tft.setTextFont(7);
  tft.print(price);
  tft.setTextColor(TFT_GREEN); tft.setTextFont(2);
  tft.println("EUR");
  
  
  
  

  
 }



 void updateTime(){
  WiFiClient Client;
  const int httpPort = 80;
  if (!Client.connect(host, httpPort)) {
    Serial.println("Connection failed");
    return;
  }
  
  // We now create a URI for the request
  String url = "/apps/thinghttp/send_request?api_key=OP0IE31DYE7SKVD0";
  
  
  // This will send the request to the server
 Client.print(String("GET ") + url + "&headers=false" + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  delay(1500);
  String lines;  // Read all the lines of the reply from server and print them to Serial
  while(Client.available()){
    
  lines += Client.readStringUntil('\r');
  
 }

  
  lines = lines.substring(393, 401);
  if (lines == NULL){screenTime(LastTime);}
  else{Time = lines; LastTime = lines;}
  Serial.println(lines);

 
 }

 void screenTime(String times){
  tft.setCursor(95, 150, 0);
  
  tft.setTextColor(TFT_GREEN); tft.setTextFont(2);
  tft.println(times);
  
  
  
  
  

  
 }


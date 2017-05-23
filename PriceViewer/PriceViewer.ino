
#include <TFT_eSPI.h> // Graphics and font library for ILI9341 driver chip
#include <SPI.h>
#include "logos.h"
#include <EEPROM.h>


#define TFT_GREY 0x5AEB // New colour
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GREY     0xD6BA
int address = 0;
byte value;


int pricePOSETHx = 20;
int pricePOSETHy = 155;

int pricePOSBTCx = 5;
int pricePOSBTCy = 155;
//int timePOS = ;



TFT_eSPI tft = TFT_eSPI(); 
#include <ESP8266WiFi.h>
String LastPriceETH="0000";
String LastPriceBTC="0000";
String LastTime="0000";
String Time;
String PriceETH;
String PriceBTC;
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
  EEPROM.begin(512);

  ssid = EEPROM.read(0);
  password = EEPROM.read(1); 


  
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
  tft.fillScreen(TFT_BLACK);
  //drawBitmap(94,50,ethLogo,52,85,WHITE);
  
}//end setup
  
void loop() {

    if(Serial.available()){configurationMenu();}
    else{
    updatePriceETH();
    updateTime();
    tft.fillRect(0,0,320,240,TFT_BLACK);
    drawBitmap(94,50,ethLogo,52,85,WHITE);
    screenPriceETH(PriceETH, 7);
    screenTime(Time);
    
    //delay(3000);
       
    
    updatePriceBTC();
    updateTime();
    tft.fillRect(0,0,320,240,TFT_BLACK);
    drawBitmap(77,50,btcLogo,85,85,WHITE);
    screenPriceBTC(PriceBTC, 7);
    screenTime(Time);
    
    //delay(3000);
      
    }
    
    
    
} //- See more at: http://www.esp8266.com/viewtopic.php?f=29&t=2912#sthash.Bq0SDsM9.dpuf





void configurationMenu(){
  tft.fillScreen(TFT_BLACK);
  drawBitmap(41,81,usbLogo,157,157,WHITE);

  while(!Serial.available()){}
  tft.setCursor(135,300,0);
  tft.setTextColor(TFT_GREEN);
  tft.setTextFont(1);
  tft.print("Connected");
  String stringRead;
  while(1){
  stringRead = "";
  while(Serial.available()){
    delay(3);
    Serial.println("Serial Connected");
    char c = Serial.read();
    stringRead += c;
  }
  if(stringRead != ""){Serial.println(stringRead);}
  if(stringRead.startsWith("exit")){tft.fillScreen(TFT_BLACK);tft.setCursor(135,300,0);Serial.println(stringRead);ESP.restart();}
  }
  
  }



























void updatePriceETH(){
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
  if (lines == NULL){screenPriceETH(LastPriceETH, 7);}
  else{PriceETH = lines; LastPriceETH = lines;}
  Serial.println(lines);
  
  
  }


void updatePriceBTC(){
  WiFiClient Client;
  const int httpPort = 80;
  if (!Client.connect(host, httpPort)) {
    Serial.println("Connection failed");
    return;
  }
  
  // We now create a URI for the request
  String url = "/apps/thinghttp/send_request?api_key=5J5OU2UMXHIPPYFN";
  
  
  // This will send the request to the server
 Client.print(String("GET ") + url + "&headers=false" + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  delay(1500);
  String lines;  // Read all the lines of the reply from server and print them to Serial
  while(Client.available()){
    
  lines += Client.readStringUntil('\r');
  
 }

 lines = lines.substring(427, 434);
  if (lines == NULL){screenPriceBTC(LastPriceBTC, 5);}
  else{PriceBTC = lines; LastPriceBTC = lines;}
  Serial.println(lines);
  
  
  }






 void screenPriceETH(String price, int sizeFont){
  tft.setCursor(pricePOSETHx, pricePOSETHy, 0);
  
  //tft.fillRect(pricePOSx,pricePOSETHy,320,240,TFT_BLACK);
  
  //tft.fillScreen(TFT_BLACK);
  
  tft.setTextColor(TFT_GREEN); tft.setTextFont(sizeFont);
  tft.print(price);
  tft.setTextColor(TFT_GREEN); tft.setTextFont(2);
  tft.println("EUR");
  
 }



 void screenPriceBTC(String price, int sizeFont){
  tft.setCursor(pricePOSBTCx, pricePOSBTCy, 0);
  
  //tft.fillRect(pricePOSx,pricePOSETHy,320,240,TFT_BLACK);
  
  //tft.fillScreen(TFT_BLACK);
  
  tft.setTextColor(TFT_GREEN); tft.setTextFont(sizeFont);
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
  tft.setCursor(95, 210, 0);
  
  tft.setTextColor(TFT_GREEN); tft.setTextFont(2);
  tft.println(times);
  
  
  
  
  

  
 }


void drawBitmap(int16_t x, int16_t y,
 const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color) {

  int16_t i, j, byteWidth = (w + 7) / 8;
  uint8_t byte;

  for(j=0; j<h; j++) {
    for(i=0; i<w; i++) {
      if(i & 7) byte <<= 1;
      else      byte   = pgm_read_byte(bitmap + j * byteWidth + i / 8);
      if(byte & 0x80) tft.drawPixel(x+i, y+j, color);
    }
  }
}












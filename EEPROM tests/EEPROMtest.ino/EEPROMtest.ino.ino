#include <EEPROM.h>

//VerdadesINQUESTIONAVEIS
int ssidSizePOS = 0;
int passSizePOS = 2;
int ssidStartPOS = 1;
int passStartPOS= 3;
//



int ssidSize;
int passSize;
int ssidStart = 4;
int passStart;


String ssid = "Rapture";
String password = "ichosetheimpossible...";


void setup() {
  // put your setup code here, to run once:
  ssidSize = ssid.length();
  passSize = password.length();  
  passStart=ssidStart+ssidSize;

  
  EEPROM.begin(512);

  for (int i = 0 ; i < 512 ; i++) {
    EEPROM.write(i, 0);
  }
  
  EEPROM.write(passSizePOS, password.length());
  EEPROM.write(ssidSizePOS, ssidSize);
  EEPROM.write(ssidStartPOS, ssidStart);
  EEPROM.write(passStartPOS, passStart);
  

  int j = 0;
  for(int x=ssidStart;x<ssidStart+ssidSize;x++){
    EEPROM.write(x, byte(ssid.charAt(j)));j++;
  }
j = 0;
  for(int x=passStart;x<passStart+passSize;x++){
    EEPROM.write(x, byte(password.charAt(j)));j++;
  }

  
  
    EEPROM.commit();
  Serial.begin(9600);
  Serial.println("");
  Serial.println("");
  Serial.println(EEPROM.read(0));
  Serial.println(EEPROM.read(1));
  Serial.println(EEPROM.read(2));
  Serial.println(EEPROM.read(3));

  for(int x=ssidStart;x<ssidStart+ssidSize;x++){
  char c = char(EEPROM.read(x));
  Serial.print(c);
  
}
Serial.print("\n");

  for(int x=passStart;x<passStart+passSize;x++){
  char c = char(EEPROM.read(x));
  Serial.print(c);
  
}
//Serial.print("\n");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  

}

/**
 *  Created By Shmulik Debby on 10.06.2017
 *  This program will connect to home network and display signal quality on LCD screen after connection.
 *  Using LCD i2c librery : https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library
 *  Using Wemos D1 mini pro+LCD I2C 20X4 with 0x3F address

*/

#include <ESP8266WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
const char* ssid = "NetworkSSID";
const char* password = "NetworkPass";
LiquidCrystal_I2C lcd(0x3F, 20, 4);

void setup() {
  Serial.begin(115200);
  delay(10);
  
  //Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA); //disable hotsopt signal
  WiFi.begin(ssid, password);
  
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    lcd.print(".");
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi connected, IP:");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
    lcd.setCursor(0, 3);
    lcd.print("Quality:");
}

void loop() {
  while(WiFi.status()== WL_CONNECTED){
     long rssi = WiFi.RSSI();
     long rssiCalc;
     delay(500);
    //Serial.print("RSSI:"+rssi);
//    converting Db to quality %
//https://stackoverflow.com/questions/15797920/how-to-convert-wifi-signal-strength-from-quality-percent-to-rssi-dbm#15798024
//https://www.speedguide.net/faq/how-does-rssi-dbm-relate-to-signal-quality-percent-439
    if(rssi <= -100)
        rssiCalc = 0;
    else if(rssi >= -50)
        rssiCalc = 100;
    else
        rssiCalc = 2 * (rssi + 100);
        
    lcd.setCursor(9,3);
    lcd.print(rssiCalc);
    
    if(rssiCalc<99){
      lcd.setCursor(12,3);
      lcd.print(" ");
      lcd.setCursor(11,3);
    }
    else
    lcd.setCursor(12,3);
    lcd.print("%");
  } //end while connected
}


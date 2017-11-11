/* 	ESP8266_DHT22_NTP_OLED.ino by Mouky66

Libs needed:
 Time.h & TimeLib.h:  https://github.com/PaulStoffregen/Time
 Timezone.h: https://github.com/JChristensen/Timezone
 SSD1306.h & SSD1306Wire.h:  https://github.com/squix78/esp8266-oled-ssd1306
 NTPClient.h: https://github.com/arduino-libraries/NTPClient
 ESP8266WiFi.h & WifiUDP.h: https://github.com/ekstrand/ESP8266wifi

 128x64 OLED pinout:
 GND | Ground
 Vin | 3.3V
 SDA | I2C SDA (GPIO D3)
 SCL | I2C SCL (GPIO D5)
 
 DHT pinout (front view left to right:
 Vin | 3.3V
 Data | D6
 3	| empty
 GND | Ground
 
 For other Fonts use http://oleddisplay.squix.ch/#/home
 */ 

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <SSD1306.h>
#include <NTPClient.h>
#include <TimeLib.h>
#include <Timezone.h>
#include "DIALOG.h"
#include <DHT.h>
#define DHTPIN D6     
#define DHTTYPE DHT22   // DHT11 or DHT22
DHT dht(DHTPIN, DHTTYPE);

#define NTP_OFFSET   0 * 60 * 60      	// In seconds
#define NTP_INTERVAL 60 * 1000    		// In miliseconds
#define NTP_ADDRESS  "de.pool.ntp.org" 
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);

// Create the display object
SSD1306  display(0x3c, D3, D5); //0x3c or 0x3d
 
const char* ssid = "x";   				// insert your ssid 
const char* password = "x";             // inset your password
String date;
String t;
const char * days[] = {"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"} ;
const char * months[] = {"Jan", "Feb", "Mar", "Apr", "Mai", "Juni", "Juli", "Aug", "Sep", "Okt", "Nov", "Dez"} ;
//const char * ampm[] = {"AM", "PM"} ;
 

void displayTempHumid(){ // Read Temp and Setup the Display
  float h = dht.readHumidity();  
  float d = dht.readTemperature(); 
  d = d - 2.5; //corrected value 
  //float f = dht.readTemperature(true); 

  display.clear();
  display.setFont(Dialog_plain_16);
  display.drawString(0, 0, String(d) + "C  " + String(h) + "%\t"); 
  display.setFont(Dialog_plain_30);
  display.drawString(22, 17, String(t));
  display.setFont(Dialog_plain_14);
  display.drawString(0, 48, String(date)); 
}

void wificonnect ()
{
    display.clear();
    display.setFont(Dialog_plain_12);
    display.drawString(0, 0, "Verbinde mit Wifi...");
    display.drawString(0, 16, String(ssid));
    display.display();
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
    }
    display.drawString(0, 36, "verbunden.");
    display.display();
    delay(1000);
  }

void getntptime ()
{
  date = ""; 
  t = "";
  timeClient.update();
  unsigned long epochTime =  timeClient.getEpochTime();
  time_t local, utc;
  utc = epochTime;

  //Central European Time (Frankfurt, Paris)
  TimeChangeRule CEST = { "CEST", Last, Sun, Mar, 2, 120 };     //Central European Summer Time
  TimeChangeRule CET = { "CET ", Last, Sun, Oct, 3, 60 };       //Central European Standard Time
  Timezone CE(CEST, CET);
  local = CE.toLocal(utc);

  // Date
  date += days[weekday(local)-1];
  date += ", ";
  date += day(local);
  date += ". ";
  date += months[month(local)-1];

  // Time
  t += hour(local);
  t += ":";
  if(minute(local) < 10) 
  t += "0";
  t += minute(local);
  }

void setup () 
{
  timeClient.begin();   // Start the NTP UDP client
  dht.begin(); // initialize dht
  display.init();
  display.clear();
}
void loop() 
{
  if (WiFi.status() == WL_CONNECTED) //Check WiFi connection status
  {   
   getntptime();
   displayTempHumid();
   display.display();
   delay(10000); 
  }
  else // reconnect to wifi again if disconnected
  {
    wificonnect();
  } 
}

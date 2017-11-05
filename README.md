# ESP8266_DHT22_NTP_OLED
NodeMCU with ESP8266 to show Time, Temperature and Humidity on an 128x64 OLED Display

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


Hardware used:
	- NodeMCU with ESP8266
	- DHT22 Temperature and Humidity Sensor
	- SSD1306 OLED 128x64 Display
	- Enclosure used https://www.thingiverse.com/thing:1720314 (Thanks to Yopo)
	
Following Libs are used:
 Time.h & TimeLib.h:  https://github.com/PaulStoffregen/Time
 Timezone.h: https://github.com/JChristensen/Timezone
 SSD1306.h & SSD1306Wire.h:  https://github.com/squix78/esp8266-oled-ssd1306
 NTPClient.h: https://github.com/arduino-libraries/NTPClient
 ESP8266WiFi.h & WifiUDP.h: https://github.com/ekstrand/ESP8266wifi
 
For other Fonts use http://oleddisplay.squix.ch/#/home
 
Just insert your WiFi credentials and upload :)
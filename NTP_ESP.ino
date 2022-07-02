#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <TM1637Display.h>     

#define CLK 2                       // Define the connections pins:
#define DIO 0

TM1637Display display = TM1637Display(CLK, DIO);              // Create display object of type TM1637Display:

const char *ssid     = "YAMANAKA";
const char *password = "this_is_a_scam";

const long utcOffsetInSeconds = 19802;  

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);


//Conn to be displayed on 7Seg display while connecting to Wifi
const uint8_t Conn[] = {
  SEG_A | SEG_D | SEG_E | SEG_F,                   // C
  SEG_G | SEG_E | SEG_D | SEG_C,                   // o
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_C | SEG_E | SEG_G                            // n
};

void setup(){
  Serial.begin(115200);
   // Clear the display:
  display.clear();
  
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
    display.setSegments(Conn);
    
  }

  timeClient.begin();
}

void loop() {
  int A,B;
  
  timeClient.update();
  display.setBrightness(7);                   // Set the brightness:
  
  A = timeClient.getHours() * 100 + timeClient.getMinutes();
  Serial.print(A);
  B = timeClient.getSeconds();
  Serial.println(B);
  
  if((B % 2) == 0)
  {
    display.showNumberDecEx(A, 0b01000000 , false, 4, 0); 
  }
  else
  {
    display.showNumberDecEx(A, 0b00000000 , false, 4, 0); 
  }
  
}

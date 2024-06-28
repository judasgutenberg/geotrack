/*****************************************
* ESP32 GPS VKEL 9600 Bds
******************************************/
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>  
 

#define SCK     5    // GPIO5  -- SX1278's SCK
#define MISO    19   // GPIO19 -- SX1278's MISnO
#define MOSI    27   // GPIO27 -- SX1278's MOSI
#define SS      18   // GPIO18 -- SX1278's CS
#define RST     23   // GPIO14 -- SX1278's RESET
#define DI0     26   // GPIO26 -- SX1278's IRQ(Interrupt Request)
#define BAND  915E6

unsigned int counter = 0;

 
String rssi = "RSSI --";
String packSize = "--";
String packet ;

#include <TinyGPS++.h>                        
TinyGPSPlus gps;         

void setup()
{
  Serial.begin(115200); //18, 19,  27 kinda worked for TX 2, 3, 4, 5 kinda worked for RX 24, 28, 29, 30, 31 causes crashes in RX 6 causes crashes
  Serial1.begin(9600, SERIAL_8N1, 34, 12);   //17-TX 18-RX  //34 tx 12rx works on green check //txt:12-17,20-26 no gps, 3-5 no gps  6-11 crashy 
  Serial.println("LoRa Setup");
  
  SPI.begin(SCK,MISO,MOSI,SS);
  LoRa.setPins(SS,RST,DI0);
  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  //LoRa.onReceive(cbk);
  //  LoRa.receive();
  Serial.println("init ok");


  delay(1500);
  
}

void loop()
{
  Serial.print("Latitude  : ");
  Serial.println(gps.location.lat(), 5);
  Serial.print("Longitude : ");
  Serial.println(gps.location.lng(), 4);
  Serial.print("Satellites: ");
  Serial.println(gps.satellites.value());
  Serial.print("Altitude  : ");
  Serial.print(gps.altitude.feet() / 3.2808);
  Serial.println("M");
  Serial.print("Time      : ");
  Serial.print(gps.time.hour());
  Serial.print(":");
  Serial.print(gps.time.minute());
  Serial.print(":");
  Serial.println(gps.time.second());
  Serial.println("**********************");



  Serial.println(String(counter));

  // send packet
  LoRa.beginPacket();
  LoRa.print("Lat: ");
  LoRa.print(gps.location.lat(), 5);
  LoRa.print("Lon: ");
  LoRa.print(gps.location.lng(), 5);
  LoRa.print("Sats: ");
  LoRa.print(gps.satellites.value(), 5);
  LoRa.print("Alt: ");
  LoRa.print(gps.altitude.feet());
  LoRa.print(gps.satellites.value(), 5);
  LoRa.print("Time: ");
  LoRa.print(gps.time.hour());
  LoRa.print(":");
  LoRa.print(gps.time.minute());
  LoRa.print(":");
  LoRa.println(gps.time.second());
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;
  
  smartDelay(1000);                                      

  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));
}

static void smartDelay(unsigned long ms)                
{
  unsigned long start = millis();
  do
  {
    while (Serial1.available())
      gps.encode(Serial1.read());
  } while (millis() - start < ms);
}

#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "DHT.h"
#include <TFT.h>  
#include <SPI.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define cs   10
#define dc   9
#define rst  8 
static const int RXPin = 4, TXPin = 3; //i change it myself and it is work
static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);
DHT dht(DHTPIN, DHTTYPE);
TFT TFTscreen = TFT(cs, dc, rst);

char houre[8];
char minut[8];
char seconde[8];
char jour[8];
char moi[8];
char anne[8];

char tep[8];
char Latitude[8];
char longitude[8];
char speede[8];

void setup()
{
  Serial.begin(9600);
  
  Serial.println(F("DHTxx test!"));
  dht.begin();
  TFTscreen.begin();
  TFTscreen.background(0, 0, 0);
  TFTscreen.stroke(255,0,155);
  TFTscreen.setTextSize(1.5);
  TFTscreen.text("Location info", 40, 1);
  //(x,y) screen cordinate

  ss.begin(GPSBaud);
  Serial.println(TinyGPSPlus::libraryVersion());
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0){
    if (gps.encode(ss.read())){
      if (gps.time.isValid()){
        
        TFTscreen.setTextSize(2);
        int h = gps.time.hour()+3;
        TFTscreen.stroke(255,255,255);
        String ho = String(h);
        ho.toCharArray(houre, 8);
        TFTscreen.text(houre, 5,20);

        TFTscreen.setTextSize(2);
        TFTscreen.stroke(255,255,255);
        TFTscreen.text(" : ", 15,20);

        TFTscreen.setTextSize(2);
        int m = gps.time.minute();
        TFTscreen.stroke(255,255,255);
        String mi = String(m);
        mi.toCharArray(minut, 8);
        TFTscreen.text(minut, 45,20);

        TFTscreen.setTextSize(2);
        TFTscreen.stroke(255,255,255);
        TFTscreen.text(" : ", 55,20);

        TFTscreen.setTextSize(2);
        int s = gps.time.second();
        TFTscreen.stroke(255,255,255);
        String se = String(s);
        se.toCharArray(seconde, 8);
        TFTscreen.text(seconde, 85,20);
        delay(1000); 
        TFTscreen.stroke(0, 0, 0);
        TFTscreen.text(speede, 95,80 );
        TFTscreen.text(seconde, 85,20);
        TFTscreen.text(minut, 45,20);
        TFTscreen.text(houre, 5,20);
        TFTscreen.text(tep, 90, 100);
        TFTscreen.text(longitude, 95,70 );
        TFTscreen.text(Latitude, 95,60 );
        TFTscreen.text(jour, 5,40);  
        }
        
        if (gps.date.isValid()){
        TFTscreen.setTextSize(1);
        int d = gps.date.day();
        TFTscreen.stroke(255,255,255);
        String da = String(d);
        da.toCharArray(jour, 8);
        TFTscreen.text(jour, 5,40);

        TFTscreen.setTextSize(1);
        TFTscreen.stroke(255,255,255);
        TFTscreen.text("/", 20,40);

        TFTscreen.setTextSize(1);
        int m = gps.date.month();
        TFTscreen.stroke(255,255,255);
        String mo = String(m);
        mo.toCharArray(moi, 8);
        TFTscreen.text(moi, 30,40);

        TFTscreen.setTextSize(1);
        TFTscreen.stroke(255,255,255);
        TFTscreen.text("/", 40,40);

        TFTscreen.setTextSize(1);
        int a = gps.date.year();
        TFTscreen.stroke(255,255,255);
        String an = String(a);
        an.toCharArray(anne, 8);
        TFTscreen.text(anne, 50,40);
        
        if (gps.location.isValid()){
          //write latitude
          TFTscreen.setTextSize(1);
          TFTscreen.text("Latitude :", 20,60 );
          float L = gps.location.lat();
          TFTscreen.stroke(255,255,255);
          String Lat = String(L);
          Lat.toCharArray(Latitude, 8);
          TFTscreen.text(Latitude, 95,60 );
          //write longitude
           TFTscreen.setTextSize(1);
           TFTscreen.stroke(255,255,255);
          TFTscreen.text("Longitude :", 20,70 );
          TFTscreen.setTextSize(1);
          float l = gps.location.lng();
          TFTscreen.stroke(255,255,255);
          String lon = String(l);
          lon.toCharArray(longitude, 8);
          TFTscreen.text(longitude, 95,70 );
          }
            
           if (gps.speed.isValid()){
            TFTscreen.setTextSize(1);
            TFTscreen.text("Speed :", 20,80 );
            float sp = gps.speed.kmph();
            TFTscreen.stroke(255,255,255);
            String spd = String(sp);
            spd.toCharArray(speede, 8);
            TFTscreen.text(speede, 95,80 );
            }

              //ecrit le signe degré
             TFTscreen.setTextSize(2);
             TFTscreen.stroke(255,255,255);
             TFTscreen.setTextSize(1);
             TFTscreen.text("o", 150, 95);
             TFTscreen.setTextSize(2);

  //mesure la temperature e l'ecris
            float t = dht.readTemperature();
            TFTscreen.stroke(255,255,255);
            String temp = String(t);
            temp.toCharArray(tep, 8);
            TFTscreen.text(tep, 90,100 );

            TFTscreen.setTextSize(1);
            TFTscreen.stroke(255,0,255);
            TFTscreen.text("@Leonel", 1,119 );
        
      //displayInfo();
    }
  }

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}
}

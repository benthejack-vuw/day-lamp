// pin definitions
#define OLED_DC 5
#define OLED_CS 3
#define OLED_RES 7

#include <SPI.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiSpi.h"

SSD1306AsciiSpi oled;
extern tmElements_t alarm_time;


int last_minute = -1; 
void setup_oled(){
  //
  pinMode(OLED_RES, OUTPUT);
  digitalWrite(OLED_RES,HIGH); 

  oled.begin(&Adafruit128x64, OLED_CS, OLED_DC);
  oled.setFont(Adafruit5x7);  
  
}

void oled_display(tmElements_t current_time){

  
  if(current_time.Minute != last_minute){
  oled.set1X();

  oled.clear();
  if(alarm_time.Hour < 10)
    oled.print("0");
  oled.print(alarm_time.Hour);
  oled.print(":");
  if(alarm_time.Minute < 10)
    oled.print("0");
  oled.print(alarm_time.Minute);

  oled.print("           ");
  if(current_time.Day < 10)
    oled.print("0");
  oled.print(current_time.Day);
  oled.print("/");
  if(current_time.Month < 10)
    oled.print("0");
  oled.print(current_time.Month);
  oled.println("");
  
  oled.set2X();
  oled.println("");
  oled.print("   ");
  if(current_time.Hour < 10)
    oled.print("0");
  oled.print(current_time.Hour);
  oled.print(":");
  if(current_time.Minute < 10)
    oled.print("0");
  oled.println(current_time.Minute);


    
  last_minute = current_time.Minute;
  }
}


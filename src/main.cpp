#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <HardwareSerial.h>
#include <Ticker.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
HardwareSerial ASM(2);
Ticker status;
int step, count;
String steps[5] = {"Mess", "Stop", "Vent", "Cal ", "blan"};

void periodicStatus() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Step: ");
  lcd.print(steps[step]);
  lcd.setCursor(0,2);
  lcd.print(count);
  count++;
  if (count >= 10) {
    count = 0;
    step++;
  }
  if (step >= 4) {
    step = 0;
  }
}


void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  Serial.begin(9600);
  ASM.begin(9600, SERIAL_8N1, 16, 17);
  status.attach_ms(1000, periodicStatus);
}

void loop()
{
  
}
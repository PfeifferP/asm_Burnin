#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <HardwareSerial.h>
#include <Ticker.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
HardwareSerial ASM(2);
Ticker status;
int loops, step, count;
String steps[5] = {"Messen", "Stop", "Belüften", "Kalibrieren ", "blan"};
String cmds[5] = {"=CYE", "=CYD", "=IVE", "!AC", ""};
int counts[5] = { 90, 5, 5, 10, 4};

String gettime (int t) {
  String st = "";
  int m = (t/60);
  int s = (t - (m*60));
  if (m<10) {st = "0";}
  st = st + String(m)+":";
  if (s<10){st=st+"0";}
  st = st + String(s);
  return st;
}

void periodicStatus() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(steps[step]);
  lcd.setCursor(15,0);
  lcd.print(gettime(count));
  
  count--;
  if (count < 1) {
    step++;
    if (step >= 4) { step = 0; }
    count = counts[step];
    Serial.println(cmds[step]);
  }
}


void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  Serial.begin(9600);
  ASM.begin(9600, SERIAL_8N1, 16, 17);
  loops = 5;
  count = counts[0];
  Serial.println(cmds[0]);
  status.attach_ms(1000, periodicStatus);
}

void loop()
{
  
}
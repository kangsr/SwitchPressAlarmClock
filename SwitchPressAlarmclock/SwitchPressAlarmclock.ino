#include<Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
#include <DS1302.h>



// Init the LCD
LiquidCrystal_I2C lcd(0x3F,16,2);
// Init the DS1302
DS1302 rtc(2, 3, 4);

Servo myservo;
int pos=0;

  int numTones = 8;
  int tones[] = {261, 294, 330, 349, 392, 440, 494, 523};


  
void setup() {
  myservo.attach(A0);

  pinMode(5, OUTPUT);

   // Set the clock to run-mode, and disable the write protection
  rtc.halt(false);
  rtc.writeProtect(false);
  
  // Setup LCD to 16x2 characters
  lcd.init(); 
  lcd.backlight();
  
}



void loop() {
  // Display time centered on the upper line
  lcd.setCursor(0, 0);
  lcd.print(rtc.getTimeStr());
  
  // Display abbreviated Day-of-Week in the lower left corner
  lcd.setCursor(0, 1);
  lcd.print(rtc.getDOWStr(FORMAT_SHORT));
  
  // Display date in the lower right corner
  lcd.setCursor(6, 1);
  lcd.print(rtc.getDateStr());

  // Wait one second before repeating :)
  delay (100);
  
  for (pos = 0; pos <=110; pos += 1) {
    myservo.write(pos);
    delay(15);
  }

  myservo.detach();

  delay(1000);

  for(int i = 0; i<numTones; i++){
    tone(5, tones[i]);
    delay(500);
  }


  
}

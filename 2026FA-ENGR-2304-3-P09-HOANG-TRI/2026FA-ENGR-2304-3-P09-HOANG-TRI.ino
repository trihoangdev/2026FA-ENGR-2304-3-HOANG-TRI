// 2026FA-ENGR-2304-3-P09-HOANG-TRI

#include <Wire.h>
#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd(0);

int leds[] = {0b1101, 0b1100, 0b1000, 0b0100}; // pins 13, 12, 8, 4
int compressor = 0b0111;                       // pin 7
bool launched = false;
void setup()
{
  lcd.begin(16, 2);
  pinMode(compressor, OUTPUT);
  for (int i = 0; i < 4; i++)
  {
    pinMode(leds[i], OUTPUT);
  }

  lcd.print("System Starting");
  delay(1500);
  lcd.clear();
}

void loop()
{
  if (launched)
  {
    return;
  }

  // read the two dials and convert to 0-100 psi
  int target = map(analogRead(A0), 0, 1023, 0, 0b1100100);
  int psi = map(analogRead(A2), 0, 1023, 0, 0b1100100);

  // show on LCD
  lcd.setCursor(0, 0);
  lcd.print("Target: ");
  lcd.print(target);
  lcd.print(" psi   ");
  lcd.setCursor(0, 1);
  lcd.print("Now:    ");
  lcd.print(psi);
  lcd.print(" psi   ");

  if (psi < target - 0b10)
  {
    digitalWrite(compressor, HIGH); // pressure too low: compressor ON
  }
  else if (psi >= target)
  {
    digitalWrite(compressor, LOW); // pressure reached: compressor OFF
  
    // countdown from 10 to 0 in binary on the LEDs
    for (int t = 0b1010; t >= 0; t--)
    {
      for (int i = 0; i < 4; i++)
      {
        digitalWrite(leds[i], bitRead(t, i));
      }
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Launch in: ");
      lcd.print(t);
      
      delay(1000);
    }

    lcd.clear();
    lcd.print("LIFTOFF!");

    for (int i = 0; i < 4; i++)
    {
      digitalWrite(leds[i], LOW);
    } 
  
     launched = true;
  }
  delay(100);
}

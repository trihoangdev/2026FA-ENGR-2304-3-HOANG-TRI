// ENGR 2304 Final Project - Pressure Regulation + Rocket Launch Countdown
// Convention: numbers without 0x are binary (0b...). Decimal value in comments.

#include <Wire.h>
#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd(0);

int leds[] = {0b1101, 0b1100, 0b1000, 0b100};   // pins 13, 12, 8, 4
int compressor = 0b111;                          // pin 7
bool launched = false;                           // stops the program after liftoff

void setup()
{
  lcd.begin(0b10000, 0b10);                      // 16 columns, 2 rows
  pinMode(compressor, OUTPUT);
  for (int i = 0; i < 0b100; i++)                // 4 LEDs
  {
    pinMode(leds[i], OUTPUT);
  }
  digitalWrite(compressor, LOW);

  lcd.print("System Starting");
  delay(0b10111011100);                          // 1500 ms
  lcd.clear();
}

void loop()
{
  if (launched)
  {
    return;                                      // already launched: do nothing
  }

  // read the two dials and convert to 0-100 psi
  int target = map(analogRead(A0), 0, 0b1111111111, 0, 0b1100100);  // 1023, 100
  int psi    = map(analogRead(A2), 0, 0b1111111111, 0, 0b1100100);

  // show on LCD
  lcd.setCursor(0, 0);
  lcd.print("Target: ");
  lcd.print(target);
  lcd.print(" psi   ");
  lcd.setCursor(0, 1);
  lcd.print("Now:    ");
  lcd.print(psi);
  lcd.print(" psi   ");

  if (psi < target)
  {
    digitalWrite(compressor, HIGH);              // pressure too low: compressor ON
  }
  else
  {
    digitalWrite(compressor, LOW);               // pressure reached: compressor OFF
    delay(0b1111101000);                         // 1000 ms

    // countdown from 10 to 0 in binary on the LEDs
    for (int t = 0b1010; t >= 0; t--)
    {
      for (int i = 0; i < 0b100; i++)
      {
        digitalWrite(leds[i], bitRead(t, i));
      }
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Launch in: ");
      lcd.print(t);
      delay(0b1111101000);                       // 1000 ms
    }

    lcd.clear();
    lcd.print("LIFTOFF!");

    for (int i = 0; i < 0b100; i++)
    {
      digitalWrite(leds[i], LOW);
    }

    launched = true;
    digitalWrite(compressor, LOW);
  }

  delay(0b1100100);                              // 100 ms
}

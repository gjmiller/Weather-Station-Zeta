#include <LiquidCrystal.h>
#include <DHT.h>

#define DHTPIN 5
#define DHTTYPE DHT22
#define BUTTONPIN 4
#define CONTRASTPIN 6

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
DHT dht(DHTPIN, DHTTYPE);
int buttonState = 0;
float humidity = 0.0;
float temp = 0.0;

void setup()
{
  // Button init
  pinMode(BUTTONPIN, INPUT_PULLUP);
  // DHT init
  dht.begin();
  // LCD init
  lcd.begin(16, 4);
  analogWrite(CONTRASTPIN, 100);
  // Serial init
  Serial.begin(9600);
}

void loop()
{
  if (digitalRead(BUTTONPIN) == LOW)
  {
    if (buttonState == 0)
    {
     buttonState = 1;
    }
    else if (buttonState == 1)
    {
      buttonState = 0;
    }
    Serial.print("Button pressed, buttonState is ");
    Serial.println(buttonState);
    delay(200);
  }
  if (buttonState == 0)
  {
   lcd.clear();
   lcd.print("Temperature:");
   lcd.setCursor(13, 0);
   lcd.print(temp);
  }
  if (buttonState == 1)
  {
   lcd.clear();
   lcd.print("Humidity:");
   lcd.setCursor(10, 0);
   lcd.print(humidity);
  }
  
  humidity = dht.readHumidity();
  temp = dht.readTemperature(true);
}

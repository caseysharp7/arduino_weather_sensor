#include <LiquidCrystal_I2C.h>
#include <NRF24L01_W.h>

NRF24L01_W radio(7, 8);
WeatherReport incoming;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  radio.begin();
  radio.setReceiveAddress("1123D");
  radio.setTransmitAddress("1123C");
  radio.setChannel(49);
	lcd.init(); // initialize the lcd
	lcd.backlight();
}

void loop()
{
	lcd.clear();
  lcd.setCursor(0, 0);
  if(radio.available()){
    incoming = radio.read();
    lcd.print("Temp: ");
    lcd.print(incoming.temperature);
    lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.print("Hum: ");
    lcd.print(incoming.humidity);
    lcd.print("\%, ");
    if(incoming.light){
      lcd.print("day");
    } else{
      lcd.print("night");
    }
  }
	delay(10000);
}

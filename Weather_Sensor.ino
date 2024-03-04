#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <NRF24L01_W.h>

NRF24L01_W radio(7, 8);

DHT weatherSensor(4, DHT11);
const int photo_resist = A2;
int a, b, c;
WeatherReport report;

void setup() {
  radio.begin();
  radio.setReceiveAddress("1123C");
  radio.setTransmitAddress("1123D");
  radio.setChannel(49);
  weatherSensor.begin();
  pinMode(photo_resist, INPUT);
  Serial.begin(9600);
}

void loop() {
  c = analogRead(photo_resist);
  a = weatherSensor.readHumidity();
  b = weatherSensor.readTemperature();
  if(c > 650){
    Serial.println("day");
    report.light = 1;
  } else {
    Serial.println("night");
    report.light = 0;
  }
  Serial.print("Hum: ");
  Serial.println(a);
  Serial.print("Temp: ");
  Serial.println(b);

  report.humidity = a;
  report.temperature = b;

  radio.write(report);

  delay(10000);
}

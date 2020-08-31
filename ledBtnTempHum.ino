#include "DHT.h"

#define DHTTYPE DHT22

const int ledPin = 3;
const int btnPin = 4;
const int dhtPin = 2;

bool showTempBright = true;

DHT dht(dhtPin, DHTTYPE);

void setup() 
{
  Serial.begin(115200);
  Wire.begin();
  
  pinMode(ledPin, OUTPUT);
  pinMode(btnPin, INPUT);

  Serial.println("Start");
  for (int i = 0; i < 255; i++)
  {
    analogWrite(ledPin, i);
    delay(10);
  }

  dht.begin();
}

void loop() 
{
  bool btnPressed = digitalRead(btnPin) == 1 ? false : true;
  
  float temp_hum_val[2] = {0};
  dht.readTempAndHumidity(temp_hum_val);

  int tempBright = (temp_hum_val[1] - 10) / 20 * 255; // 10 - 30 C
  int humBright = (temp_hum_val[0] - 30) / 70 * 255; // 30 - 100 %
  Serial.print("Temperature brightness (0-255): ");
  Serial.println(tempBright);
  Serial.print("Humidity brightness (0-255): ");
  Serial.println(humBright);
  
  Serial.print("Humidity: ");
  Serial.print(temp_hum_val[0]);
  Serial.println(" %");
  Serial.print("Temperature: ");
  Serial.print(temp_hum_val[1]);
  Serial.println(" C");
  Serial.println(" ");

  if (btnPressed)
  {
    showTempBright = showTempBright ? false : true;

    btnPressed = false;
  }

  if (showTempBright)
  {
    analogWrite(ledPin, tempBright);
  }
  else
  {
    analogWrite(ledPin, humBright);
  }
  
  delay(1000);
}

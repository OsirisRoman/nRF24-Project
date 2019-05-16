#include "RF24.h"
#include <DHT.h>

RF24 myRadio (7, 8); //in Mega can use>(48, 49);
byte addresses [][6] ={"0"};

#define DHTPIN 5          // What digital pin we're connected to
// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11

DHT dht(DHTPIN, DHTTYPE);

struct package
{
  int id=1;
  float temperature = 0.0;
  float humidity = 0.0;
  //char text[100] = "Text to be transmitted";
  char text[100] = "ola jasj";
};
typedef struct package Package;
Package data;



void sendSensor()
{
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  
  if (isnan(humidity) || isnan(temperature)) {
    Serial.print("\nFailed to read from DHT sensor!");
    return;
  } else {
    data.id=data.id+1;
    data.temperature=temperature;
    data.humidity=humidity;
    myRadio.write(&data, sizeof(data));
    Serial.print("\nPackage:");
    Serial.print(data.id);
    Serial.print("\n");
    Serial.println(data.temperature);
    Serial.println(data.humidity);
    Serial.println(data.text);
    Serial.println("ola jajs");
  }
}

void setup()
{
  Serial.begin(115200);
  delay(100);
  myRadio.begin();
  myRadio.setChannel(121);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ;
  myRadio.openWritingPipe( addresses[0]);

  dht.begin();
}

void loop()
{
  /*myRadio.write(&data, sizeof(data));
  Serial.print("\nPackage:");
  Serial.print(data.id);
  Serial.print("\n");
  Serial.println(data.temperature);
  Serial.println(data.text);
  Serial.println("ola jajs");
  data.id = data.id + 1;
  data.temperature = data.temperature+0.1;*/

  sendSensor();
  delay(50);
}

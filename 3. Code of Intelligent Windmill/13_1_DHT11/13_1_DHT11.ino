#include <dht11.h>
dht11 DHT11;
#define DHT11PIN 12
 
void setup()
{
  Serial.begin(9600);
}
 
void loop()
{
  int chk = DHT11.read(DHT11PIN);  //Read the value of the DHT11
  Serial.print("Temp : ");
  Serial.print((float)DHT11.temperature);  //Read the temperature value and float is a floating point value.
  Serial.print("C");
  Serial.print("    ");
  Serial.print("RelF: ");
  Serial.print((float)DHT11.humidity);   //Read the humidity value
  Serial.println("%");
  
  delay(2000);
}

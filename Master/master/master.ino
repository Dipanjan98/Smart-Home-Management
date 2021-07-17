//Name:Khosnor,ID:011171065
// Master
const int echoPin = 2; // Echo Pin for Ultrasonic Sensor
const int pingPin = 3; // Trigger Pin for Ultrasonic Sensor

#include <Wire.h>
#include <VirtualWire.h>
#include <VirtualWire_Config.h>
#include <dht.h>
dht DHT; // making objecr of DHT 11 (DHT the objects)
void setup() {
  Serial.begin(9600);
  pinMode(pingPin, OUTPUT); // initialising pin 3 as output
  pinMode(echoPin, INPUT); // initialising pin 2 as input



  Serial.println("****MASTER Monitor*****");
  // Start the I2C Bus as Master
  Wire.begin(); 
}

void loop() {
 
  ////////// Distance measuring ////////////////////
  long duration, inches, meter;
  
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(pingPin, LOW);
  
  duration = pulseIn(echoPin, HIGH); // using pulsin function to determing the total time here
  inches = microsecondsToInches(duration); // calling method
  meter= inches/39.37;
  Serial.print("Distance Measure: ");
  Serial.print(meter);
  Serial.print(" Meter ");
  Serial.println();

  ///////// Temperature Measure /////////
  DHT.read11(13); /// reading the temperature of humidity from pin 13 using DHT
  int temp=DHT.temperature;
  Serial.print("Temperature Measure: ");
  Serial.print(temp);
  Serial.print("Celcius");
  Serial.println();
  Serial.println();

  /////////// Sending Temperature to Slave 1 /////////////////////

  Wire.beginTransmission(9); // transmit to device #9
  Wire.write(temp);              // sends inches 
  Wire.endTransmission();    // stop transmitting

  /////////// Sending Distance to Slave 2/////////////////////

  Wire.beginTransmission(12); // transmit to device #12
  Wire.write(meter);              // sends meter
  Wire.endTransmission();    // stop transmitting
  delay(1000);
}

long microsecondsToInches(long microseconds) // coverting microsec to inches 
{
 return microseconds / 74 / 2;
}

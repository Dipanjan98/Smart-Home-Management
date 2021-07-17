//Name:Khosnor,ID:011171065

void setup() 
{ 
 pinMode(pingPin, OUTPUT); // Sets the trigPin as an Output 12
 pinMode(echoPin, INPUT); // Sets the echoPin as an Input 11
 Serial.begin(9600); // Starts the serial communication 
} 
void loop() {
 
  ////////// Distance measure Code ////////////////////
  long duration, inches, meter;
  
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(pingPin, LOW);
  
  duration = pulseIn(echoPin, HIGH); // using pulsin function to determine total time
  inches = microsecondsToInches(duration); // calling method
  meter= inches/39.37;
  Serial.print("Distance Measure: ");
  Serial.print(meter);
  Serial.print(" Meter ");


  Serial.println();


  Wire.beginTransmission(12); // transmit to device #12
  Wire.write(meter);              // sends meter
  Wire.endTransmission();    // stop transmitting


 
  delay(1000);
}

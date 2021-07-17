//Name:Khosnor,ID:011171065
// Slave 2

#include <Wire.h>
int x=0;


void setup() {
  pinMode(10, OUTPUT); //RED 
  pinMode(9,OUTPUT); //GREEN
  pinMode(8,OUTPUT); //BLUE 
  // Start the I2C Bus as Slave on address 12
  Wire.begin(12); 
  // Attach a function to trigger when something is received.
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  Serial.println("Slave 2 Reading");
}

void receiveEvent(int bytes) {
  x = Wire.read();    // read one character from I2C
}

void loop() {
   Serial.print("Distance Received: ");
   Serial.print(x);
   Serial.println(" Meter");
   Serial.println();

    
   if(x<=4)
   {
      digitalWrite(10, 255);
      digitalWrite(9, 0);
      digitalWrite(8, 0);
   }
    if(x==5)
   {
      digitalWrite(10, 150);
      digitalWrite(9, 0);
      digitalWrite(8, 100);
   }
   if(x==6)
   {
      digitalWrite(10, 100);
      digitalWrite(9, 0);
      digitalWrite(8, 180);
   }
   if(x==7)
   {
      digitalWrite(10, 50);
      digitalWrite(9, 0);
      digitalWrite(8, 200);
   }
   if(x==8 || x>8)
   {
      digitalWrite(10, 0);
      digitalWrite(9, 0);
      digitalWrite(8, 255);
   }
 
 delay(1000);
}

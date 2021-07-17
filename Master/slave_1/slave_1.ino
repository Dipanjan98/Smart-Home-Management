//Name:Khosnor,ID:011171065
// Slave 1

#include <Wire.h>
#include <VirtualWire.h>
int x=0;

#define BPS 8000 // transmission rate (bits per second)

// IDs of the receiver modules [1;255]
#define RECEIVER1_ID 1
#define RECEIVER2_ID 2
#define RECEIVER3_ID 3

#define MESSAGE_LENGTH 3 // packet size in bytes

#define MILLIS_IDLE_BETWEEN_TRANSMISSION 9 // recommended approx. MESSAGE_LENGTH * 8 / BPS * 1,000 * 3


uint8_t outputBuffer[MESSAGE_LENGTH]; // output buffer

void setup() {
  pinMode(4, INPUT); //push button 1
  pinMode(3, INPUT); // push button 2
  pinMode(2, INPUT); // push button 3
  
  
  // Start the I2C Bus as Slave on address 9
  Wire.begin(9); 
  // Attach a function to trigger when something is received here.
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  Serial.println("Slave 1 Reading");

  vw_set_tx_pin(12); // transmitter module data pin
  vw_setup(BPS); // transmission rate
}

void receiveEvent(int bytes) {
  x = Wire.read();    // read one character from I2C
}

void loop() {
 Serial.print("Temperature Received: ");
 Serial.print(x);
 Serial.println(" Celcius");
 Serial.println();

 int button1= digitalRead(4);
 int button2= digitalRead(3);
 int button3= digitalRead(2);
 if(button1 == HIGH)
 {
  
  sendValue(RECEIVER1_ID, x); // send data to receiver 1
 }
 if(button2 == HIGH)
 {
   sendValue(RECEIVER2_ID, x); // send data to receiver 2
 }
 if(button3 == HIGH)
 {
  sendValue(RECEIVER3_ID, x); // send data to receiver 2
 }
 delay(1000);
}


void sendValue(int receiverId, int value) {
  byte* valPtr = (byte*)&value;
  
  // fill output buffer with data
  outputBuffer[0] = (uint8_t)receiverId;
  outputBuffer[1] = (uint8_t) *(valPtr++);
  outputBuffer[2] = (uint8_t) *(valPtr++);
  
  // transmitt data
  vw_send(outputBuffer, MESSAGE_LENGTH);
  vw_wait_tx(); // wait till whole message is gone
  delay(MILLIS_IDLE_BETWEEN_TRANSMISSION); // wait some time  more
}

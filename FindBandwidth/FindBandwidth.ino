/*
  ATmega128RFA1 Dev Board Basic Chat
  by: Jim Lindblom
      SparkFun Electronics
  date: July 3, 2012
  License: Beerware. Feel free to use, reuse, and modify this code
  as you please. If you find it useful, you can buy me a beer.

  This code sets up the ATmega128RFA1's wireless transciever in
  the most basic way possible to serve as a serial gateway.
  Serial into the ATmega128RFA1's UART0 will go out the RF radio.
  Data into the RF radio will go out the MCU's UART0.
*/

#include "RadioFunctions.h"

double sent;
double rec;

void setup()
{
  Serial.begin(9600);  // Start up serial
  Serial1.begin(115200);
  rfBegin(11);  // Initialize ATmega128RFA1 radio on channel 11 (can be 11-26)

  // Send a message to other RF boards on this channel

}

void loop()
{

  if (Serial.available())  // If serial comes in...
  {
    sent = micros();
    rfWrite(Serial.read()); // ...send it out the radio.
  }
  if (rfAvailable())  // If data receievd on radio...
  {
    Serial.println(rfRead());  // ... send it out serial.
    
    rec = micros();
    
    Serial.print("Data sent at: ");
    Serial.println(sent);
    Serial.print("Recieved at: ");
    Serial.println(rec);
    Serial.print("Sends 127 bytes in ");
    Serial.print((rec - sent) / 2);
    Serial.println(" microseconds.");
    Serial.print(1.016 / ((rec - sent) / 2000000));
    Serial.println("Kbits per second");


  }
}

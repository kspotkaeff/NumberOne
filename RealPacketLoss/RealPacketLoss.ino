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

int i = 0;
void setup()
{
  Serial.begin(9600);  // Start up serial
  Serial1.begin(115200);
  rfBegin(11);  // Initialize ATmega128RFA1 radio on channel 11 (can be 11-26)

  // Send a message to other RF boards on this channel
  //  rfPrint("1");
  rfPrint("1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");

}
int counter = 0;
void loop()
{
  if (rfAvailable())  // If data receievd on radio...
  {
    Serial.print(rfRead());  // ... send it out serial.
    i++;
    counter = 0;
  }
  if (!rfAvailable())
  {
    counter++;
    delay(25);
    if (counter > 100) {
      Serial.println();
      Serial.print(i);
      Serial.println("/100 packets recieved");
      while (1) {}
    }
  }

}

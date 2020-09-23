/* 
Combriat 2020
Manager for interrupted capacitive sensing
*/

#include "interruptCapSense.h"


interruptCapSense::interruptCapSense(int _sendPin, const int _samples, unsigned long _timout, unsigned long _delay)
{
  samples = _samples;
  sendPin = _sendPin;
  timout = _timout;
  delay = _delay;
  times = new unsigned long[samples];
  for (int i=0; i<samples;i++) times[i] = 0;
}

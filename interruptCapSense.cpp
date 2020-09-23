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
  pinMode(sendPin, OUTPUT);
  for (int i=0; i<samples;i++) times[i] = 0;
}

interruptCapSense::~interruptCapSense()
{
  delete times;
}


bool interruptCapSense::update()
{
  bool ret = false;
  switch (state)
    {
    case 0:  // initial
      digitalWrite(sendPin, HIGH);
      last_timing = micros();
      ISR_target = 0;
      state +=1;
      break;
      
    case 1:  // waiting for the ISR to fire
      if (ISR_target != 0)
	{
	  times[runner] = ISR_target - last_timing;
	  runner += 1;
	  if (runner == samples) runner = 0;
	  ret = true;
	  state += 1;
	  digitalWrite(sendPin, LOW);
	  last_timing = micros();
	}
      else if (micros() - last_timing > timout)
	{
	  state +=1;
	  digitalWrite(sendPin, LOW);
	  last_timing = micros();
	}
      break;

    case 2:
      if (micros() - last_timing > delay) state = 0;
      break;
      
    }
  return ret;
}

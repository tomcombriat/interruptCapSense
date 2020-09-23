/*
Combriat 2020

A simple example to demonstrate the use of the interruptCapSense library.

As interrupts need to be global, they are defined outside the library (this is a bit hacky, but maybe less than an integrated solution). Thus, one interrupt function has to be define for each sensor, and then linked to it.

Wiring:                      ----------  
                             |         |
   send_pin -------- R ------|  foil   |
                          |  |         |
                          |  ----------  
                          |
                          |
  receive_pin-------------



R should be chosen quite big, and depending on the system and desired range. Values between 1Mohm and 40Mohms should be useful.

This obviously inspired by the CapSense library.

*/

#include <interruptCapSense.h>


#define send_pin PB0  // any digital pin
#define receive_pin PA0  // should be a interrupt compatible pin (digital)

interruptCapSense Sensor(send_pin, 20);
void interrupt()
{
  Sensor.ISR_target = micros();
}



void setup() {
  Serial.begin(250000);
  pinMode(receive_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(receive_pin), interrupt, RISING);

  Sensor.init();  // needed for the sensor to get the first values for the rolling average.

}

void loop() {

  if (Sensor.update())
  {
    Serial.print(Sensor.getCumul());  // if you do not want to deal with floats. Beware of overflows!
    Serial.print(" ");
    Serial.println(Sensor.getAverage());
  }
}

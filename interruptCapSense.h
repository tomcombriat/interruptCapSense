/* 
Combriat 2020
Manager for interrupted capacitive sensing
*/


#ifndef _INTCAPSENSE_
#define _INTCAPSENSE_


class interruptCapSense {
  
 public:
  
  interruptCapSense(int _sendPin, const int _samples = 20, unsigned long _timout = 10 , unsigned long _delay = 1);
  void init();
  volatile unsigned long ISR_target;
  bool update();
  unsigned long getCumul();
  float getAverage();


 private:
  int samples;
  unsigned long *times;
  int runner=0;
  unsigned long last_timing;
  int state = 0;
  int sendPin;
  unsigned long timout, delay;
  



};

#endif

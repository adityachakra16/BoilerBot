#ifndef RcChannel_h
#define RcChannel_h
#include "Arduino.h"



class RcChannel 
{
  public:
    RcChannel();
    int Read(int _pin);
  
};

#endif

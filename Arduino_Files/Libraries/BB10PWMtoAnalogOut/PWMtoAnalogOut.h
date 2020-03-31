#ifndef PWMtoAnalogOut_h
#define PWMtoAnalogOut_h
#include "Arduino.h"



class PWMtoAnalogOut
{
  public:
    PWMtoAnalogOut();
    int Left(int steer_val, int throttle_val, int STEER_CENTER, int THROTTLE_MULTIPLIER, int STEER_MULTIPLIER, float MIN_SPEED, float MAX_SPEED);
	int Right(int steer_val, int throttle_val, int STEER_CENTER, int THROTTLE_MULTIPLIER, int STEER_MULTIPLIER, float MIN_SPEED, float MAX_SPEED);
  
};

#endif

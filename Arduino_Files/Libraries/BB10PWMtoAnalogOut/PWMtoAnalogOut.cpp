/*
 * ReadCh.cpp - Library for reading a pwm signal
 * Created by Brandon Skiles
*/

#include "Arduino.h"
#include "PWMtoAnalogOut.h"

PWMtoAnalogOut::PWMtoAnalogOut()
{
}

int PWMtoAnalogOut::Left(int steer_val, int throttle_val, int STEER_CENTER, int THROTTLE_MULTIPLIER, int STEER_MULTIPLIER, float MIN_SPEED, float MAX_SPEED)
{
  float left_speed = 0;
  //int right_speed = 0;
  ///int speed_arr[2] = {0,0}; //Hold the left speed value in position 0 and the right in position 1
  if((steer_val == 0) || (throttle_val == 0)) {
	  return 0;
  }
  
  if(steer_val < STEER_CENTER) {
    //right_speed = THROTTLE_MULTIPLIER*(throttle_val-1000) + STEER_MULTIPLIER*(STEER_CENTER - steer_val);
    left_speed =  THROTTLE_MULTIPLIER*(throttle_val-1000) - STEER_MULTIPLIER*(STEER_CENTER - steer_val);
  }
  
  else if(steer_val > STEER_CENTER) {
    left_speed = THROTTLE_MULTIPLIER*(throttle_val-1000) + STEER_MULTIPLIER*((STEER_CENTER - steer_val)*-1);
    //right_speed = THROTTLE_MULTIPLIER*(throttle_val-1000) - STEER_MULTIPLIER*((STEER_CENTER - steer_val)*-1);
  }
  else {
    left_speed = THROTTLE_MULTIPLIER*(throttle_val-1000);
	//right_speed = THROTTLE_MULTIPLIER*(throttle_val-1000);
  }
  //Serial.println(left_speed);
  
  if (left_speed > 0) {
	  left_speed = (left_speed * (255.0-MIN_SPEED)/MAX_SPEED) + MIN_SPEED;
  }
  else {
	  left_speed = (left_speed * (255.0-MIN_SPEED)/MAX_SPEED) - MIN_SPEED;
  }
  
  return left_speed;

}

int PWMtoAnalogOut::Right(int steer_val, int throttle_val, int STEER_CENTER, int THROTTLE_MULTIPLIER, int STEER_MULTIPLIER, float MIN_SPEED, float MAX_SPEED)
{
  //int left_speed = 0;
  float right_speed = 0;
  //int speed_arr[2] = {0,0}; //Hold the left speed value in position 0 and the right in position 1
  
  if((steer_val == 0) || (throttle_val == 0)) {
	  return 0;
  }
  
  if(steer_val < STEER_CENTER) {
    right_speed = THROTTLE_MULTIPLIER*(throttle_val-1000) + STEER_MULTIPLIER*(STEER_CENTER - steer_val);
    //left_speed =  THROTTLE_MULTIPLIER*(throttle_val-1000) - STEER_MULTIPLIER*(STEER_CENTER - steer_val);
  }
  
  else if(steer_val > STEER_CENTER) {
    //left_speed = THROTTLE_MULTIPLIER*(throttle_val-1000) + STEER_MULTIPLIER*((STEER_CENTER - steer_val)*-1);
    right_speed = THROTTLE_MULTIPLIER*(throttle_val-1000) - STEER_MULTIPLIER*((STEER_CENTER - steer_val)*-1);
  }
  else {
    //left_speed = THROTTLE_MULTIPLIER*(throttle_val-1000);
	right_speed = THROTTLE_MULTIPLIER*(throttle_val-1000);
  }
  
   if (right_speed > 0) {
	  right_speed = (right_speed * (255.0-MIN_SPEED)/MAX_SPEED) + MIN_SPEED;
  }
  else {
	  right_speed = (right_speed * (255.0-MIN_SPEED)/MAX_SPEED) - MIN_SPEED;
  }
  
  return right_speed;

}


/*
 * ReadCh.cpp - Library for reading a pwm signal
 * Created by Brandon Skiles
*/

#include "Arduino.h"
#include "RcChannel.h"

RcChannel::RcChannel()
{
}

int RcChannel::Read(int _pin)
{
	int time_beg = 0; //Holds the value of the start time
	int time_end = 0; //Holds the value of the end time
	int loop_count = 0; //Counts the number of loop cycles to detect timeout
  
	while(digitalRead(_pin) == LOW) {
		loop_count ++;
		if(loop_count > 3500){ 
		return 0;
		}
	}
	time_beg = micros();
	loop_count = 0;
	while(digitalRead(_pin) == HIGH) {
	loop_count ++;
	if(loop_count > 3500){ 
	  return 0;
		} 
	}
	time_end = micros();
	return (time_end - time_beg);
}




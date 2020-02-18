This package is used for transmitting and receiving position data to and from the ardiuno mega 2560, ultimately for 
motor control.

This node is named motor_command_fb and publishes a Int8MultiArray of two elements to motor_speed_command topic. The first element is the left wheel speed and the second element is the right wheel speed. This node also subscribes to motor_speed_fb which is published by the mega 2560. 

Package       : motor_command_fb_pkg
Launch file   : motor_command_fb.launch
Node 	      : motor_comand_fb
Programs      : motor_command_fb.py

Publishes to  : motor_speed_command
Subscribes to : motor_speed_fb


To use this package 
	$ roslaunch motor_command_fb_pkg motor_command_fb.launch
	In another terminal run $ rosrun rosserial_python serial_node.py /dev/<Serial_Port>




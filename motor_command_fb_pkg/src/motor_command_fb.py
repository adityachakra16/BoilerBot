#! /usr/bin/env python

import rospy
from std_msgs.msg import Int8MultiArray
def callback(motor_fb):
	print(motor_fb.data)
		

rospy.init_node('arduino_tx')
pub = rospy.Publisher('/motor_speed_command', Int8MultiArray, queue_size=1)
sub = rospy.Subscriber('/motor_speed_fb',Int8MultiArray, callback)

motor_control_msg = Int8MultiArray()
motor_control_msg.data = [0,0]
rate = rospy.Rate(1)
count = 0
while not rospy.is_shutdown():
    if count % 2 == 0:
        motor_control_msg.data[1] = 2
        motor_control_msg.data[0] = count
    else: 
        motor_control_msg.data[1] = 1
        motor_control_msg.data[0] = count
    count += 1
    pub.publish(motor_control_msg)
    rate.sleep()

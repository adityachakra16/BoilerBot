#! /usr/bin/env python
import rospy
from sensor_msgs.msg import LaserScan

def callback(msg):
    print (msg.range_min)

def callback2(scan):
    angle_scan = 15
    scan_start = 180 - angle_scan
    scan_end = 180 + angle_scan
    threshold_distance = 0.3
    obstacle_existence = 'no'
    obstacle_count = 0



    angle_scan = 10
    scan_start = 180 - angle_scan
    scan_end = 180 + angle_scan
    threshold_distance = 100
    obstacle_existence = 'no'
    for i in range(scan_start, scan_end):
        if scan.ranges[i] < threshold_distance and scan.ranges[i] > 0.01:
            obstacle_existence = 'yes'
        print  ("In for")
    print obstacle_existence


    '''
    if self.state == 'checking_obstacle':
        angle_scan = 15
        scan_start = 270 - angle_scan
        scan_end = 270 + angle_scan
        threshold_distance = 0.5
        obstacle_existence = 'no'
        for i in range(scan_start, scan_end):
            if scan.ranges[i] < threshold_distance and scan.ranges[i] > 0.01:
                obstacle_existence = 'yes'
                print 'obstacle in', i
        if obstacle_existence == 'no':
            message = "parking_lot_detected"
            self._pub1.publish(message)
            self.state = 'parking'
        elif obstacle_existence == 'yes':
            if self.parking_lot_num == 1:
                self.parking_lot_num = 2
                self.state = 'setting_parking_position'
            elif self.parking_lot_num == 2:
                self.state = 'parking_end'
                '''


rospy.init_node('scan_values')
sub = rospy.Subscriber('/mybot/laser/scan', LaserScan, callback2)

rospy.spin()

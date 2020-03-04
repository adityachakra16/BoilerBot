# BoilerBot

An autonomous vehicle built by Purdue University students

Setup:

1. Clone integration branch inside 'src/' directory in your catkin workspace
2. Run: 'catkin_make'
3. Run: 'source devel/setup.bash'
4. Launch: roslaunch boilerbot_gazebo_integ qualification.launch
   - This should launch the Gazebo simulation environment.
5. Run: bash run_rviz.sh
   - This should open the Rviz GUI
6. Launch: roslaunch boilerbot_nav_integ gmapping_demo.launch
   - This should start the simultaneous mapping (gmapping)
7. Go on Rviz, click the 'Add' button (bottom left) and add RobotModel, Map and LaserScan
8. Click the LaserScan dropdown. Change topic to 'mybot/laser/scan'. Change size to 0.1.
   - At this point, you should be seeing red lines on the Rviz environment.
9. Click the Map dropdown. Change topic to 'map/'.
   - This should add lines to the Rviz environment connecting the robot and the obstacles.
10. Run: python teleop_twist_keyboard.py 
   - This will enable you to control the robot with keyboard. The map should get denser as the robot moves. 
  

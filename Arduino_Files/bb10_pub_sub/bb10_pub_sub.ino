/*
 * This will subscribe to the notor_speed_command topic and publish back on the motor_speed_fb topic
 * Note: Do not try to use serial.print.
 * Note: Must use "rosrun rosserial_python serial_node.py /dev/ttyACM0" on ros to enable rosserial comms. 
 *       Replace ACM0 with the specific serial port. 
 *
 */
#include <ros.h>                      //Must include this header
#include <std_msgs/Int8MultiArray.h>  // ^
int8_t motor_fb_array[2] = {0,0};     //The array to hold the values to be sent back on ROS topic motor_speed_fb
ros::NodeHandle  nh;                  //Enable the node handle

void messageCb( const std_msgs::Int8MultiArray& speed_msg){  //This is the callback loop, it will get called whenever subscriber receives a message
  
  if((speed_msg.data[0] % 10) == 0) //This can be changed, it is just a random test to ensure the values are being received correctly.
  {
    digitalWrite(13, HIGH);         // ^
  }
  else                              // ^
  { 
    digitalWrite(13,LOW);           // ^
  }
  motor_fb_array[0] = speed_msg.data[0]; //Assigns the first element of the motor feedback array.
  motor_fb_array[1] = speed_msg.data[1]; //Assigns the second element of the motor feedback array.
}

std_msgs::Int8MultiArray fb_msg;                //Enable the publisher             
ros::Publisher pub("motor_speed_fb", &fb_msg);  //Publish fb_msg to "motor_speed_fb topic
ros::Subscriber<std_msgs::Int8MultiArray> sub("motor_speed_command", messageCb);  //Enable the subscriber

void setup()
{
  pinMode(13, OUTPUT);       //Just for testing
  fb_msg.data_length = 2;    //Set the number of data in the fb_msg array    
  nh.initNode();             //Initialize the node
  nh.subscribe(sub);         //Subscribe to motor_speed_command
  nh.advertise(pub);         //Publish to motor_speed_fb
}

void loop()
{
  nh.spinOnce();               //Handles all of the ros required commands
  fb_msg.data = motor_fb_array;//
  pub.publish( &fb_msg );      //Publish fb_msg
  delay(1000);                 //Delay, It seems to work better if this loop is runnung at the same rate as rospy.rate()//Initialize the node
}

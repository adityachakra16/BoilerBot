#define EXIT_FAILURE 0
#define EXIT_SUCCESS 1
#define MOTOR1_CW 1
#define MOTOR2_CW 0

const int FR1_pin = 2;
const int SV1_pin = 3;
const int PG1_pin = 4;
const int FR2_pin = 5;
const int SV2_pin = 6;
const int PG2_pin = 7;
const int THROTTLE_CH_PIN =11;
const int STEER_CH_PIN = 10;

const int STEER_CENTER = 1500;
const int THROTTLE_CENTER = 1500;

const int STEER_MULTIPLIER = 1;
const int THROTTLE_MULTIPLIER = 2;
const int MAX_SPEED = THROTTLE_MULTIPLIER*1000 + STEER_MULTIPLIER*500;
const int MIN_SPEED = 90;

void setup() {
  
  Serial.begin(9600);
  pinMode(FR1_pin, INPUT);
  pinMode(PG1_pin, INPUT);
  pinMode(SV1_pin, OUTPUT); 
  pinMode(THROTTLE_CH_PIN, INPUT);
  pinMode(STEER_CH_PIN, INPUT);
  Serial.print("MAX_SPEED = ");
  Serial.println(MAX_SPEED);
}

void loop() {
  float steer_ch_val = 0;
  float throttle_ch_val = 0;
  int right_speed = 0;
  int left_speed = 0;
  
  steer_ch_val = _read_steer_ch();
  throttle_ch_val = _read_throttle_ch();
  if((throttle_ch_val == EXIT_FAILURE) || (steer_ch_val == EXIT_FAILURE)) {
    _fail_mode();
  }
  else {
    left_speed = _get_left_speed(steer_ch_val, throttle_ch_val);
    right_speed = _get_right_speed(steer_ch_val, throttle_ch_val);
    /*Serial.print("LEFT_SPEED = ");
    Serial.println(left_speed);
    Serial.print("RIGHT_SPEED = ");
    Serial.println(right_speed);
    Serial.println();*/
    /*Serial.print("STEER_CH = ");
    Serial.println(steer_ch_val);
    Serial.print("THROTTLR_CH = ");
    Serial.println(throttle_ch_val);
    Serial.println();*/
    //delay(1000);
    _motor_write(left_speed, right_speed);
    
  }
  
    
}


//--------------------------------------Helper Functions------------------------------------//

int _get_left_speed(int steer_val, int throttle_val) {
  int left_speed = 0;
  if(steer_val < STEER_CENTER) {
    left_speed = left_speed + STEER_MULTIPLIER*(STEER_CENTER - steer_val);
    left_speed = left_speed + THROTTLE_MULTIPLIER*(throttle_val-1000);
  }
  else {
    left_speed = THROTTLE_MULTIPLIER*(throttle_val-1000);
  }
  return left_speed;
}

int _get_right_speed(int steer_val, int throttle_val) {
  int right_speed = 0;
  if(steer_val > STEER_CENTER) {
    right_speed = right_speed + STEER_MULTIPLIER*((STEER_CENTER - steer_val)*-1);
    right_speed = right_speed + THROTTLE_MULTIPLIER*(throttle_val-1000);
  }
  else {
    right_speed = THROTTLE_MULTIPLIER*(throttle_val-1000);
  }
  return right_speed;
}





//---------------------------------Read Channel Functions------------------------------------//
float _read_steer_ch() {
  int time_beg = 0; //Holds the value of the start time
  int time_end = 0; //Holds the value of the end time
  int loop_count = 0; //Counts the number of loop cycles to detect timeout
  
  while(digitalRead(STEER_CH_PIN) == LOW) {
    loop_count ++;
    if(loop_count > 3500){ 
      return EXIT_FAILURE;
    }
  }
  time_beg = micros();
  loop_count = 0;
  while(digitalRead(STEER_CH_PIN) == HIGH) {
    loop_count ++;
    if(loop_count > 3500){ 
      return EXIT_FAILURE;
    } 
  }
  time_end = micros();
  return (time_end - time_beg);
}
//--------------------------------------------------------------------------
float _read_throttle_ch() {
  int time_beg = 0; //Holds the value of the start time
  int time_end = 0; //Holds the value of the end time
  int loop_count = 0; //Counts the number of loop cycles to detect timeout
  
  while(digitalRead(THROTTLE_CH_PIN) == LOW) {
    loop_count ++;
    if(loop_count > 3500){ 
      return EXIT_FAILURE;
    }
  }
  time_beg = micros();
  loop_count = 0;
  while(digitalRead(THROTTLE_CH_PIN) == HIGH) {
    loop_count ++;
    if(loop_count > 3500){ 
      return EXIT_FAILURE;
    }
  }
  time_end = micros();
  return (time_end - time_beg);
}



void _fail_mode() {
  Serial.println("Epic_Failure");
  analogWrite(SV1_pin, LOW);
  analogWrite(SV2_pin, LOW);
}
//---------------------------------------------------------------------------------------------//

void _motor_write(float left_speed, float right_speed) {
  float mapped_left_speed = 0;
  float mapped_right_speed = 0;

  mapped_left_speed = left_speed*255/MAX_SPEED;
  mapped_right_speed =  right_speed*255.0/MAX_SPEED;
  
  if(mapped_left_speed < MIN_SPEED) {
    mapped_left_speed = 0;
  }
  if(mapped_right_speed < MIN_SPEED) {
    mapped_right_speed = 0;
  }
    
  digitalWrite(FR1_pin, MOTOR1_CW);
  digitalWrite(FR2_pin, !MOTOR2_CW);
  analogWrite(SV1_pin, mapped_left_speed);
  analogWrite(SV2_pin, mapped_right_speed);
  /*Serial.print("MOTOR1 Speed has been written as: ");
  Serial.println(mapped_left_speed);
  Serial.print("MOTOR2 Speed has been written as: ");
  Serial.println(mapped_right_speed);
  Serial.println();*/
}


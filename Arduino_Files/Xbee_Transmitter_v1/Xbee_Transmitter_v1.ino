/* 	~ Simple Arduino - xBee Transmitter sketch ~
	Read an analog value from potentiometer, then convert it to PWM and finally send it through serial port to xBee.
	The xBee serial module will send it to another xBee (resiver) and an Arduino will turn on (fade) an LED.
	The sending message starts with '<' and closes with '>' symbol. 
	Dev: Michalis Vasilakis // Date:2/3/2016 // Info: www.ardumotive.com // Licence: CC BY-NC-SA                    */
//Constants: 

const int potPin = A0; //Pot at Arduino A0 pin 

//Variables:

int value ; //Value from pot



void setup() {
        //Start the serial communication
	Serial.begin(9600); //Baud rate must be the same as is on xBee module
}

void loop() {
	Serial.print('<'); 	//Starting symbol
 	Serial.print(300);//Value from 0 to 255
	Serial.println('>');//Ending symbol
}

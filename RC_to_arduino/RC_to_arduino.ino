//This sketch takes input from a T6L RC Transmitter through a Futaba R3106GF Reciever. It prints the output and passes it to servo outputs to a rudder servo and two ESCs.

//Left Stick U/D is RC channel 3 (throttle)
//Left Stick L/R is RC channel 4 (rudder)
//Right Stick U/D is RC channel 2 (elevator) 
//Right Stick L/R is RC channel 1 (aileron)
//Switch is RC channel 5;
//Dial is RC channel 6;


#include <Servo.h>

int LeftMotor_in = 3;
int RightMotor_in = 2;
int Rudder_in = 4;

int LeftMotor_out = 7;
int RightMotor_out = 8;
int Rudder_out = 9;

Servo LeftMotor;
Servo RightMotor;
Servo Rudder;



void setup() {
  
  pinMode(LeftMotor_in, INPUT);
  pinMode(RightMotor_in, INPUT);
  pinMode(Rudder_in, INPUT);

  LeftMotor.attach(LeftMotor_out);
  RightMotor.attach(RightMotor_out);
  Rudder.attach(Rudder_out);
  
  Serial.begin(9600);
}

void loop() {
  
  int LeftSignal_in = pulseIn(LeftMotor_in, HIGH);
  int RightSignal_in = pulseIn(RightMotor_in, HIGH);
  int RudderSignal_in = pulseIn(Rudder_in, HIGH);

  int LeftSignal_out = LeftSignal_in;

  int RightSignal_out = RightSignal_in;

  //Set outputs so both motors are controlled by the left throttle stick
    
  int RudderSignal_out = RudderSignal_in;

  LeftMotor.writeMicroseconds(LeftSignal_out);
  RightMotor.writeMicroseconds(RightSignal_out);
  Rudder.writeMicroseconds(RudderSignal_out);
  
/*Serial.println("Reciever Input: Left  Right Rudder");
Serial.print("                ");
Serial.print(LeftSignal_in);
Serial.print(" | ");
Serial.print(RightSignal_in);
Serial.print(" | ");
Serial.println(RudderSignal_in);

Serial.println("Arduino Output: Left  Right Rudder");
Serial.print("                 ");
*/
Serial.print(LeftSignal_out);
Serial.print(" | ");
Serial.print(RightSignal_out);
Serial.print(" | ");
Serial.println(RudderSignal_out);

delay(50);

}

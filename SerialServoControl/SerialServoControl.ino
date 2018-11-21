#include <Servo.h>

const byte numChars = 32;
char receivedChars[numChars]; // an array to store the received data
boolean newData = false;
String InputChar;

Servo LeftMotor;
Servo RightMotor;
Servo Rudder;

int LeftMotor_in = 3;
int RightMotor_in = 2;
int Rudder_in = 4;
int Take_Control = 5;

int LeftMotor_out = 7;
int RightMotor_out = 8;
int Rudder_out = 9;

int led_pin = 13;

void setup() {
 pinMode(led_pin, OUTPUT);
 LeftMotor.attach(LeftMotor_out);
 RightMotor.attach(RightMotor_out);
 Rudder.attach(Rudder_out);
 
 Serial.begin(9600);
 delay(1000);
 Serial.println("<Orders to the Helm?>");

}

void loop() {
 recvWithEndMarker();
 showNewData();
 useData();

}

void recvWithEndMarker() {
 static byte ndx = 0;
 char endMarker = '\r';
 char rc;
 
 while (Serial.available() > 0 && newData == false) {
 rc = Serial.read();

 if (rc != endMarker) {
 receivedChars[ndx] = rc;
 ndx++;
 if (ndx >= numChars) {
 ndx = numChars - 1;
 }
 }
 else {
 receivedChars[ndx] = '\0'; // terminate the string
 ndx = 0;
 newData = true;
 }
 }
}

void showNewData() {
 if (newData == true) {
 InputChar = String(receivedChars);
 Serial.print(receivedChars);
 Serial.println(", Aye."); 
 newData = false;
 }
}

void useData() {
 
 if (InputChar == "On") {
  digitalWrite(led_pin, HIGH);
 }
 else if (InputChar == "Off") {
  digitalWrite(led_pin, LOW);
 }  
 else if (InputChar == "Left full rudder") {
  Rudder.write(150);
  Serial.println("Conning Officer, my rudder is left 30 degrees, no ordered course given.");
 }
 else if (InputChar == "Right full rudder") {
  Rudder.write(30);
  Serial.println("Conning Officer, my rudder is right 30 degrees, no ordered course given.");
 }
 else if (InputChar == "Rudder amidships") {
  Rudder.write(90);
  Serial.println("Conning Officer, my rudder is amidships, no ordered course given.");
 }
 else if (InputChar == "Handshake") {
  Handshake();
 }
 else if (InputChar == "Remote Control") {
  RemoteControl();
 }
 else if (InputChar = "All stop") {
  LeftMotor.writeMicroseconds(1535), RightMotor.writeMicroseconds(1535);
 }
 else {
 Serial.println("Orders to the Helm?");
 }
 
 if (InputChar != "Remote Control") {
  InputChar = "null";
 }

 
}

void Handshake (){
  //1000 microseconds fwd, 2000 microsecond aft, 1555 off  LeftMotor.writeMicroseconds(1100), RightMotor.writeMicroseconds(1950);
  LeftMotor.writeMicroseconds(1950), RightMotor.writeMicroseconds(1100);
  delay(1000);
  LeftMotor.writeMicroseconds(1535), RightMotor.writeMicroseconds(1535);
  delay(1000);
  LeftMotor.writeMicroseconds(1100), RightMotor.writeMicroseconds(1950);
  delay(1000);
  LeftMotor.writeMicroseconds(1550), RightMotor.writeMicroseconds(1550);
  delay(1000);
  Rudder.write(90);
  delay(1000);
  Rudder.write(15); //Right full
  delay(2000);
  Rudder.write(90);
  delay(2000);
  Rudder.write(165); //Left Full
  delay(2000);
  Rudder.write(90);
  Serial.println("Handshake complete.");
}

void RemoteControl(){
  int LeftSignal_in = pulseIn(LeftMotor_in, HIGH);
  int RightSignal_in = pulseIn(RightMotor_in, HIGH);
  int RudderSignal_in = pulseIn(Rudder_in, HIGH);

  LeftMotor.writeMicroseconds(LeftSignal_in);
  RightMotor.writeMicroseconds(RightSignal_in);
  Rudder.writeMicroseconds(RudderSignal_in);
}

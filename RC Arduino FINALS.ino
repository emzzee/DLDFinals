#include <AFMotor.h>
#include <SoftwareSerial.h>
SoftwareSerial BT_Serial(0, 1); // RX, TX


AF_DCMotor motor1(3);
AF_DCMotor motor2(2);
AF_DCMotor motor3(4);
AF_DCMotor motor4(1);


#define R_S A0 //ir sensor Right
#define L_S A2 //ir sensor Left

int bt_data; // variable to receive data from the serial port  
int mode=0;
int Speed = 255;

void setup() {

  // turn on motor #2
  motor1.setSpeed(255);
  motor1.run(RELEASE);
  motor2.setSpeed(255);
  motor2.run(RELEASE);
  motor3.setSpeed(255);
  motor3.run(RELEASE);
  motor4.setSpeed(255);
  motor4.run(RELEASE);
  pinMode(R_S, INPUT); // declare if sensor as input  
  pinMode(L_S, INPUT); // declare ir sensor as input
Serial.begin(9600); // start serial communication at 9600bps
BT_Serial.begin(9600); 
delay(500);

}
void loop(){

if(BT_Serial.available() > 0){  //if some date is sent, reads it and saves in state     
bt_data = BT_Serial.read();      
if(bt_data > 20){Speed = bt_data;}      
}

     if(bt_data == 8){mode=1; Speed=130;} //Auto Line Follower Command  
else if(bt_data == 9){mode=0; Stop();}    //Manual Android Application Control Command

if(mode==0){     
   if(bt_data == 1){forward(); }  // if the bt_data is '1' the DC motor will go forward
else if(bt_data == 2){backward();}  // if the bt_data is '2' the motor will Reverse
else if(bt_data == 3){turnLeft();}  // if the bt_data is '3' the motor will turn left
else if(bt_data == 4){turnRight();} // if the bt_data is '4' the motor will turn right
else if(bt_data == 5){Stop(); }     // if the bt_data '5' the motor will Stop
}else{    

if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 0)){forward();}
if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 0)){turnRight();}
if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 1)){turnLeft();}
if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 1)){Stop();} 
delay(10);
}
}

void forward(){  //forword
motor1.setSpeed(255);
motor1.run(FORWARD);
motor2.setSpeed(255);
motor2.run(FORWARD);
motor3.setSpeed(255);
motor3.run(FORWARD);
motor4.setSpeed(255);
motor4.run(FORWARD);
}


void turnRight(){ //turnRight
motor1.setSpeed(255);
motor1.run(FORWARD);
motor2.setSpeed(255);
motor2.run(BACKWARD);
motor3.setSpeed(255);
motor3.run(FORWARD);
motor4.setSpeed(255);
motor4.run(BACKWARD);


}


void turnLeft(){ //turnLeft
motor1.setSpeed(255);
motor1.run(BACKWARD);
motor2.setSpeed(255);
motor2.run(FORWARD);
motor3.setSpeed(255);
motor3.run(BACKWARD);
motor4.setSpeed(255);
motor4.run(FORWARD);


}


void backward(){ //backward
motor1.setSpeed(255);
motor1.run(BACKWARD);
motor2.setSpeed(255);
motor2.run(BACKWARD);
motor3.setSpeed(255);
motor3.run(BACKWARD);
motor4.setSpeed(255);
motor4.run(BACKWARD);
}

void Stop(){ //stop
motor1.setSpeed(0);
motor1.run(RELEASE);
motor2.setSpeed(0);
motor2.run(RELEASE);
motor3.setSpeed(0);
motor3.run(RELEASE);
motor4.setSpeed(0);
motor4.run(RELEASE);
}


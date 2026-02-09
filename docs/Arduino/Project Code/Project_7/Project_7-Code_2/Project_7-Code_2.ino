#include <Servo.h>  //add Servo library files
Servo myservo1;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;
Servo myservo4;
int pos1=90, pos2=60, pos3=130, pos4=0;  // define the variables of 4 Servo angle and assign initial values(posture angle values of boot-up)
char val;


void setup()
{
   //posture of boot-up
  myservo1.write(pos1);  
  myservo2.write(pos2);
  myservo3.write(pos3);
  myservo4.write(pos4);
  delay(1500);

  Serial.begin(9600); //  set baud rate to 9600
}

void loop() 
{
  myservo1.attach(A1);  //set control pin of servo1 to A1
  myservo2.attach(A0);  //set control pin of servo2 to A0
  myservo3.attach(8);   //set control pin of servo3 to D8
  myservo4.attach(9);   //set control pin of servo4 to D9

  if(Serial.available())   //determine if data is received
  {
    val=Serial.read();    //read the received data
    Serial.println(val);
  }
  switch(val)   
    {
      case 'L':  arm_open();  break;   //claw opens
      case 'R':  arm_close();  break;   //claw closes
      case 'F':  left_f();  break;   //left servo swings forward
      case 'B':  left_b();  break;   //left servo swings back ward
      case 'f':  right_f();  break;   //right servo stretches out
      case 'b':  right_b();  break;   //right servo draws back
      case 'l':  T_left();  break;  //base servo turns left
      case 'r':  T_right();  break;  //base servo turns right
    }
}
//**************************************************
//turn left
void T_left()
{
    pos1=pos1+1;
    myservo1.write(pos1);
    delay(5);
    if(pos1>180)
    {
      pos1=180;
    }
}
//turn right
void T_right()
{
    pos1=pos1-1;
    myservo1.write(pos1);
    delay(5);
    if(pos1<1)
    {
      pos1=1;
    }
}
//********************************************
//claw closes
void arm_close()
{
      pos4=pos4-1;
      Serial.println(pos4);
      myservo4.write(pos4);
      delay(5);
      if(pos4<0)
      {
        pos4=0;
      }
}
//claw opens
void arm_open()
{
    pos4=pos4+1;
      Serial.println(pos4);
      myservo4.write(pos4);
      delay(5);
      if(pos4>108)
      {
        pos4=108;
      }
}

//******************************************
//left servo forward
void left_f()
{
    pos2=pos2-1;
    myservo2.write(pos2);
    delay(5);
    if(pos2<0)
    {
      pos2=0;
    }
}
//left servo backward
void left_b()
{
    pos2=pos2+1;
    myservo2.write(pos2);
    delay(5);
    if(pos2>180)
    {
      pos2=180;
    }
}

//***************************************
//right servo forward
void right_f()
{
  pos3=pos3+1;
    myservo3.write(pos3);
    delay(5);
    if(pos3>180)
    {
      pos3=180;
    }
}
//right servo backward
void right_b()
{
  pos3=pos3-1;
    myservo3.write(pos3);
    delay(5);
    if(pos3<35)
    {
      pos3=35;
    }
}

#include <Servo.h>  //add servo library file
Servo myservo1;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;
Servo myservo4;  
int pos1=90, pos2=60, pos3=130, pos4=0;  // define the variable of 4 servo angle and assign the initial value( that is the boot posture angle value)

const int right_X = A2; //define rightX pin to A2 
const int right_Y = A5; //define rightY pin to A3 
const int right_key = 7; //define the pin of right key to 7（the value of Z）

const int left_X = A3; //define rightX pin to A3
const int left_Y = A4;  //define rightX pin to A4
const int left_key = 6; //define the pin of right key to 6（the value of Z）

int x1,y1,z1;  //define variable for storing the read value of Joystick
 int x2,y2,z2;
int s1,s2,s3,s4; //for saving the read angle value of servo
void setup() 
{
  myservo1.attach(A1);  //set control pin of Servo1 to A1
  myservo2.attach(A0);  //set control pin of Servo2 to A0
  myservo3.attach(8);   //set control pin of Servo3 to D6
  myservo4.attach(9);   //set control pin of Servo4 to D9

  //posture of boot-up
  myservo1.write(pos1);  
  delay(1000);
  myservo2.write(pos2);
  myservo3.write(pos3);
  myservo4.write(pos4);
  delay(1500);
    
  
  pinMode(right_key, INPUT);   //set left and right keys to input
  pinMode(left_key, INPUT);
  //Serial.begin(115200); // set baud rate to 115200
}

void loop() 
{
  x1 = analogRead(right_X); //read value of right X
  y1 = analogRead(right_Y);  //read value of right Y
  z1 = digitalRead(right_key);  ///read value of right Z
  
  x2 = analogRead(left_X);  //read value of left X
  y2 = analogRead(left_Y);  //read value of left Y
  z2 = digitalRead(left_key);  //read value of left Z
  //delay(5);  //reduce speed overall
  if(z1==1)  //determine if the right key of Joystick is pressed
  {
    delay(10);  //delay for eliminating shake 

    if(z1==1)    // judge again if the right key is pressed
    {
      s1=myservo1.read();  //read the current angle value of Servos
      s2=myservo2.read();
      s3=myservo3.read();
      s4=myservo4.read();
    }
  }
  if(z2==1) //determine if left key is pressed
  {
    delay(10);
    if(z2==1)
    {
        pos1=myservo1.read();  //memorize angle values of 4 servos
        pos2=myservo2.read();
        pos3=myservo3.read();
        pos4=myservo4.read();

        if(pos1<s1)  // if angle of servo 1 is smaller than variable s1 value
        {
          while(pos1<s1)  //while loops，rotate the servo to the position of the value stored in the array
          {
            myservo1.write(pos1); //Servo1 operates the motion
            pos1++;  //pos1 plus 1
            delay(5); //delay for 5ms to control Servo rotation speed          
}   
        }
        else  //if angle of servo 1 is greater than the value stored in array 1.
        {
          while(pos1>s1)     //while loop,rotate the servo to the position of the value stored in the array.
          {
            myservo1.write(pos1);  //Servo1 operates the motion
            pos1--;     //pos1 subtracts 1
            delay(5);   //delay for 5ms，controlling the rotation speed of servo

          }
        }
      //*************************************************  
      //the explanation is the same as servo 1 
        if(pos2<s2)
        {
          while(pos2<s2)
          {
            myservo2.write(pos2);
            pos2++;
            delay(5);
          }
        }
        else
        {
          while(pos2>s2)
          {
            myservo2.write(pos2);
            pos2--;
            delay(5);
          }
        }
     //*************************************************  
      //the explanation is the same as servo 1 
        if(pos3<s3)
        {
          while(pos3<s3)
          {
            myservo3.write(pos3);
            pos3++;
            delay(5);
          }
        }
        else
        {
          while(pos3>s3)
          {
            myservo3.write(pos3);
            pos3--;
            delay(5);
          }
        }
      //*************************************************  
      //the explanation is the same as servo 1 
        if(pos4<s4)
        {
          while(pos4<s4)
          {
            myservo4.write(pos4);
            pos4++;
            delay(5);
          }
        }
        else
        {
          while(pos4>s4)
          {
            myservo4.write(pos4);
            pos4--;
            delay(5);
          }
        }
        
    }
  }
  
  //claw
  zhuazi();
  //rotate
  zhuandong();
  //right Servo
  right_ser();
  //left Servo
  left_ser();
}


//claw
void zhuazi()
{
    //claw
  if(x2<50) //if push the left joystick to the right
  {
      pos4=pos4-1;  //current angle of servo 4 subtracts 2（change the value you subtract, thus change the closed speed of claw）
      //Serial.println(pos4);
      myservo4.write(pos4);  //Servo4 operates the action, claw is gradually closed
      delay(5);
      if(pos4<0)  //determine if the value of pos4 reduces to 0
      {            //（change value according to real situation) 
        pos4=0;   //don’t stop until reduce to 37
      }
   }
  if(x2>1000) ////if push left rocker to left side
  {
      pos4=pos4+2; //current angle of servo 4 plus 2（change the value you plus, thus change the open speed of claw）
      //Serial.println(pos4);
      myservo4.write(pos4); //Servo4 operates the motion, the claw gradually opens.
      delay(5);
      if(pos4>110)  //limit the largest angle when opening
      {
        pos4=110;
      }
  }
}
//******************************************************
 //rotate
void zhuandong()
{
  if(x1<50)  // if push the right joystick to the right 

  {
    pos1=pos1-1;  //pos1 subtracts 1
    myservo1.write(pos1);  //Servo1 operates the motion, the arm turns right
    delay(5);
    if(pos1<1)   //limit the angle when turning right
    {
      pos1=1;
    }
  }
  if(x1>1000)  //if push the right joystick to the left
  {
    pos1=pos1+1;  //pos1 plus 1
    myservo1.write(pos1);  //robot arm turns left
    delay(5);
    if(pos1>180)  // limit the angle when turning left 
    {
      pos1=180;
    }
  }
}

//**********************************************************/
//right Servo
void right_ser()
{
    if(y1<50) //if push the right joystick backward 
  {
    pos3=pos3-1;
    myservo3.write(pos3); //the joystick of right Servo swings back
    delay(5);
    if(pos3<0)  //limit angle
    {
      pos3=0;
    }
  }
  if(y1>1000)  //if push right joystick forward
  {
    pos3=pos3+1;  
    myservo3.write(pos3);  //the joystick of right Servo swings forward
    delay(5);
    if(pos3>180)  //limit descent angle
    {
      pos3=180;
    }
  }
}

//*************************************************************/
//left Servo
void left_ser()
{
  if(y2<50)  //if push the left joystick backward 
  {
    pos2=pos2+1;
myservo2.write(pos2);  //the joystick of left Servo swings backward
    delay(5);
if(pos2>180)   //limit  the retracted angle   
 {
      pos2=180;
    }
  }
  
  if(y2>1000)  //if push the left joystick forward
  {
    pos2=pos2-1;
    myservo2.write(pos2);  //the joystick of left Servo swings forward
    delay(5);
    if(pos2<35)  //limit angle when swinging forward
    {
      pos2=35;
    }
  }
  
}

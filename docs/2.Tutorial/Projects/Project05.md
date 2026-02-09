## Project 5: Dual-Joystick Controlling

**Description:**

In the previous section, we have introduced how to use 4 Servos to control the robot arm. Next, combine those two experiments. Use two Joystick modules to control 4DOF robot arm realize different motions.

At first, set the boot posture. The Joystick control is shown as below table.

| **Right Joystick** | **Servo**                                                    | **Left Joystick** | **Servo**                                                    |
| :----------------: | :----------------------------------------------------------- | ----------------- | ------------------------------------------------------------ |
|       X1<50       | Servo 1 gradually reduces to 0° (push the right joystick to the right, the servo that controls the arm rotation turns right, and stops at 0° ) | X2<50            | Servo 4 gradually reduces to 0° (push the left joystick to the right, the claw is closes) |
|      X1>1000      | Servo 1 gradually increases to 180° (push the right joystick to the left, the servo that controls the arm rotation turns left, and stops at 180° ) | X2>1000          | Servo 4 gradually increases to 110° (push the left joystick to the left, the claw opens) |
|      Y1>1000      | Servo 3 gradually increases to 180° ( that is, right joystick stretches out, the upper arm stretches out) | Y2>1000          | Servo2 gradually reduces to 35° ( that is, left joystick stretches out and the lower arm lifts up) |
|       Y1<50       | Servo 2 gradually reduces to 0° ( that is,the right joystick draws back, the upper arm draws back) | Y2<50            | Servo 2 gradually increases to 180° ( that is, left joystick draws back ,the lower arm decrease) |

**Connection Diagram**

![](media/c19bcdd5f7993cbc50e2db937f598571.png)

![](media/526a7d846db04d20ea8b0156c3cde101.png)

**Test Code**

```c
#include <Servo.h>  //add Servo library file
Servo myservo1;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;
Servo myservo4;  

int pos1=90, pos2=60, pos3=130, pos4=0;  // define the variable of 4 servo angle,and assign the initial value (that is the boot posture angle value) 


const int right_X = A2; // define the right X pin to A2
const int right_Y = A5; //define the right Y pin to A5
const int right_key = 7; // define the right key to 7(the value of Z axis)
const int left_X = A3; // define the left X pin to A3
const int left_Y = A4;  // define the left Y pin to A4
const int left_key = 6; // define the left key to 6(the value of Z axis)

int x1,y1,z1;  //define a variable to store the read Joystick value
int x2,y2,z2;

void setup() 
{
  //Serial.begin(9600); //  set the baud rate to 9600 

  //start up posture 
  myservo1.write(pos1);  
  delay(1000);
  myservo2.write(pos2);
  myservo3.write(pos3);
  myservo4.write(pos4);
  delay(1500);

  pinMode(right_key, INPUT);   // set the right/left key to INPUT
  pinMode(left_key, INPUT);
  //Serial.begin(9600); //  set baud rate to 9600
}
 
void loop() 
{
  myservo1.attach(A1);  //set the control pin of Servo1 to A1
  myservo2.attach(A0);  //set the control pin of Servo2 to A0
  myservo3.attach(8);   //set the control pin of Servo3 to D8
  myservo4.attach(9);   //set the control pin of Servo4 to D9

  x1 = analogRead(right_X); // read the value of right X axis

  y1 = analogRead(right_Y);  // read the value of right Y axis
  z1 = digitalRead(right_key);  ////read the value of right Z axis
  
  x2 = analogRead(left_X);  //read the value of left X axis
  y2 = analogRead(left_Y);  //read the value of left Y axis
  z2 = digitalRead(left_key);  //read the value of left Z axis
  //delay(5);  //lower the speed overall
    //Serial.println("**********right**********");
  //Serial.print("right_X = "); // on the serial monitor, print out right_X = 
  //Serial.print(x1 ,DEC); // print out the value of right X and line wrap
  //Serial.print("  ");
  //Serial.print("right_Y = ");
  //Serial.print(y1 ,DEC);
  //Serial.print("  ");
  //Serial.print("right_key = ");
  //Serial.print(z1 ,DEC);
  //Serial.print(" ||| ");
  //Serial.println("*********left***********");
  //Serial.print("left_X = ");
  //Serial.print(x2 ,DEC);
  //Serial.print("  ");
  //Serial.print("left_Y = ");
  //Serial.print(y2 ,DEC);
  //Serial.print("  ");
  //Serial.print("left_key = ");
  //Serial.println(z2 ,DEC);

  //clamp claw
  zhuazi();
  //rotate
  zhuandong();
  //Right Servo
  right_ser();
  //Left Servo
  left_ser();
}

//Claw
void zhuazi()
{
    //Claw
  if(x2<50) //if push the left joystick to the right
  {
      pos4=pos4-1;  //current angle of servo 4 subtracts 1（change the value you subtract, thus change the closed speed of claw）
      //Serial.println(pos4);
      myservo4.write(pos4);  //Servo4 operates the action，claw gradually closes
      delay(5);
      if(pos4<0)  //if pos4 value subtracts to 0
      {            //（change value according to real situation）
        pos4=0;   //stop subtraction when reduce to 0
      }
   }
  if(x2>1000) ////if push the left joystick to the left 
  {
      pos4=pos4+2; // current angle of servo 4 plus 2（change the value you plus, thus change the open speed of claw）

      //Serial.println(pos4);
      myservo4.write(pos4); //Servo4 operates the motion, the claw gradually opens.

      delay(5);
      if(pos4>110)  //limit the largest angle when open the claw 
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
    myservo1.write(pos1);  //Servo1 operates the motion, the arm turns right.
    delay(5);
    if(pos1<1)   //limit the angle when turn right
    {
      pos1=1;
    }
  }
  if(x1>1000)  // if push the right joystick to the left
  {
    pos1=pos1+1;  //pos1 plus 1
    myservo1.write(pos1);  //arm turns left 
    delay(5);
    if(pos1>180)  //limit the angle when turn left 
    {
      pos1=180;
    }
  }
}

//**********************************************************/
//Right Servo
void right_ser()
{
    if(y1<50) //if push the right joystick backward
  {
    pos3=pos3-1;
    myservo3.write(pos3); //the joystick of right Servo swings backward
    delay(5);
    if(pos3<0)  //limit the angle
    {
      pos3=0;
    }
  }
  if(y1>1000)  // if push the right joystick forward
  {
    pos3=pos3+1;  
    myservo3.write(pos3);  //the joystick of right Servo swings forward
    delay(5);
    if(pos3>180)  //limit the angle when go down
    {
      pos3=180;
    }
  }
}

//*************************************************************/
//Left Servo
void left_ser()
{
  if(y2<50)  //if push the left joystick backward 
  {
    pos2=pos2+1;
    myservo2.write(pos2);  //the joystick of left Servo swings backward
    delay(5);
    if(pos2>180)   // limit the retracted angle 
    {
      pos2=180;
    }
  }
  
  if(y2>1000)  //if push the left joystick forward 
  {
    pos2=pos2-1;
    myservo2.write(pos2);  //the joystick of left Servo swings forward
    delay(5);
    if(pos2<35)  // Limit the the stretched angle
    {
      pos2=35;
    }
  }

}
```

**Test Result**

Upload code to the main control board, stack the shield on the main control board, and wire according to connection diagram. 

After powering on, the 4 DOF robot arm is in the initial position. Shake the two joysticks to control the 4 DOF robot arm to perform various movements.

## Project 6: Add Memory Function

### Project 6.1: Memorize One Posture

**Description**

In the previous section, use the analog value of pin X,Y of 2 Joystick modules to control the robot arm.

In the following experiment, we add a memory function for the robot arm, making it remember a posture then operate. 

Set 4 variables for saving the angle value of 4 servos, use the Joystick to control a posture. Press the key Z1 of right Joystick to save the angle value of 4 servos; press the key Z2 of left Joystick to make the servo operate a posture saved in the variable.

**Connection Diagram**

![](media/526a7d846db04d20ea8b0156c3cde101.png)

![](media/c19bcdd5f7993cbc50e2db937f598571.png)

**Test Code**

```c
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
```

**Test Result**

Wire it up, stack the shield onto Arduino, upload the code. Powered on, press the key Z1 of right Joystick to save the angle value of 4 servos control. Press the key Z2 of left Joystick to operate a servo posture saved in the variable.

### Project 6.2: Memorize Several Postures

**Description**

In the previous section, we have set the angle of 4 servos to make the robot arm remember and operate a posture. To extend the experiment, next make it remember several postures, at most 10 (you can set it in the code), then make 4DOF robot arm continually operate the posture in memory. 

That is, make robot arm memorize a group of actions, and you can set the memorizing speed in the code.

**Connection Diagram**

![](media/526a7d846db04d20ea8b0156c3cde101.png)

![](media/c19bcdd5f7993cbc50e2db937f598571.png)

**Test Code**

```c
#include <Servo.h>  //add Servo libraries file
Servo myservo1;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;
Servo myservo4;  
int pos1=90, pos2=60, pos3=130, pos4=0;  //define the variable of 4 servo angle and assign the initial value( that is the boot posture angle value)

const int right_X = A2; //define right X pin to A2 
const int right_Y = A5; //define right X pin to A5 
const int right_key = 7; //define right key to 7（the value of Z）

const int left_X = A3; //define right X pin to A3
const int left_Y = A4;  //define right Y pin to A4
const int left_key = 6; //define the left key to 6（the value of Z）

int x1,y1,z1;  //define variable for saving the read value of Joystick
int x2,y2,z2;
int s1,s2,s3,s4;
int jiyi1[10];  //define 4 array, separately save the angle of 4 Servo
int jiyi2[10];  //（array length is 10，namely can save angle data of 0~10 servo ）
int jiyi3[10];  //if need to save more data, just change the number 10 to be more larger number.
int jiyi4[10];
int i=0; //for looping
int j=0; //for saving the last value of “i”

void setup() 
{
  //posture of boot-up
  myservo1.write(pos1);  
  delay(1000);
  myservo2.write(pos2);
  myservo3.write(pos3);
  myservo4.write(pos4);
  delay(1500);
    
  
  pinMode(right_key, INPUT);   //set left and right keys to input
  pinMode(left_key, INPUT);
  //Serial.begin(115200); // set baud rate to 15200
}

void loop() 
{
  myservo1.attach(A1);  //set control pin of Servo1 to A1
  myservo2.attach(A0);  //set control pin of Servo2 to A0
  myservo3.attach(8);   // set control pin of Servo3 to D8
  myservo4.attach(9);   // set control pin of Servo4 to D9
  
  x1 = analogRead(right_X); //read the value of right X
  y1 = analogRead(right_Y);  //read the value of right Y
  z1 = digitalRead(right_key);  //read the value of right Z
  
  x2 = analogRead(left_X);  //read the value of right X
  y2 = analogRead(left_Y);  //read the value of right Y
  z2 = digitalRead(left_key);  //read the value of right Z
  //delay(5);  //reduce speed overall
  if(z1==1)   //determine if right key of Joystick is pressed
  {
    delay(10);   //delay for eliminating shake 
    if(z1==1)   //judge again if the right key is pressed
    {
      s1=myservo1.read();    //read the angle value of each servo  
      delay(100);
      //Serial.println(s1);
      s2=myservo2.read();
      delay(100);
      //Serial.println(s2);
      s3=myservo3.read();
      delay(100);
      //Serial.println(s3);
      s4=myservo4.read();
      delay(100);
      //Serial.println(s4);
      
      jiyi1[i]=s1;   //Save the read servo value to the array sequentially
      jiyi2[i]=s2;
      jiyi3[i]=s3;
      jiyi4[i]=s4;
      i++;     //i value plus 1
      j=i;     //assign the last value of i to j
      delay(100);
      //Serial.println(i);   //print out “i” on serial monitor
    }
  }
      
  if(z2==1) //determine if left key of Joystick is pressed
  {
    delay(10);
    if(z2==1)   //judge again if the left key is pressed 
    {
      i=0;  //assign “i”to 0 for memorizing next time
      pos1 = myservo1.read();    // memorize the angle value of 4 servo posture
      pos2 = myservo2.read();
      pos3 = myservo3.read();
      pos4 = myservo4.read();

      for(int k=0;k<j;k++)   //loop for j times, perform all actions saved.
      {
        if(pos1<jiyi1[k])    //if the current servo 1 angle is less than the value stored in array 1.
        {
          while(pos1<jiyi1[k])  //while loop, make servo turn to the position of value stored in the array.
          {
            myservo1.write(pos1);  //Servo1 performs the action
            delay(5);    //delay for 5ms to control Servo rotation speed
            pos1++;  //pos1 plus 1
            //Serial.println(pos1);
          }
        }
        else    // if the current Servo 1 angle is greater than the value stored in array 1.
        {
         while(pos1>jiyi1[k])     //while loop, make servo turn to the position of value stored in the array.
          {
            myservo1.write(pos1);   //Servo1 performs the action
            delay(5);    //delay 5ms，controlling the Servo rotating speed
            pos1--;     //pos1 subtracts 1
            //Serial.println(pos1);
          }
        }
//***************************************************************
  //the explanation is the same as the previous servo 
        if(pos2<jiyi2[k])
        {
          while(pos2<jiyi2[k])
          {
            myservo2.write(pos2);
            delay(5);
            pos2++;
            //Serial.println(pos1);
          }
        }
        else
        {
         while(pos2>jiyi2[k])
          {
            myservo2.write(pos2);
            delay(5);
            pos2--;
            //Serial.println(pos1);
          }
        }
 //***************************************************************
  //the explanation is the same as the previous servo 

        if(pos3<jiyi3[k])
        {
          while(pos3<jiyi3[k])
          {
            myservo3.write(pos3);
            delay(5);
            pos3++;
            //Serial.println(pos1);
          }
        }
        else
        {
         while(pos3>jiyi3[k])
          {
            myservo3.write(pos3);
            delay(5);
            pos3--;
            //Serial.println(pos1);
          }
        }
 //***************************************************************
  //the explanation is the same as the previous servo 

        if(pos4<jiyi4[k])
        {
          while(pos4<jiyi4[k])
          {
            myservo4.write(pos4);
            delay(5);
            pos4++;
            //Serial.println(pos1);
          }
        }
        else
        {
         while(pos4>jiyi4[k])
          {
            myservo4.write(pos4);
            delay(5);
            pos4--;
            //Serial.println(pos1);
          }
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
      pos4=pos4-1;  //angle of servo 4, subtract 1 (change the value you subtract, thus change the closed speed of claw)

      //Serial.println(pos4);
      myservo4.write(pos4);  //Servo4 operates the motion and claw is gradually closed. 
      delay(5);
      if(pos4<0)  //if pos4 value subtracts to 0, the claw in 37 degrees we have tested is closed.） 
      {            //（should change the value based on the fact）
        pos4=0;   //stop subtraction when reduce to 0
      }
   }
  if(x2>1000) ////if push the left joystick to the left
  {
      pos4=pos4+2; //current angle of servo 4 plus 2（change the value you plus, thus change the open speed of claw）

      //Serial.println(pos4);
      myservo4.write(pos4); //Servo4 operates the action, claw gradually opens.
      delay(5);
      if(pos4>110)  // limit the largest angle opened
      {
        pos4=110;
      }
  }
}
//******************************************************
 //rotate
void zhuandong()
{
  if(x1<50)  //if push the right joystick to the right 
  {
    pos1=pos1-1;  //pos1 subtracts 1
    myservo1.write(pos1);  //Servo1 operates the motion and robot arm turns right 
    delay(5);
    if(pos1<1)   //limit angle when turning right
    {
      pos1=1;
    }
  }
  if(x1>1000)  //if push the right joystick to the left 
  {
    pos1=pos1+1;  //pos1 plus 1
    myservo1.write(pos1);  //robot arm turns left
    delay(5);
if(pos1>180)  //limit the angle when turning left   
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
    myservo3.write(pos3); //the joystick of right Servo swings backward
    delay(5);
    if(pos3<0)  //limit angle
    {
      pos3=0;
    }
  }
  if(y1>1000)  //if push the right joystick forward

  {
    pos3=pos3+1;  
    myservo3.write(pos3);  //the joystick of right Servo swings forward
    delay(5);
    if(pos3>180)  //limit the descent speed
    {
      pos3=180;
    }
  }
}

//*************************************************************/
//left Servo
void left_ser()
{
  if(y2<50)  //if push left joystick backward
  {
    pos2=pos2+1;
myservo2.write(pos2);  //the joystick of left Servo swings backward
    delay(5);
    if(pos2>180)   //limit the retracted angle
    {
      pos2=180;
    }
  }
  
  if(y2>1000)  //if push the left joystick forward 
  {
    pos2=pos2-1;
myservo2.write(pos2);  //the joystick of left Servo swings forward.
    delay(5);
    if(pos2<35)  //limit the stretched angle
    {
      pos2=35;
    }
  }
  
}
```

**Test Result**

Wire it up, stack the shield onto Arduino , upload the code. 

Powered on, press the key Z1 of right Joystick to save the angle value of 4 servos. Press down the key Z1 to memorize different postures, at most 10 postures in the code. If need to memorize more postures, you can set it in the code. 

When memorizing successfully, press down the key Z2 of left Joystick to make the robot arm carry out several postures stored successively.

### Project 6.3: Memorize Several Postures And Loop

**Description**

In the previous section, we have introduced how to make 4DOF robot arm to memorize and perform a group of posture. Furthermore, let’s extend one more loop function. 

That is, when robot arm performs all the memorized actions, it will not stop, and continue to repeat those actions.

In the following experiment, press the key Z1, 4DOF robot arm will exit the looping action. Press the key Z1 again, start to memorize the posture, after that, press the key Z2 to loop the memorized actions.

**Connection Diagram**

![](media/526a7d846db04d20ea8b0156c3cde101.png)

![](media/c19bcdd5f7993cbc50e2db937f598571.png)

**Test Code**

```c
#include <Servo.h>  //add the servo libraries
Servo myservo1;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;
Servo myservo4;
int pos1=90, pos2=60, pos3=130, pos4=0;  //define the variable of 4 servo angle and assign the initial value( that is the boot posture angle value)

const int right_X = A2; //define the right X pin to A2 
const int right_Y = A5; //define the right Y pin to A5 
const int right_key = 7; //define the right key pin to 7（that is Z value）

const int left_X = A3; //define the left X pin to A3
const int left_Y = A4;  //define the left Y pin to A4
const int left_key = 6; //define the left key pin to 6（that is Z value）

int x1,y1,z1;  //define the variable, used to save the joystick value.
int x2,y2,z2;     
int s1,s2,s3,s4;
int jiyi1[20];  //define 4 array, separately used to save the angle of four servo.
int jiyi2[20];  //（array length is 20，namely can save angle data of 0~20 servo）
int jiyi3[20];  //if need to save more data, just change the number 20 to be more larger number.
int jiyi4[20];
int i=0;  //for loop
int j=0;  //save the last value of i

void setup() 
{
  // posture of boot-up
  myservo1.write(pos1);  //turn servo 1 to 90°
  delay(1000);
  myservo2.write(pos2);  //turn servo 2 to 90°
  myservo3.write(pos3);  //turn servo 3 to 120°
  myservo4.write(pos4);  //turn servo 4 to 35° 
  delay(1500);
  
  pinMode(right_key, INPUT);   //set the right/left key to INOUT
  pinMode(left_key, INPUT);
  //Serial.begin(115200);   //set baud rate to 115200
}

void loop() 
{
  myservo1.attach(A1);  //set the control pin of servo 1 to A1
  myservo2.attach(A0);  //set the control pin of servo 2 to A0
  myservo3.attach(8);   //set the control pin of servo 3 to D6
  myservo4.attach(9);   //set the control pin of servo 4 to D9
  
  x1 = analogRead(right_X); //read the right X value
  y1 = analogRead(right_Y);  //read the right Y value
  z1 = digitalRead(right_key);  //read the right Z value 
  
  x2 = analogRead(left_X);  //read the left X value
  y2 = analogRead(left_Y);  //read the left Y value
  z2 = digitalRead(left_key);  //read the left Z value
  //delay(8);  //delay, used to reduce the joystick value read, that is reduce the whole speed.
  if(z1==1)   //if the joystick right key is pressed
  {
    delay(10);  //delay for eliminating shake 
    if(z1==1)   //judge again if the right key is pressed
    {
      s1=myservo1.read();  // read the angle value of servo 1 and assign it to s1
      delay(100);
      //Serial.println(s1); //print out the angle value of servo 1 on the serial monitor
      s2=myservo2.read();  //read the angle value of servo 2 and assign it to s2
      delay(100);
      //Serial.println(s2);
      s3=myservo3.read();   //read the angle value of servo 3 and assign it to s3
      delay(100);
      //Serial.println(s3);
      s4=myservo4.read();   //read the angle value of servo 4 and assign it to s4 
      delay(100);
      //Serial.println(s4);
      
      
      jiyi1[i]=s1;  //Save the read servo value to the array sequentially
      jiyi2[i]=s2;
      jiyi3[i]=s3;
      jiyi4[i]=s4;
      i++;   //i plus 1
      j=i;   //assign the last value of i to j
      delay(100);  //delay 100ms
      //Serial.println(i);  //print out the value i
    }
  }
  if(z2==1) //if the left joystick key is pressed
  {
    delay(10);  //delay for eliminating shake 
    if(z2==1)   //judge again if the left key is pressed 
    {
      pos1 = myservo1.read();  //memorize the angle value of 4 servo posture
      pos2 = myservo2.read();
      pos3 = myservo3.read();
      pos4 = myservo4.read();
      
      while(z2==1)  //loop, make the arm repeat the action.
      {
        for(int k=1;k<j;k++)  //for loop, perform all the stored actions.
        {
          if(pos1<jiyi1[k])   //if the current servo 1 angle is less than the value stored in array 1.
          {
            while(pos1<jiyi1[k])  //whileloop, make servo turn to the position of value stored in the array.            
{
              myservo1.write(pos1);  //Servo1 performs the action
              delay(5);   //delay 5ms，controlling the servo rotating speed.
              pos1++;   //pos1 plus 1，gradually reach out the saved angle value
              //Serial.println(pos1);
            }
          }
          else   //if the current servo 1 angle is greater than the value stored in array 1.
          {
           while(pos1>jiyi1[k])    //while loop, make servo turn to the position of value stored in the array.
            {
              myservo1.write(pos1);  //Servo1 performs the action
              delay(5);   //delay 5ms，controlling the servo rotating speed.
              pos1--;   //pos1 subtracts 1
              //Serial.println(pos1);
            }
          }
  //***************************************************************
  //the explanation is the same as the previous servo. 
          if(pos2<jiyi2[k])
          {
            while(pos2<jiyi2[k])
            {
              myservo2.write(pos2);
              delay(5);
              pos2++;
              //Serial.println(pos1);
            }
          }
          else
          {
           while(pos2>jiyi2[k])
            {
              myservo2.write(pos2);
              delay(5);
              pos2--;
              //Serial.println(pos1);
            }
          }
   //*********************************************
   //the explanation is the same as the previous servo. 
          if(pos3<jiyi3[k])
          {
            while(pos3<jiyi3[k])
            {
              myservo3.write(pos3);
              delay(5);
              pos3++;
              //Serial.println(pos1);
            }
          }
          else
          {
           while(pos3>jiyi3[k])
            {
              myservo3.write(pos3);
              delay(5);
              pos3--;
              //Serial.println(pos1);
            }
          }
//*********************************************
//the explanation is the same as the previous servo. 
          if(pos4<jiyi4[k])
          {
            while(pos4<jiyi4[k])
            {
              myservo4.write(pos4);
              delay(5);
              pos4++;
              //Serial.println(pos1);
            }
          }
          else
          {
           while(pos4>jiyi4[k])
            {
              myservo4.write(pos4);
              delay(5);
              pos4--;
              //Serial.println(pos1);
            }
          }
        }
//************************************************************
//for exiting the loop
            z1 = digitalRead(right_key);  //read the right Z value
            if(z1==1)  //if the right key is pressed
            {
              delay(10);  //eliminate the shake
              if(z1==1)  //if the key z1 is pressed
              {
                //pos1=jiyi1[(j-1)];  // assign the last angle value saved in array to pos
                //pos2=jiyi2[(j-1)];  //for exiting the loop, still access to joystick control.
                //pos3=jiyi3[(j-1)];  
                //pos4=jiyi4[(j-1)];
                i=0;  //assign i as 0，prepare for saving the angle value using array
                z2=0; //assign z2 as 0，for exiting the while loop
                break;  //exit the current loop
              }
            }
//********************************************************
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
      pos4=pos4-1;  //angle of servo 4, subtract 2 (change the value you subtract, thus change the closed speed of claw)
      //Serial.println(pos4);
      myservo4.write(pos4);  //servo 4 operates the motion and claw is gradually closed.
      delay(5);
      if(pos4<0)  //if pos4 value subtracts to 0, the claw closes at 0 degree 
      {            //（should change the value based on the fact）
        pos4=0;   //stop subtraction when reduce to 2
      }
   }
  if(x2>1000) ////if push the left joystick to the left
  {
      pos4=pos4+2; //current angle of servo 4 plus 2（change the value you plus, thus change the open speed of claw）
      //Serial.println(pos4);
      myservo4.write(pos4); //Servo4 operates the action, claw gradually opens.
      delay(5);
      if(pos4>110)  //limit the largest angle opened
      {
        pos4=110;
      }
  }
}
//******************************************************
 //rotate
void zhuandong()
{
  if(x1<50)  //if push the right joystick to the right 
  {
    pos1=pos1-1;  //pos1 subtracts 1
    myservo1.write(pos1);  //servo 1 performs the action, the robot arm turns right.
    delay(5);
    if(pos1<1)   //limit the right turning angle 
    {
      pos1=1;
    }
  }
  if(x1>1000)  //if push the right joystick to the left
  {
    pos1=pos1+1;  //pos1 plus 1
    myservo1.write(pos1);  //the robot arm turns left
    delay(5);
    if(pos1>180)  //limit the left turning angle 
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
    myservo3.write(pos3); //the joystick of right Servo swings backward
    delay(5);
    if(pos3<0)  //limit angle
    {
      pos3=0;
    }
  }
  if(y1>1000)  //if push the right joystick forward
  {
    pos3=pos3+1;  
    myservo3.write(pos3);  //the joystick of right Servo swings forward
    delay(5);
    if(pos3>180)  //limit the declining angle 
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
    if(pos2>180)   //limit the retracted angle
    {
      pos2=180;
    }
  }
  
  if(y2>1000)  //if push the left joystick forward
  {
    pos2=pos2-1;
    myservo2.write(pos2);  //the joystick of left Servo swings forward
    delay(5);
    if(pos2<35)  //limit the stretched angle
    {
      pos2=35;
    }
  }
  
}
```

**Test Result**

Wire it up, stack the shield onto Arduino, upload the code. Powered on, press the key Z1 of right Joystick to save the angle value of 4 servos. Press down the key Z1 to memorize different postures, at most 10 postures in the code. If need to memorize more postures, can set it in the code.

When memorizing successfully, press down the key Z2 of left Joystick to make the robot arm carry out several postures stored successively, looping.

Long press the key Z1, 4DOF robot arm will exit the looping action. Press the key Z1 again, start to memorize the posture, after that, press the key Z2 to loop the memorized actions.


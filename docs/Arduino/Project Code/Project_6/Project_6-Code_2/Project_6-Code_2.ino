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

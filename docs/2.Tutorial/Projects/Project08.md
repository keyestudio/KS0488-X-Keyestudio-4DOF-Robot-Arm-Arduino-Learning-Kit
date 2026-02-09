## Project 8: PS2 Controlling Robotic Arm (Extension)

### Project 8.1: PS2 Joypad Keys Test

**Description**

The shield comes with a PS2 **Joypad connector** which help you control robotic arm easily. The PS2 **Joypad**( PS2 receiver）is not included in kit. You need to purchase it online.

Firstly plug the PS2 receiver into the PS2 interface of the servo driver shield and then connect the PS2 **Joypad**. After the PS2 handle is connected well, upload code to test on Arduino IDE. Before testing, we need to put the PS2X_lib folder in the libraries folder where the Arduino IDE is installed. 

After uploading the sample code of PPS2X_lib folder, open the serial monitor, connect the PS2 **Joypad**, and press each button of the PS2 **Joypad** to view the characters printed on monitor.

**Test Code**

```c
#include <PS2X_lib.h>  //for v1.6

/******************************************************************
 * set pins connected to PS2 controller:
 *   - 1e column: original 
 *   - 2e colmun: Stef?
 * replace pin numbers by the ones you use
 ******************************************************************/


/******************************************************************
 * select modes of PS2 controller:
 *   - pressures = analog reading of push-butttons 
 *   - rumble    = motor rumbling
 * uncomment 1 of the lines for each mode selection
 ******************************************************************/
//#define pressures   true
#define pressures   false
//#define rumble      true
#define rumble      false

PS2X ps2x; // create PS2 Controller Class

//right now, the library does NOT support hot pluggable controllers, meaning 
//you must always either restart your Arduino after you connect the controller, 
//or call config_gamepad(pins) again after connecting the controller.

int error = 0;
byte type = 0;
byte vibrate = 0;

void setup(){
 
  Serial.begin(57600);
  
  delay(300);  //added delay to give wireless ps2 module some time to startup, before configuring it
   
  //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************
  
  //setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
 // error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
   error = ps2x.config_gamepad(13,11,10,12); 
  if(error == 0){
    Serial.print("Found Controller, configured successful ");
    Serial.print("pressures = ");
  if (pressures)
    Serial.println("true ");
  else
    Serial.println("false");
  Serial.print("rumble = ");
  if (rumble)
    Serial.println("true)");
  else
    Serial.println("false");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
  }  
  else if(error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if(error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
  
//  Serial.print(ps2x.Analog(1), HEX);
  
  type = ps2x.readType(); 
  switch(type) {
    case 0:
      Serial.print("Unknown Controller type found ");
      break;
    case 1:
      Serial.print("DualShock Controller found ");
      break;
    case 2:
      Serial.print("GuitarHero Controller found ");
      break;
  case 3:
      Serial.print("Wireless Sony DualShock Controller found ");
      break;
   }
}

void loop() {
  /* You must Read Gamepad to get new values and set vibration values
     ps2x.read_gamepad(small motor on/off, larger motor strenght from 0-255)
     if you don't enable the rumble, use ps2x.read_gamepad(); with no values
     You should call this at least once a second
   */  
  if(error == 1) //skip loop if no controller found
    return; 
  
  if(type == 2){ //Guitar Hero Controller
    ps2x.read_gamepad();          //read controller 
   
    if(ps2x.ButtonPressed(GREEN_FRET))
      Serial.println("Green Fret Pressed");
    if(ps2x.ButtonPressed(RED_FRET))
      Serial.println("Red Fret Pressed");
    if(ps2x.ButtonPressed(YELLOW_FRET))
      Serial.println("Yellow Fret Pressed");
    if(ps2x.ButtonPressed(BLUE_FRET))
      Serial.println("Blue Fret Pressed");
    if(ps2x.ButtonPressed(ORANGE_FRET))
      Serial.println("Orange Fret Pressed"); 

    if(ps2x.ButtonPressed(STAR_POWER))
      Serial.println("Star Power Command");
    
    if(ps2x.Button(UP_STRUM))          //will be TRUE as long as button is pressed
      Serial.println("Up Strum");
    if(ps2x.Button(DOWN_STRUM))
      Serial.println("DOWN Strum");
 
    if(ps2x.Button(PSB_START))         //will be TRUE as long as button is pressed
      Serial.println("Start is being held");
    if(ps2x.Button(PSB_SELECT))
      Serial.println("Select is being held");
    
    if(ps2x.Button(ORANGE_FRET)) {     // print stick value IF TRUE
      Serial.print("Wammy Bar Position:");
      Serial.println(ps2x.Analog(WHAMMY_BAR), DEC); 
    } 
  }
  else { //DualShock Controller
    ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed
    
    if(ps2x.Button(PSB_START))         //will be TRUE as long as button is pressed
      Serial.println("Start is being held");
    if(ps2x.Button(PSB_SELECT))
      Serial.println("Select is being held");      

    if(ps2x.Button(PSB_PAD_UP)) {      //will be TRUE as long as button is pressed
      Serial.print("Up held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
    }
    if(ps2x.Button(PSB_PAD_RIGHT)){
      Serial.print("Right held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
    }
    if(ps2x.Button(PSB_PAD_LEFT)){
      Serial.print("LEFT held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
    }
    if(ps2x.Button(PSB_PAD_DOWN)){
      Serial.print("DOWN held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
    }   

    vibrate = ps2x.Analog(PSAB_CROSS);  //this will set the large motor vibrate speed based on how hard you press the blue (X) button
    if (ps2x.NewButtonState()) {        //will be TRUE if any button changes state (on to off, or off to on)
      if(ps2x.Button(PSB_L3))
        Serial.println("L3 pressed");
      if(ps2x.Button(PSB_R3))
        Serial.println("R3 pressed");
      if(ps2x.Button(PSB_L2))
        Serial.println("L2 pressed");
      if(ps2x.Button(PSB_R2))
        Serial.println("R2 pressed");
      if(ps2x.Button(PSB_TRIANGLE))
        Serial.println("Triangle pressed");        
    }

    if(ps2x.ButtonPressed(PSB_CIRCLE))               //will be TRUE if button was JUST pressed
      Serial.println("Circle just pressed");
    if(ps2x.NewButtonState(PSB_CROSS))               //will be TRUE if button was JUST pressed OR released
      Serial.println("X just changed");
    if(ps2x.ButtonReleased(PSB_SQUARE))              //will be TRUE if button was JUST released
      Serial.println("Square just released");     

    if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) { //print stick values if either is TRUE
      Serial.print("Stick Values:");
      Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX  
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_LX), DEC); 
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_RY), DEC); 
      Serial.print(",");
      Serial.println(ps2x.Analog(PSS_RX), DEC); 
    }     
  }
  delay(50);  
}
```

**Test Result:**

Stack the drive shield onto Arduino and upload the code. Connecting the PS2 Joypad, open the serial monitor and set the baud rate to 57600. 

When press down the key or push the rocker, you could see the corresponding character showed on the monitor.

### Project 8.2: PS2 Joypad Control

**Description:**

In the previous section, we have showed how to use Joystick module to control the robot arm. It is almost the same for you to control the 4DOF robot arm using the PS2 Joypad.

**Connection Diagram**

![](media/c19bcdd5f7993cbc50e2db937f598571.png)

**Test Code**

```c
#include <PS2X_lib.h>

PS2X ps2x; // create PS2 Controller Class


//right now, the library does NOT support hot pluggable controllers, meaning 
//you must always either restart your Arduino after you connect the controller, 
//or call config_gamepad(pins) again after connecting the controller.
int error = 0; 
byte vibrate = 0;

#include <Servo.h>  // add the servo libraries 
Servo myservo1;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;
Servo myservo4;

int pos1=90, pos2=60, pos3=130, pos4=0;  // define the variable of 4 servo angle and assign the initial value( that is the boot posture angle value)

void setup(){
 Serial.begin(57600);

// boot posture
  myservo1.write(pos1);  
  delay(1000);
  myservo2.write(pos2);
  myservo3.write(pos3);
  myservo4.write(pos4);
  delay(1500);
  
 error = ps2x.config_gamepad(13,11,10,12);   //setup GamePad(clock, command, attention, data) pins, check for error
 
 if(error == 0){
   Serial.println("Found Controller, configured successful");
   Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
  Serial.println("holding L1 or R1 will print out the analog stick values.");
  Serial.println("Go to www.billporter.info for updates and to report bugs.");
 }
   
  else if(error == 1)
   Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
   Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
   
   //Serial.print(ps2x.Analog(1), HEX);
 
 
 ps2x.enableRumble();              //enable rumble vibration motors
 ps2x.enablePressures();           //enable reading the pressure values from the buttons. 
  

  
}

void loop(){
   /* You must Read Gamepad to get new values
   Read GamePad and set vibration values
   ps2x.read_gamepad(small motor on/off, larger motor strenght from 0-255)
   if you don't enable the rumble, use ps2x.read_gamepad(); with no values
   
   you should call this at least once a second
   */

  myservo1.attach(A1);  // set the control pin of servo 1 to A1
  myservo2.attach(A0);  // set the control pin of servo 2 to A0
  myservo3.attach(8);   // set the control pin of servo 3 to D6
  myservo4.attach(9);   // set the control pin of servo 4 to D9
  
 if(error != 0)
  return; 
  
  ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
  
  if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed
       Serial.println("Start is being held");
  if(ps2x.Button(PSB_SELECT))
       Serial.println("Select is being held");
       
       
   if(ps2x.Button(PSB_PAD_UP)) {         //will be TRUE as long as button is pressed
     Serial.print("Up held this hard: ");
     Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
    }
    if(ps2x.Button(PSB_PAD_RIGHT)){
     Serial.print("Right held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
    }
    if(ps2x.Button(PSB_PAD_LEFT)){
     Serial.print("LEFT held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
    }
    if(ps2x.Button(PSB_PAD_DOWN)){
     Serial.print("DOWN held this hard: ");
   Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
    }   

  
    vibrate = ps2x.Analog(PSAB_BLUE);        //this will set the large motor vibrate speed based on 
                                            //how hard you press the blue (X) button    
  
  if (ps2x.NewButtonState())               //will be TRUE if any button changes state (on to off, or off to on)
  {
      if(ps2x.Button(PSB_R3))
        
       Serial.println("R3 pressed");
     
       
      if(ps2x.Button(PSB_L3))
       Serial.println("L3 pressed");
      
      if(ps2x.Button(PSB_L2))
       Serial.println("L2 pressed");
      if(ps2x.Button(PSB_R2))
       Serial.println("R2 pressed");
      if(ps2x.Button(PSB_GREEN))
       Serial.println("Triangle pressed");
       
  }   
       
  
  if(ps2x.ButtonPressed(PSB_RED))             //will be TRUE if button was JUST pressed
       Serial.println("Circle just pressed");
       
  if(ps2x.ButtonReleased(PSB_PINK))             //will be TRUE if button was JUST released
       Serial.println("Square just released");     
  
  if(ps2x.NewButtonState(PSB_BLUE))            //will be TRUE if button was JUST pressed OR released
       Serial.println("X just changed");    

    //rotate
    zhuandong();
    //clamp claw
    zhuazi();
    //main arm
    dabi();
    //forearm
    xiaobi();
    
  if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) // print stick values if either is TRUE
  {
      Serial.print("Stick Values:");
      Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX  
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_LX), DEC); 
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_RY), DEC); 
      Serial.print(",");
      Serial.println(ps2x.Analog(PSS_RX), DEC); 
  }    
  delay(5);    
}
//********************************************************************
// turn
void zhuandong()
{
//turn right
   if(ps2x.Analog (PSS_RX) > 200)  // if push the right joystick to the right 
    {
      //Serial.println(ps2x.Analog(PSS_RX), DEC);
      pos1=pos1-1;    //pos1 subtracts 1
      myservo1.write(pos1);   // servo 1 executes the action, the arm will turn right.
      // delay(5);
      if(pos1<1)   // limit the right turning angle 
      {
        pos1=1;
      }
     }
      // turn left
     if(ps2x.Analog (PSS_RX) < 50)    // if push the right joystick to the left
     {
       //Serial.println(ps2x.Analog(PSS_RX), DEC);
       pos1=pos1+1;   //pos1 plus 1
       myservo1.write(pos1);     // the arm turns left 
       // delay(5);
       if(pos1>180)     // limit the left turning angle
       {
         pos1=180;
       }
     }
 }
 //**********************************************************************  
 // upper arm 
void xiaobi()
{
  //upper arm front
   if(ps2x.Analog(PSS_RY)<50)  // if push the right joystick upward
   {
      pos2=pos2-1;
      myservo2.write(pos2);    // the upper arm will lift
      delay(5);
      if(pos2<0)    // limit the lifting angle
      {
        pos2=0;
      }
    }
    //upper arm back
    if(ps2x.Analog(PSS_RY)>200)    // if push the right joystick downward
    {
      pos2=pos2+1;
      myservo2.write(pos2);   // the upper arm will go down
      delay(5);
      if(pos2>180)  // limit the declining angle
      {
        pos2=180;
      }
    }
}
//***************************************************************
void zhuazi()
{
// close the claw
   if(ps2x.Analog(PSS_LX)>220)   // if push the left joystick to the right
   {
      pos4=pos4-1;
      Serial.println(pos4);
      myservo4.write(pos4);  // servo 4 carries out the action and the claw is gradually closed.
      delay(5);
      if(pos4<0)   // if pos4 value subtracts to 37, the claw in 37 degrees we have tested is closed.）
      {
        pos4=0;
      }
    }
    // open the claw
    if(ps2x.Analog(PSS_LX)<10)   // if push the left joystick to the left
    {
      pos4=pos4+8;
      Serial.println(pos4);
      myservo4.write(pos4);   // servo 4 carries out the action and the claw is gradually opened
      delay(5);
      if(pos4>108)    // limit the maximum opening angle 
      {
        pos4=108;
      }
    }
} 
//*********************************************************
void dabi()
{
  // lower arm front
  if(ps2x.Analog(PSS_LY)>200)  // if push the left joystick upward
  {
    pos3=pos3+1;
    myservo3.write(pos3);  // the lower arm will stretch out
    delay(5);
    if(pos3>180)   // limit the stretched angle
    {
      pos3=180;
    }
   }
  if(ps2x.Analog(PSS_LY)<10)    //if push the left joystick downward
  {
    pos3=pos3-1;
    myservo3.write(pos3);   // the lower arm will draw back
    delay(5);
    if(pos3<35)    // limit the retracted angle
    {
      pos3=35;
    }
   }
}
```

**Test Result:**

Stack the shield onto Arduino and upload the code. Powered on and connected the PS2 Joypad, you can use the PS2 Joypad to control the robot arm actions.

### Project 8.3: PS2 Controlling Posture Memory

**Description:**

In the previous experiment, we have showed how to use Joystick module to control the robot arm memorize several postures. Now we replace the joystick module with PS2 Joypad. The program thought is almost the same.

**Connection Diagram**

![](media/c19bcdd5f7993cbc50e2db937f598571.png)

**Test Code**

```c
#include <PS2X_lib.h>
#include <Servo.h>  // add the servo libraries
Servo myservo1;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;
Servo myservo4;  

int pos1=90, pos2=60, pos3=130, pos4=0;  // define the variable of 4 servo angle and assign the initial value( that is the boot posture angle value)

PS2X ps2x; // create PS2 Controller Class

//right now, the library does NOT support hot pluggable controllers, meaning 
//you must always either restart your Arduino after you conect the controller, 
//or call config_gamepad(pins) again after connecting the controller.
int error = 0; 
byte vibrate = 0;

int s1,s2,s3,s4;
int jiyi1[20];  // define four array, separately used to save the angle of 4 servos.
int jiyi2[20];
int jiyi3[20];
int jiyi4[20];
int i=0;
int j=0;

void setup()
{
 Serial.begin(57600);

 // boot posture
  myservo1.write(pos1);  
  delay(1000);
  myservo2.write(pos2);
  myservo3.write(pos3);
  myservo4.write(pos4);
  delay(1500);

  
 error = ps2x.config_gamepad(13,11,10,12);   //setup GamePad(clock, command, attention, data) pins, check for error
 
 if(error == 0){
   Serial.println("Found Controller, configured successful");
   Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
  Serial.println("holding L1 or R1 will print out the analog stick values.");
  Serial.println("Go to www.billporter.info for updates and to report bugs.");
 }
   
  else if(error == 1)
   Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
   Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
   
   //Serial.print(ps2x.Analog(1), HEX);
 
 
 ps2x.enableRumble();              //enable rumble vibration motors
 ps2x.enablePressures();           //enable reading the pressure values from the buttons. 
  

  
}

void loop()
{
  myservo1.attach(A1);  // set the control pin of servo 1 to A1
  myservo2.attach(A0);  // set the control pin of servo 2 to A0
  myservo3.attach(8);   // set the control pin of servo 3 to D6
  myservo4.attach(9);   // set the control pin of servo 4 to D9
  
 if(error != 0)
  return; 
  
  ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
  
  if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed
       Serial.println("Start is being held");
  if(ps2x.Button(PSB_SELECT))
       Serial.println("Select is being held");
       
       
   if(ps2x.Button(PSB_PAD_UP)) {         //will be TRUE as long as button is pressed
     Serial.print("Up held this hard: ");
     Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
    }
    if(ps2x.Button(PSB_PAD_RIGHT)){
     Serial.print("Right held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
    }
    if(ps2x.Button(PSB_PAD_LEFT)){
     Serial.print("LEFT held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
    }
    if(ps2x.Button(PSB_PAD_DOWN)){
     Serial.print("DOWN held this hard: ");
   Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
    }   

  
    vibrate = ps2x.Analog(PSAB_BLUE);        //this will set the large motor vibrate speed based on 
                                            //how hard you press the blue (X) button    
  
  if (ps2x.NewButtonState())               //will be TRUE if any button changes state (on to off, or off to on)
  {
      if(ps2x.Button(PSB_R3))
      {
        //Serial.println("R3 pressed");
        // record
        s1=myservo1.read();
        delay(100);
        Serial.println(s1);
        s2=myservo2.read();
        delay(100);
        Serial.println(s2);
        s3=myservo3.read();
        delay(100);
        Serial.println(s3);
        s4=myservo4.read();
        delay(100);
        Serial.println(s4);
      
        jiyi1[i]=s1;  // save the servo value read in the array sequentially
        jiyi2[i]=s2;
        jiyi3[i]=s3;
        jiyi4[i]=s4;
        i++;
        j=i;
       // delay(100);
       Serial.println(i);
      }
       
      if(ps2x.Button(PSB_L3))
      {
        //Serial.println("L3 pressed");
        i=0;
   //perform
       pos1 = myservo1.read();
       pos2 = myservo2.read();
       pos3 = myservo3.read();
       pos4 = myservo4.read();

      for(int k=0;k<j;k++)  //for loop, to execute all the stored actions
      { 
        if(pos1<jiyi1[k])  //if the current servo 1 angle is less than the value stored in array 1.
        {
          while(pos1<jiyi1[k])  //while loop, make servo turn to the position of value stored in the array.
          {
            myservo1.write(pos1);   // servo 1 executes the action
            delay(5);   // delay 5ms，controlling the rotating speed of servo
            pos1++;
            //Serial.println(pos1);
          }
        }
        else   //if the current servo 1 angle is greater than the value stored in array 1.
        {
         while(pos1>jiyi1[k])  //while loop, make servo turn to the position of value stored in the array.
          {  
            myservo1.write(pos1);   // servo 1 executes the action
            delay(5);    //delay 5ms，controlling the rotating speed of servo
            pos1--;
            //Serial.println(pos1);
          }
        
//**********************************************
// the same analysis as the previous servo
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
 //*****************************************************
 //the same analysis 
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
 //*****************************************************   
 //the same analysis
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
       
      
      if(ps2x.Button(PSB_L2))
       Serial.println("L2 pressed");
      if(ps2x.Button(PSB_R2))
       Serial.println("R2 pressed");
      if(ps2x.Button(PSB_GREEN))
       Serial.println("Triangle pressed");
       
  }   
       
  
  if(ps2x.ButtonPressed(PSB_RED))             //will be TRUE if button was JUST pressed
       Serial.println("Circle just pressed");
       
  if(ps2x.ButtonReleased(PSB_PINK))             //will be TRUE if button was JUST released
       Serial.println("Square just released");     
  
  if(ps2x.NewButtonState(PSB_BLUE))            //will be TRUE if button was JUST pressed OR released
       Serial.println("X just changed");    

    // turn
    zhuandong();
    // claw
    zhuazi();
    // lower arm
    dabi();
    // upper arm
    xiaobi();
  
  if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) // print stick values if either is TRUE
  {
      Serial.print("Stick Values:");
      Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX  
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_LX), DEC); 
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_RY), DEC); 
      Serial.print(",");
      Serial.println(ps2x.Analog(PSS_RX), DEC); 
  } 
    
 delay(5);
}

//********************************************************************
// turn 
void zhuandong()
{
//turn right 
   if(ps2x.Analog (PSS_RX) > 200)  // if push the right joystick to the right
    {
      //Serial.println(ps2x.Analog(PSS_RX), DEC);
      pos1=pos1-1;    //pos1 subtracts 1
      myservo1.write(pos1);   // servo 1 carries out the action and the arm will turn right
      // delay(5);
      if(pos1<1)   // limit the right turning angle 
      {
        pos1=1;
      }
     }
      //turn left
     if(ps2x.Analog (PSS_RX) < 50)    //if push the right joystick to the left
     {
       //Serial.println(ps2x.Analog(PSS_RX), DEC);
       pos1=pos1+1;   //pos1 plus 1
       myservo1.write(pos1);     // the arm will turn left
       // delay(5);
       if(pos1>180)     // limit the left turning angle 
       {
         pos1=180;
       }
     }
 }
 //**********************************************************************  
 // upper arm
void xiaobi()
{
  //upper arm front
   if(ps2x.Analog(PSS_RY)<50)  // if push the right joystick upward
   {
      pos2=pos2-1;
      myservo2.write(pos2);    // the upper arm will lift up
      delay(5);
      if(pos2<0)    // limit the lifting angle 
      {
        pos2=0;
      }
    }
    // upper arm back 
    if(ps2x.Analog(PSS_RY)>200)    //if push the right joystick downward
    {
      pos2=pos2+1;
      myservo2.write(pos2);   // the upper arm will go down 
      delay(5);
      if(pos2>180)  // limit the declining angle 
      {
        pos2=180;
      }
    }
}
//***************************************************************
void zhuazi()
{
// close the claw
   if(ps2x.Analog(PSS_LX)>220)   // if push the left joystick to the right 
   {
      pos4=pos4-1;
      Serial.println(pos4);
      myservo4.write(pos4);  // servo 4 carries out the action and the claw is gradually closed.
      delay(5);
      if(pos4<0)   // if pos4 value reduces to 37（the claw we test in 37degrees is closed）
      {
        pos4=0;
      }
    }
    // open the claw
    if(ps2x.Analog(PSS_LX)<10)   // if push the left joystick to the left
    {
      pos4=pos4+8;
      Serial.println(pos4);
      myservo4.write(pos4);   // servo 4 carries out the action and the claw is gradually opened
      delay(5);
      if(pos4>108)    // limit the maximum angle opened
      {
        pos4=108;
      }
    }
} 
//*********************************************************
void dabi()
{
  // lower arm front
  if(ps2x.Analog(PSS_LY)>200)  //  if push the left joystick upward
  {
    pos3=pos3+1;
    myservo3.write(pos3);  // the lower arm will stretch out
    delay(5);
    if(pos3>180)   // limit the stretched angle
    {
      pos3=180;
    }
   }
  if(ps2x.Analog(PSS_LY)<10)    // if push the left joystick downward
  {
    pos3=pos3-1;
    myservo3.write(pos3);   //the lower arm will retract
    delay(5);
    if(pos3<35)    // limit the retracted angle
    {
      pos3=35;
    }
   }
}
```

**Test Result:**

Stack the shield onto Arduino and upload the code. Powered on and connected the PS2 Joypad, you can use the PS2 Joypad to control the robot arm memorize several postures.

### Project 8.4: PS2 Controlling Posture Memory And Loop

**Description:**

In the previous experiment, we have showed how to use Joystick module to control the robot arm memorize several postures and loop. Now we replace the Joystick module with the PS2 Joypad. The program is almost the same.

**Connection Diagram**

![](media/c19bcdd5f7993cbc50e2db937f598571.png)

**Test Code**

```c
#include <PS2X_lib.h>
#include <Servo.h>  // add the servo libraries
Servo myservo1;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;
Servo myservo4;  

int pos1=90, pos2=60, pos3=130, pos4=0;  // define the variable of 4 servo angle and assign the initial value( that is the boot posture angle value)

PS2X ps2x; // create PS2 Controller Class

//right now, the library does NOT support hot pluggable controllers, meaning 
//you must always either restart your Arduino after you conect the controller, 
//or call config_gamepad(pins) again after connecting the controller.
int error = 0; 
byte vibrate = 0;

int s1,s2,s3,s4;
int jiyi1[30];   //define four array, separately used to save the angle of 4 servos.
int jiyi2[30];
int jiyi3[30];
int jiyi4[30];
int i=0;
int j=0,tt=0;
void setup()
{
 Serial.begin(57600);

 // boot posture
  myservo1.write(pos1);  
  delay(1000);
  myservo2.write(pos2);
  myservo3.write(pos3);
  myservo4.write(pos4);
  delay(1500);

  
 error = ps2x.config_gamepad(13,11,10,12);   //setup GamePad(clock, command, attention, data) pins, check for error
 
 if(error == 0){
   Serial.println("Found Controller, configured successful");
   Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
  Serial.println("holding L1 or R1 will print out the analog stick values.");
  Serial.println("Go to www.billporter.info for updates and to report bugs.");
 }
   
  else if(error == 1)
   Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
   Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
   
   //Serial.print(ps2x.Analog(1), HEX);
 
 
 ps2x.enableRumble();              //enable rumble vibration motors
 ps2x.enablePressures();           //enable reading the pressure values from the buttons. 
}

void loop()
{
  myservo1.attach(A1);  // set the control pin of servo 1 to A1
  myservo2.attach(A0);  //set the control pin of servo 2 to A0
  myservo3.attach(8);   //set the control pin of servo 3 to D6
  myservo4.attach(9);   //set the control pin of servo 4 to D9
  
 if(error != 0)
  return; 
  
  ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
  
  if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed
       Serial.println("Start is being held");
  if(ps2x.Button(PSB_SELECT))
       Serial.println("Select is being held");
       
       
   if(ps2x.Button(PSB_PAD_UP)) {         //will be TRUE as long as button is pressed
     Serial.print("Up held this hard: ");
     Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
    }
    if(ps2x.Button(PSB_PAD_RIGHT)){
     Serial.print("Right held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
    }
    if(ps2x.Button(PSB_PAD_LEFT)){
     Serial.print("LEFT held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
    }
    if(ps2x.Button(PSB_PAD_DOWN)){
     Serial.print("DOWN held this hard: ");
   Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
    }   

  
    vibrate = ps2x.Analog(PSAB_BLUE);        //this will set the large motor vibrate speed based on 
                                            //how hard you press the blue (X) button    
  
  if (ps2x.NewButtonState())               //will be TRUE if any button changes state (on to off, or off to on)
  {
      if(ps2x.Button(PSB_R3))
      {
        //Serial.println("R3 pressed");
        //record
        s1=myservo1.read();
        delay(100);
        Serial.println(s1);
        s2=myservo2.read();
        delay(100);
        Serial.println(s2);
        s3=myservo3.read();
        delay(100);
        Serial.println(s3);
        s4=myservo4.read();
        delay(100);
        Serial.println(s4);
      
        jiyi1[i]=s1;  //save the servo value read in the array sequentially
        jiyi2[i]=s2;
        jiyi3[i]=s3;
        jiyi4[i]=s4;
        i++;
        j=i;
       // delay(100);
       Serial.println(i);
      }
      
       // carry out
      if(ps2x.Button(PSB_L3))
      {
        //Serial.println("L3 pressed");
        i=0;
        tt=1;
   
       pos1 = myservo1.read();  // record the angle value of 4 servo posture
       pos2 = myservo2.read();
       pos3 = myservo3.read();
       pos4 = myservo4.read();

     while(tt==1)  // repeat the actions
     {
       for(int k=0;k<j;k++)   //for loop, to execute all the stored actions.
      {
        if(pos1<jiyi1[k])   // if the current servo 1 angle is less than the value stored in array 1. 
        {
          while(pos1<jiyi1[k])    //while loop, make servo turn to the position of value stored in the array.
          {
            myservo1.write(pos1);   //servo 1 executes the action
            delay(5);     //delay 5ms，controlling the rotating speed of servo.
            pos1++;
            //Serial.println(pos1);
          }
        }
        else     //if the current servo 1 angle is greater than the value stored in array 1.
        {
         while(pos1>jiyi1[k])     //while loop, make servo turn to the position of value stored in the array.
          {
            myservo1.write(pos1);    //servo 1 executes the action
            delay(5);           //delay 5ms，controlling the rotating speed of servo.
            pos1--;
            //Serial.println(pos1);
          }
        
//**********************************************
// the same analysis as the previous servo
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
 //*****************************************************
// the same analysis as the previous servo
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
 //*****************************************************   
// the same analysis as the previous servo
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
    //*******************************************************
    // exit the looping
     ps2x.enableRumble();              //enable rumble vibration motors
     ps2x.enablePressures();
     ps2x.read_gamepad(false, vibrate); 
     vibrate = ps2x.Analog(PSAB_BLUE);
      if (ps2x.NewButtonState())               //will be TRUE if any button changes state (on to off, or off to on)
      {
        if(ps2x.Button(PSB_R3))
        {
          tt=0;
          i=0;
          break;
        }
      }
   //*********************************************************
   }
  }

      if(ps2x.Button(PSB_L2))
       Serial.println("L2 pressed");
      if(ps2x.Button(PSB_R2))
       Serial.println("R2 pressed");
      if(ps2x.Button(PSB_GREEN))
       Serial.println("Triangle pressed");
       
  }   
       
  
  if(ps2x.ButtonPressed(PSB_RED))             //will be TRUE if button was JUST pressed
       Serial.println("Circle just pressed");
       
  if(ps2x.ButtonReleased(PSB_PINK))             //will be TRUE if button was JUST released
       Serial.println("Square just released");     
  
  if(ps2x.NewButtonState(PSB_BLUE))            //will be TRUE if button was JUST pressed OR released
       Serial.println("X just changed");    

    //turn
    zhuandong();
    //claw
    zhuazi();
    // lower arm
    dabi();
    // upper arm
    xiaobi();
  
  if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) // print stick values if either is TRUE
  {
      Serial.print("Stick Values:");
      Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX  
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_LX), DEC); 
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_RY), DEC); 
      Serial.print(",");
      Serial.println(ps2x.Analog(PSS_RX), DEC); 
  } 
    
 delay(5);
}

//********************************************************************
// turn 
void zhuandong()
{
// turn right
   if(ps2x.Analog (PSS_RX) > 200)  // if push the right joystick to the right
    {
      //Serial.println(ps2x.Analog(PSS_RX), DEC);
      pos1=pos1-1;    //pos1 subtracts 1
      myservo1.write(pos1);   // servo 1 carries out the action, the robot arm turns right.
      // delay(5);
      if(pos1<1)   // limit the right turning angle
      {
        pos1=1;
      }
     }
      // turn left
     if(ps2x.Analog (PSS_RX) < 50)    // if push the right joystick to the left
     {
       //Serial.println(ps2x.Analog(PSS_RX), DEC);
       pos1=pos1+1;   //pos1 plus 1
       myservo1.write(pos1);     // the robot arm turns left 
       // delay(5);
       if(pos1>180)     // limit the left turning angle
       {
         pos1=180;
       }
     }
 }
 //**********************************************************************  
 // the upper arm 
void xiaobi()
{
  // upper arm front
   if(ps2x.Analog(PSS_RY)<50)  // if push the right joystick upward
   {
      pos2=pos2-1;
      myservo2.write(pos2);    // the upper arm will lift up
      delay(5);
      if(pos2<0)    // limit the lifting angle 
      {
        pos2=0;
      }
    }
    // upper arm back
    if(ps2x.Analog(PSS_RY)>200)    //if push the right joystick to downward
    {
      pos2=pos2+1;
      myservo2.write(pos2);   // the robot arm will go down
      delay(5);
      if(pos2>180)  // limit the declining angle
      {
        pos2=180;
      }
    }
}
//***************************************************************
void zhuazi()
{
// close the claw
   if(ps2x.Analog(PSS_LX)>220)   // if push the left joystick to the right  
   {
      pos4=pos4-1;
      Serial.println(pos4);
      myservo4.write(pos4);  // servo 4 carries out the action and claw is gradually closed 
      delay(5);
      if(pos4<0)   // if pos4 value subtracts to 37, the claw in 37 degrees we have tested is closed.）
      {
        pos4=0;
      }
    }
    // open the claw
    if(ps2x.Analog(PSS_LX)<10)   //  if push the left joystick to the left
    {
      pos4=pos4+8;
      Serial.println(pos4);
      myservo4.write(pos4);   //  servo 4 carries out the action and claw is gradually opened
      delay(5);
      if(pos4>108)    // limit the maximum angle opened
      {
        pos4=108;
      }
    }
} 
//*********************************************************
void dabi()
{
  // lower arm front
  if(ps2x.Analog(PSS_LY)>200)  // if push the left joystick upward
  {
    pos3=pos3+1;
    myservo3.write(pos3);  //  the lower arm will stretch out
    delay(5);
    if(pos3>180)   // limit the stretched angle 
    {
      pos3=180;
    }
   }
  if(ps2x.Analog(PSS_LY)<10)    // if push the left joystick downward
  {
    pos3=pos3-1;
    myservo3.write(pos3);   // the lower arm will draw back 
    delay(5);
    if(pos3<35)    //  limit the retracted angle 
    {
      pos3=35;
    }
   }
}
```

**Test Result:**

Stack the shield onto Arduino and upload the code. Powered on and connected the PS2 Joypad, you can use the PS2 Joypad to control the robot arm memorize several postures, looping.



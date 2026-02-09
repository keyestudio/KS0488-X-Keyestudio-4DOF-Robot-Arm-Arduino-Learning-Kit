## Project 4: Assembly Guide

**The initial angles of the four servos are as follows:**

|        **Item**         | **Angle** |
| :---------------------: | :-------: |
| Servo1（Servo on base） |    90°    |
|  Servo2（Left Servo）   |    60°    |
|  Servo3（Right Servo）  |   130°    |
| Servo4（Servo of claw） |    0°     |

**Step1: Assemble the base**

1\. Firstly, you should prepare the components as follows:

  - 4pcs M3*10MM dual-pass hex copper posts
  - 4pcs M3*6MM round head screws
  - An Acrylic board

（<span style="color: rgb(255, 76, 65);">Note the orientation of this acrylic board</span>）

![](media/0d4656b4d6212acf82f63146bda948f6.png)

![2](media/68e6cf4930f6d7ca184acc5c046d5154.jpeg)Accessory 1

2\. Assemble screws and copper posts on this acrylic board. Components needed as below:

  - 2pcs M3*10MM flat head screws
  - 2pcs M3 hex nuts
  - Accessory 1
  - A battery holder

Install the batter holder to the accessory 1, and then we get the accessory 2.

![3](media/5a06c7767191219551efce0e76539ce2.jpeg)

![4](media/76b814dea4ec7147178abe451e3067dc.jpeg)

![5](media/8d54e52e1b6dbad855c272a5608f8f51.jpeg)

![6](media/66ca7bc0888fbdbed0df388303b5c479.jpeg)Accessory 2

3\. Components needed as below:

  - 4pcs M3 * 6MM round head cross screws
  - 4pcs M3 * 45MM dual-pass hex copper posts
  - Accessory 2

Mount copper posts on the accessory 2 with screws to form the accessory 3.

![7](media/d74920d012f84725f48a4dab9075ee11.jpeg)

![8](media/27ae54042e092eb7db5d966a20819c7d.jpeg)

![9](media/79b9cdf429cca147fe55510d35e117ab.jpeg)Accessory 3

4\. Components needed as below:

  - 2 pcs M2 * 8MM round head screws
  - 2 pcs M2 nuts
  - 1 pcs 180°servo
  - 1 Acrylic board

First set the servo to 90 °, set the servo’s angle to 90 °, stack the servo motor driver shield onto the Arduino control board, and connect the servo to the motor driver shield.

![](media/44b4246336b2d36a86dcffc27809b5a1.png)

Upload the test code to the servo motor driver shield to make the 180°servo rotate 90° via Arduino software. When setting the servo angle, connect the servo to the A0 end of the shield(there is a silk screen on the back of the shield), upload the corresponding code, plug in power and press the reset button. Then the servo can be removed when turning to 90°。

<span style="color: rgb(255, 76, 65);">Set the servo to **90°**</span>

```c
#include <Servo.h>
Servo myservo;  // create servo object to control a servo

void setup()
{
  myservo.attach(A0);  // modify each pin to adjust 
  myservo.write(90);  // angle value  
  delay(1000);
}

void loop() 
{

}
```

![](media/ce101b6a2b40de8f8769337454406578.png)

Remove the servo, then install it on the acrylic board with 2 pcs M2\*8MM round head screws and 2 pcs M2 nuts. Finally, we get the accessory 4.

![10](media/6c9641813f05682bb9485fc28ceb8efc.jpeg)

![11](media/0e9b7ed4d04b6a9c6f35f8e4ea1330bf.jpeg)

![12](media/a73a9cde9017969c1131715291aa6054.jpeg)Accessory 4

5\. Assemble the accessory 4 onto the accessory 3 with 4pcs M3 * 6MM round head screws to form the accessory 5.

![13](media/753917572ff419e2afb834dd4bd8282b.jpeg)

![14](media/b1c94e0dd1e3fa6ac8df625be6132868.jpeg)Accessory 5

**Step 2: Assemble the front part of the robot arm**

![Step-07](media/43a7b0a0072b9722cc78f27a6f8742ae.png)accessory 19

**Step 3: Fix the accessory 5 and the accessory 19 together with 1 pcs M2 * 5 screw. Then we get the accessory 20**

![47](media/6410ac51e6a3c2ac9d3b08d386e468cb.jpeg)

![48](media/8fb41a96ed3ce5b0bf3377f11fae18ec.jpeg)Accessory 20

**Step 4: Next, we need to use 8pcs M3 * 6MM round-head screws and 4pcs M3 * 10MM dual-pass hex coppers pillars to install the Arduino control board onto the accessory 20 and stack the servo motor driver shield onto the control board. Then we get the accessory 21**

![17](media/a245b27a1391302239d296de862e5419.jpeg)

![](media/031291924e3d960106048792b0916373.png)

![](media/1eb9baf8b45c9746502c9d5c6c741fa0.png)

At last, the front part of the robot arm is installed successfully.

![](media/642a509d588921a941b152966fc671fc.png)Accessory 21

**Step 5: Then we interface the servo with the corresponding ports of servo motor driver shield. The wiring method is shown below, and the accessory 22 is generated**

![](media/c19bcdd5f7993cbc50e2db937f598571.png)

The brown wire of the servo1 (Base Servo) is connected to G, the red wire is connected to V, and the orange one is connected to S (A1). As shown in the figure below:

![](media/3130aa144ab982aff097398b8ae8951e.png)

The brown wire of the servo 2(left) is interfaced to G，the red wire to V and the orange one to S（A0）. As shown in the figure below:

![](media/ac51730e09817f0c74f37533efcdb519.png)

The brown wire of the Servo 3(right)）is interfaced with G，the red wire with V and the orange one with S(8). As shown in the figure below:

![](media/84b467f5a98ba0e3499e427e4f0bbeac.png)

Interface the brown wire of servo 4 with G, the red one with V and the orange one to S (9) with three M-F Dupont wires. As shown in the figure below:

![](media/dea1085f6e793f3f9c861b1ce9a5f990.png)

![](media/fa82cfca15a0005b19238ee3b389bf27.png)Accessory 22

**Step 6: Install the control part of the robotic arm**

Prepare the following components as below:

  - 6pcs M3 * 10MM double-pass hexagonal copper posts,

  - 10pcs M3 * 6MM round head cross screws

  - 2pcs joystick modules

  - A blue acrylic board

Fix the above components together to generate the accessory 23.

![09_01](media/b9bca43c1bb8b37d325f3fd37767101b.png)

![09_02](media/66a053175d1c26b8ecddc331b61d19f8.png)

![09_04](media/d4876de708393f1402547341ba36a9eb.png)

![09_05](media/0ecbb92e4ff7804c9fe28e53accd4d98.png)Accessory 23

Connect the accessory 22 and the accessory 23 together with a f-f DuPont wire, according to the following connection diagram.

![](media/526a7d846db04d20ea8b0156c3cde101.png)

On the driver shield, pin G and V of joystick modules are separately connected to G, V；

Pin X (X axis), Y (Y axis) and B(Z axis) of the right joystick module are separately connected to S（A2), S (A5) and S (7).

Pin X, Y and B of the left joystick module are separately connected to S (A3), S (A4) and S (6).

![](media/526a7d846db04d20ea8b0156c3cde101.png)

On the driver shield, pin G and V of joystick modules are separately connected to G,V；

Pin X (X axis), Y (Y axis) and B(Z axis) of the right joystick module are separately connected to S（A2), S (A5) and S (7).

Pin X, Y and B of the left joystick module are separately connected to S (A3), S (A4) and S (6).

**<span style="color: rgb(255, 76, 65);">Note:</span>** Refer to the following figure:

![](media/8a0c1d7927b092fe29be104dcd034fab.png)

![](media/d3c514d1bc72f5098875b671bfe75ec8.jpeg)

**Complete rendering**

![](media/e1d6d4cc1e21055084c67af12c23386b.jpeg)

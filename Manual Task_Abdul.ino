#include <Servo.h>
#include <Stepper.h>

#define STEPS 32
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
Stepper stepper(STEPS, IN4, IN2, IN3, IN1);
#define joystick A1
Servo servo1;

int joyX = 0;
int joyY = 1;
  
int servoVal;
int angle=0;
void setup() 
{
  servo1.attach(5);
}
  
void loop()
{
  
  servoVal = analogRead(joyX);
  servoVal = map(servoVal, 0, 1023, 0, 180);
  if (servoVal > 175){
    angle=angle-1;
    servo1.write(angle);
  }

   if (servoVal < 25 ){
    angle=angle+1;
    servo1.write(angle);
  }
 // servo1.write(servoVal);

  int val = analogRead(joystick);
if( (val > 500) && (val < 523) )
{
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, LOW);
}
else
{
// move the motor in the first direction
while (val >= 523)
{
// map the speed between 5 and 500 rpm
int speed_ = map(val, 523, 1023, 5, 500);
// set motor speed
stepper.setSpeed(speed_);
 
// move the motor (1 step)
stepper.step(1);
 
val = analogRead(joystick);
}
 
// move the motor in the other direction
while (val <= 500)
{
// map the speed between 5 and 500 rpm
int speed_ = map(val, 500, 0, 5, 500);
// set motor speed
stepper.setSpeed(speed_);
 
// move the motor (1 step)
stepper.step(-1);
 
val = analogRead(joystick);
}
}

}

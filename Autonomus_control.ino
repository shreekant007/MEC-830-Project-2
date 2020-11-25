#include <Stepper.h>//Call the stepper.h library
#include <Servo.h>//Call the servo.h library
int STEPS = 2048;  // 32steps per revolution

int button = 2;

int Lightsensorleft = A3;
int Lightsensorright = A2;
Servo myservo; //it created an object called myservo.
Stepper mystepper(STEPS, 8, 10, 9, 11);// Setup of proper sequencing for Motor Driver Pins In1, In2, In3, In4 in the sequence 8-10-9-11
long previousMillis = 0;
unsigned long currentMillis = 0;

// adjust timing based on your length of the path
long forward = 10000;//10 seconds go forward
long turn = 7000;//7 seconds to rotate 90degree CW
long forward2 = 10000;//10 seconds go forward
long turn2 = 7600;//7 seconds to rotate 90degree CCW
long forward3 = 10000;//10 seconds go forward

void setup()
{ Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);//button input
  myservo.attach(12);//set pin 12 as the output for servo
  mystepper.setSpeed(10);//set stepper motor speed to 10 rpm
  myservo.write(85);//set the servo angle to 85 degree
}

void loop()
{
  //if button #2 is pressed start running the code
  if (digitalRead(2) == LOW)
  {
    //go from p0-p1
    currentMillis = millis();//get the present time and store it in variable currentMillis
    while (millis() - currentMillis <  forward) //run the code while the time is less than 10 seconds 
    {
      mystepper.step(204);//stepper motor takes zero steps
      myservo.write(85);
    }
    
    // Rotate at P1
    currentMillis = millis();//get the present time again and store it in variable currentMillis
    while (  millis() - currentMillis < turn) //run the code while the time is less than 7 seconds
    {
      myservo.write(5);
      mystepper.step(204);//stepper motor takes zero step
    }
    
     //go from p1 to p2
    currentMillis = millis();
    while ( millis() - currentMillis < forward2) //run the code while the time is less than 10 seconds
    {
      mystepper.step(204);//stepper motor takes zero steps
      myservo.write(85);
    }
    
    // Rotate at P2
    currentMillis = millis();
    while ( millis() - currentMillis < turn2) //run the code while the time is less than 7.6 seconds
    {
      mystepper.step(204);//stepper motor takes zero steps
      myservo.write(178);
    }
    
    // go from p2 to p3
    currentMillis = millis();
    while (millis() - currentMillis < forward3) //run the code while the time is less than 10 seconds
    {
      mystepper.step(204);//stepper motor takes zero steps
      myservo.write(85);
    }

  }
}

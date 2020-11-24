#include <Stepper.h>//Call the stepper.h library // test
#include <Servo.h>//Call the servo.h library

const int STEPS = 32;  // 32steps per revolution
const int xaxis = 1; // connect analog pin 1 to X axis in joystick
const int yaxis = 0;// connect analog pin 2 to Y axis in joystick

Servo myservo; //it created an object called myservo.
Stepper myStepper(STEPS, 8, 10, 9, 11);// Setup of proper sequencing for Motor Driver Pins In1, In2, In3, In4 in the sequence 8-10-9-11

void setup()
{
  myservo.attach(12);//set pin 12 as the output for servo
  //myservo.write(90);// Set the servo at 90degree so the bar is in the center
}

void loop()
{
  int a = analogRead(xaxis);//Get the analog reading from pin A1 and store in variable "a"
  int b = analogRead(yaxis);//Get the analog reading from pin A0 and store in variable "b"
  int speedstepper;// Create a variable for stepper speed
  int speedservo;// Create a variable for servo speed
   delay(100);

  if (b >= 450 && b <= 545)// when the joystick is in neutral position
  {
    myStepper.step(0);//stepper motor takes zero steps
     
  }

  else
  {
    while (b < 450) // if goes backwards the value is between 0 - 450. So, make the stepper motor turn
    {
      speedstepper = map(b, 450, 0, 5, 500);//Map the speed according to joystick position
      myStepper.setSpeed(speedstepper);//Set stepper motor speed
      myStepper.step(1);//Make the stepper motor take 1 steps
      b = analogRead(yaxis);
      
    }
   while (b > 545)//if goes forward the value is between 545 - 1023. So, make the stepper motor turn
    {
      speedstepper = map(b, 545, 1023, 5, 500);//Map the speed according to joystick position
      myStepper.setSpeed(speedstepper);//Set stepper motor speed
      myStepper.step(-1);//Make the stepper motor take -1 steps
      b = analogRead(yaxis);
   
  
    }
  }
    /* Control the Servo*/
  speedservo = map(a, 0, 1023,0, 180); // servo value between 0-180, joy stick value between 0 - 1023. So, map speed accordingly
    myservo.write(speedservo); // sets the servo position according to the joystick value
    delay(100);
  
   
}

#include <Stepper.h>//Call the stepper.h library
#include <Servo.h>//Call the servo.h library
int STEPS = 2048;  // 32steps per revolution
int trigpin = 6; // trig pin set to pin 8
int echopin = 7; // echo pin set to pin 9
int button = 3;// assign pin 3 to button 
int Input, duration, distance;// Variables
Servo myservo; //it created an object called myservo.
// Setup of proper sequencing for Motor Driver Pins In1, In2, In3, In4 in the sequence 8-10-9-11
Stepper mystepper(STEPS, 8, 10, 9, 11);
long previousMillis = 0;
unsigned long currentMillis = 0;

// adjust timing based on your length of the path
long forward = 12000;//10000 seconds go forward
long turn = 1000;//7 seconds to rotate 90degree CW
long forward2 = 8000;//600010 seconds go forward
long turn2 = 9000;
long forward3 = 25000;
void setup()
{ Serial.begin(9600);
  pinMode(trigpin, OUTPUT); //sets the trigpin as the output
  pinMode(echopin, INPUT); //sets the echo pin as the input
  pinMode(3, INPUT_PULLUP);//button input
  myservo.attach(12);//set pin 12 as the output for servo
  mystepper.setSpeed(14);//set stepper motor speed to 10 rpm
  myservo.write(93);//set the servo angle to 85 degree
}

void loop()
{
  //if button #2 is pressed start running the code
  if (digitalRead(3) == 0)
  {
    Input = sensor();// get reading from ultra sonice sensor and store it variable Input
    previousMillis = millis();// store current time in variable previousMillis
    while (Input > 10)// run the stepper motor if the input reading is above 10cm
    {
      mystepper.step(350);//stepper motor takes 350 steps
      myservo.write(93);//Servo angle is set to 93 degrees
      Input = sensor();// Get sensor reading
      if (Input < 10)//If loop to break the while loop if object is detected
      {
        break;
      }
    }
    if ( Input < 10 )//if loop to avoid obstacle
    {
      delay(500);
      currentMillis = millis();//get the present time again and store it in variable currentMillis
      while (  millis() - currentMillis < 1000) //run the code while the time is less than 1 seconds
      {
        myservo.write(35);//set the servo angle to 35 degree
        mystepper.step(350);//stepper motor takes 350 step
      }

      currentMillis = millis();
      while ( millis() - currentMillis < 6000) //run the code while the time is less than 6 seconds
      {
        mystepper.step(350);//stepper motor takes 350 steps
        myservo.write(92);//set the servo angle to 92 degree
      }

      currentMillis = millis();
      while ( millis() - currentMillis < 8000) //run the code while the time is less than 8 seconds
      {
        mystepper.step(350);//stepper motor takes 350 steps
        myservo.write(125);//set the servo angle to 125 degree
      }
      
      currentMillis = millis();
      while (millis() - currentMillis < 7800) //run the code while the time is less than 7.8 seconds
      {
        mystepper.step(350);//stepper motor takes 350 steps
        myservo.write(92);//set the servo angle to 92 degree
      }
      currentMillis = millis();
      while ( millis() - currentMillis < 1900) //run the code while the time is less than 10 seconds
      {
        mystepper.step(350);//stepper motor takes 350 steps
        myservo.write(35);//set the servo angle to 35 degree
      }
      while ( millis() - previousMillis < 65000) //run the code while the time is less than 65 seconds
      {
        mystepper.step(350);//stepper motor takes 350steps
        myservo.write(92);//set the servo angle to 92 degree
      }
      currentMillis = millis();
      while ( millis() - currentMillis < 60000) //run the code while the time is less than 60 seconds
      {
        mystepper.step(0);//stepper motor takes zero steps
        myservo.write(92);//set the servo angle to 92 degree
      }
    }
  }
}

double sensor()
{
  // Code for running the Ultrasonic sensor //
  digitalWrite(trigpin, LOW); //clears the trig pin
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH); //sets the trig pin on high for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW); //clears the trig pin
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echopin, HIGH); // duration for pulse to reach detector (in microseconds)
  distance =  duration * 0.034 / 2; // ((0.034cm/us)/2) x duration in microsecond.
  distance = constrain(distance, 0, 15);
  return (distance); // position of servo motor
}

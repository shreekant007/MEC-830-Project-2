#include <Stepper.h>
#include <Servo.h>

int x, y, z;

// Define Stepper

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

// Define Servo

Servo myServo;

// Define Joystick

const int X_pin = 1; // analog Pin Connected to X Output
const int Y_pin = 0; // analog Pin Connected to Y Output

void setup() {
  myStepper.setSpeed(10);   // set the speed at 10 rpm:
  myServo.attach(6);
  myServo.write(50);
  Serial.begin(9600);
}

void loop() {
   // Change in front back Stepper
   y = analogRead(Y_pin);
   y = map(y, 0, 1023, -100, 100);

   x = analogRead(X_pin);
   x = map(x, 0, 1023, -100, 100);

   if (x > 5) {
      myServo.write(x);
   }
    else if (x < -5) {
      myServo.write(x);
   }
   
   if (y > 5) {
      myStepper.step(y);
   }
   else if (y < -5) {
      myStepper.step(y);
   }
   //myStepper.step(y);
   Serial.println(y);
   Serial.println(x);
}

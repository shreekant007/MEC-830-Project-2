#include "Stepper.h"
#include <Servo.h>
#define STEPS  2038   // Number of steps per revolution of Internal shaft
Stepper small_stepper(STEPS, 8, 10, 9, 11);

int left_photo; 
int right_photo;
Servo myservo;
volatile int current_servo_angle;
Servo servo2; 

int need_vertical_adjustment; 
int max_light;
int best_angle;
int new_light; 

int angle; 
int start_angle= 0 ;
int resolution = 3;
float servo_adjustment;
int stepper_adjustment;
int new_angle;
//start angle = 20 is facing forward
// negative goes left


// Arduino pin numbers
const int SW_pin = 4; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output

volatile float x_desired;
volatile float y_desired;
// calibration
// default (no motion) x = 515, y = 510
// max y = 1023, 0
// max x = 1023, 0 

// servo: middle angle set to 45 deg. max left: 0, max right: 90 
// max stepper steps: 500, min 0 

void setup(){

  small_stepper.setSpeed(15);
  myservo.write(start_angle);
  myservo.attach(6);
  servo2.attach(5);
////  need_vertical_adjustment = 0;
  Serial.begin(9600);
  current_servo_angle = myservo.read();
  Serial.println(current_servo_angle);

} 

void loop() {  
//  small_stepper.step(-100);
   x_desired = analogRead(X_pin);
   y_desired = analogRead(Y_pin);
   Serial.println(x_desired);
   Serial.println(y_desired);
   current_servo_angle = myservo.read();

// change these values according to your calibration
// im also using continuous servo instead of stepper so the mapped speeds have to be changed accordingly
// (for cont servo, 0 is max speed CW, 180 is max speed CCW, 90 is no motion)

//   have margin of error for y and x so it doesnt move when there's slight change in analog signal
   if (y_desired < 500 or y_desired > 550){
    stepper_adjustment = map(y_desired, 0, 1023, 150, 30);
//    small_stepper.step(stepper_adjustment); // use this if stepper
    servo2.write(stepper_adjustment);
   }

   else {
//    small_stepper.step(0);
    servo2.write(90);
   }

  
   if (x_desired < 510 or x_desired > 520){
       //   max servo movement = 2,  min = -2
       servo_adjustment = map(x_desired, 0, 1023, -2, 2); // do servo adjustment in increments
       new_angle = current_servo_angle + servo_adjustment; 
    // don't forget to constrain servo!
       if (new_angle <= 90 and new_angle >= 0){ 
        myservo.write(new_angle);
       }
   }
   delay(10); 
}

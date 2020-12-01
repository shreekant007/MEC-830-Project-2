#include "Stepper.h"
#include <Servo.h>
#include "SR04.h"
#define TRIG_PIN 10
#define ECHO_PIN 9
#define STEPS  2038   // Number of steps per revolution of Internal shaft
//Stepper small_stepper(STEPS, 8, 10, 9, 11); 
Servo myservo;
Servo servo2; 
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);

float distance;
int left_photo; 
int right_photo;
volatile int current_servo_angle;
int need_vertical_adjustment; 
int max_light;
int best_angle;
int new_light; 

int angle; 
int start_angle= 0; //start angle = 0 is facing forward
int resolution = 2;
float servo_adjustment;
int stepper_adjustment;
int new_angle;
int BUTTON_1 = 11;
int BUTTON_2 = 13;

// negative goes left

// Arduino pin numbers
const int SW_pin = 4; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output

volatile float x_desired;
volatile float y_desired;
// calibration

// servo: middle angle set to 45 deg. max left: 0, max right: 90 
// max stepper steps: 500, min 0 

unsigned long currentMillis = 0;
long right_turn = 3000;//10 seconds go forward
long left_turn = 3000;
long right_forward = 2000;
long forward = 4000;

void setup(){
  pinMode(BUTTON_1, INPUT_PULLUP);
//  small_stepper.setSpeed(15);
  myservo.write(start_angle);
  myservo.attach(6);
  servo2.attach(5);
////  need_vertical_adjustment = 0;
  Serial.begin(9600);
  current_servo_angle = myservo.read();
  Serial.println(current_servo_angle);

} 

// this one uses continuous servo. replace all code with servo2 with stepper motor

void loop() {  
  if (digitalRead(BUTTON_1) == LOW){
    current_servo_angle = myservo.read();
    for (int angle=current_servo_angle; angle<=45; angle+=resolution){
        myservo.write(angle);
        delay(20);
    }
//    servo2.write(120);
    Serial.println("Hello");
    
//    // have an emergency button to stop
//    if (digitalRead(BUTTON_2) == LOW){
//        servo2.write(90);
//        current_servo_angle = myservo.read();
//        for (int angle=current_servo_angle; angle>=start_angle; angle-=resolution){
//            myservo.write(angle);
//            delay(20);
//        }
//        Serial.println("Exit code");
//        break;
//    }

// forward
    currentMillis = millis();
    while (millis() - currentMillis < 3000){
      Serial.println("robot move forward");
      servo2.write(120);   
    }
    servo2.write(90);
    
    currentMillis = millis();
    current_servo_angle = myservo.read();

    // right turn 
    for (int angle=current_servo_angle; angle<=90; angle+=resolution){
      Serial.println("wheel right turn");
      myservo.write(angle);
      delay(20);
    }
    
    currentMillis = millis();
    
    while (millis() - currentMillis < right_turn){
      Serial.println("robot turn right");
      servo2.write(120);  
    }

    servo2.write(90);
    
    current_servo_angle = myservo.read();
    for (int angle=current_servo_angle; angle>=45; angle-=resolution){
      Serial.println("wheels turn to middle");
      myservo.write(angle);
      delay(20);
    }
    
    currentMillis = millis();
    while (millis() - currentMillis < 1000){
      Serial.println("robot move forward");
      servo2.write(120);   
    }
    servo2.write(90);
//    left turn
    current_servo_angle = myservo.read();
    Serial.println(current_servo_angle);
    
    for (int angle=current_servo_angle; angle>=0; angle-=resolution){
      Serial.println("wheels left turn");
      myservo.write(angle);
      delay(20);
    }

    currentMillis = millis();
    while (millis() - currentMillis < 2500){
      Serial.println("robot left turn");
      servo2.write(120);  
    }

    servo2.write(90);
    current_servo_angle = myservo.read();
    for (int angle=current_servo_angle; angle<=45; angle+=resolution){
      Serial.println("wheels turn to middle");
      myservo.write(angle);
      delay(20);
    }
    
    currentMillis = millis();
    while (millis() - currentMillis < 3000){
      Serial.println("robot move forward");
      servo2.write(120);   
    }
    servo2.write(90);
    }
    current_servo_angle = myservo.read();
    for (int angle=current_servo_angle; angle>=start_angle; angle-=resolution){
        myservo.write(angle);
        delay(20);
    }
    servo2.write(90);
}

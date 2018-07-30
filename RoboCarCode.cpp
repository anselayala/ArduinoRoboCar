#include "motordriver_4wd.h"
#include <seeed_pwm.h>
#include "Ultrasonic.h"

volatile long left_encoder_count = 0, right_encoder_count = 0;
int left_dirn = 1, right_dirn = 1;
int loopCount = 0;
int oneTurn = 34;
int ninty = 65;
int once = 0;
bool trappin = true;
bool sky = true;
Ultrasonic ultrasonic(11);
long RangeInCentimeters;

void setup()
{
  MOTOR.init();
  attachInterrupt(0, LeftEncoder, CHANGE);
  attachInterrupt(1, RightEncoder, CHANGE);
  Serial.begin(9600);
  while (!Serial)
  {
    //Do nothing is no port is read
  }
}

void loop()
{
  RangeInCentimeters = ultrasonic.MeasureInCentimeters();
  if (loopCount > 0) {
    delay(1000);
    stoop();
    if(RangeInCentimeters < 150 ){
      moveReverse(28, oneTurn);
    }
    else{
      turnRight(25, ninty);
      moveReverse(25, oneTurn*5);
     
    }
    stoop();

  } else if (RangeInCentimeters <= 55 && trappin == true) {
    stoop();
    delay(1000);
    turnRight(25, ninty);
  trappin = false;
 // loopCount++;
  }
  else if (RangeInCentimeters < 28 && trappin == false) {
        moveForward(25, oneTurn);
          if (RangeInCentimeters < 12) {
            stoop();    
          }
     loopCount++;
  }
  else {
    moveForward(25, oneTurn);
  }


}

void moveReverse(int speed, int count) {
  while (((left_encoder_count + right_encoder_count) / 2) < count) {

    MOTOR.setSpeedDir1(speed, DIRF);
    MOTOR.setSpeedDir2(speed, DIRR);
  }
  resetEncoder();
}
void moveForward(int speed, int count) {
  while (((left_encoder_count + right_encoder_count) / 2) < count) {

    MOTOR.setSpeedDir1(speed, DIRR);
    MOTOR.setSpeedDir2(speed, DIRF);
  }
  resetEncoder();
}
void turnLeft(int speed, int count) {
  while (((left_encoder_count + right_encoder_count) / 2) < count) {

    MOTOR.setSpeedDir1(speed, DIRF);
    MOTOR.setSpeedDir2(speed, DIRF);
  }
  resetEncoder();
}
void turnRight(int speed, int count) {
  while (((left_encoder_count + right_encoder_count) / 2) < count) {

    MOTOR.setSpeedDir1(speed, DIRR);
    MOTOR.setSpeedDir2(speed, DIRR);
  }
  resetEncoder();
}





//old

void stoop()
{
  MOTOR.setSpeedDir1(0, DIRF);
  MOTOR.setSpeedDir2(0, DIRR);
}

void LeftEncoder()
{
  left_encoder_count = left_encoder_count + left_dirn;
}

void RightEncoder()
{
  right_encoder_count = right_encoder_count + right_dirn;
}

void resetEncoder() {
  right_encoder_count = 0;
  left_encoder_count = 0;
}

void square()
{
  if (loopCount < 4) {
    moveForward(25, oneTurn);
    stoop();
    delay(1000);
    turnLeft(25, ninty);
    stoop();
    delay(1000);
  }

  else {
    stoop();
  }
  loopCount++;
  Serial.println(loopCount);
}

void backForward()
{
  // long RangeInInches;
  //RangeInInches = ultrasonic.MeasureInInches();

  RangeInCentimeters = ultrasonic.MeasureInCentimeters();

  if (RangeInCentimeters < 45) {
    stoop();
    moveReverse(25, oneTurn);
  }

  else if (RangeInCentimeters > 45) {
    stoop();
    moveForward(25, oneTurn);
  }
  else {
    stoop();
  }
  Serial.println(RangeInCentimeters);
  delay(100);

}

//void circle(int diamater)

/*********************************************************************************************************
   END FILE
 *********************************************************************************************************/

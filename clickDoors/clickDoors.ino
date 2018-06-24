#include <Servo.h> 
 
Servo servoLeft;
Servo servoFront;

const int pinServoLeft = 2;
const int pinServoFront = 1;
const int buttonPin = 15;

const int posLeftOpen = 195;
const int posLeftClose = 10;
const int posFrontOpen = 10;
const int posFrontClose = 195;

const int posRefMax = 100;
int pos = 0;

int posLeft(int posRef)
{
  return posLeftOpen + (posRef * (posLeftClose - posLeftOpen)) / posRefMax;
}
int posFront(int posRef)
{
  return posFrontOpen + (posRef * (posFrontClose - posFrontOpen)) / posRefMax;
}
void updateServo(int pos)
{
    servoLeft.write(posLeft(pos));
    servoFront.write(posFront(pos));
}

void setup() 
{ 
  servoLeft.attach(pinServoLeft);
  servoFront.attach(pinServoFront);
  pinMode(buttonPin, INPUT);
}

 
void loop() 
{ 
  int button = digitalRead(buttonPin);
  int incPos = 0;
  if (!button)
    return;
    
  if (pos <= posRefMax / 20)
    incPos = 1;
  if (posRefMax - pos <= posRefMax / 20)
    incPos = -1;

  servoLeft.attach(pinServoLeft);
  servoFront.attach(pinServoFront);

  while(pos > 0 and pos < posRefMax) {
    pos += incPos;
    updateServo(pos);
    delay(15);
  }
  servoLeft.detach();
  servoFront.detach();
} 


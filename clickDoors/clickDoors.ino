#include <Servo.h> 
 
Servo servoLeft;
Servo servoFront;

const int pinServoLeft = 2;
const int pinServoFront = 1;
const int buttonPin = 15;
const int ledPin =  16;

const int posLeftOpen = 195;
const int posLeftClose = 10;
const int posFrontOpen = 10;
const int posFrontClose = 195;

const int posRefMax = 100;
int pos = posRefMax / 2;

int posLeft(int posRef)
{
  return posLeftOpen + (posRef * (posLeftClose - posLeftOpen)) / posRefMax;
}
int posFront(int posRef)
{
  return posFrontOpen + (posRef * (posFrontClose - posFrontOpen)) / posRefMax;
}
void updateServo(int posRef)
{
    servoLeft.write(posLeft(posRef));
    servoFront.write(posFront(posRef));
}

void setup() 
{ 
  servoLeft.attach(pinServoLeft);
  servoFront.attach(pinServoFront);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  updateServo(pos);
  digitalWrite(ledPin, LOW);
}

 
void loop() 
{ 
  int button = digitalRead(buttonPin);
  int incPos = 0;
//  if (!button == LOW)
//    return;
  if (button == HIGH) {
    digitalWrite(ledPin, LOW);
  } else {
    digitalWrite(ledPin, HIGH);
  }
    
  if (pos <= posRefMax / 2 && button == HIGH)
    incPos = 1;
  if (posRefMax - pos <= posRefMax / 2 && button == HIGH)
    incPos = -1;

//  servoLeft.attach(pinServoLeft);
//  servoFront.attach(pinServoFront);

  while(pos > 0 and pos < posRefMax)
  {
    pos += incPos;
    servoLeft.write(pos);
    delay(15);
  }
  incPos = 0;
//  servoLeft.detach();
//  servoFront.detach();
} 


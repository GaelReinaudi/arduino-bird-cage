#include <Servo.h> 
 
Servo servoLeft;
Servo servoFront;

const int pinServoLeft = 2;
const int pinServoFront = 3;
const int buttonPin = 15;
const int ledPin =  16;

const int posLeftOpen = 10;
const int posLeftClose = 195;
const int posFrontOpen = 195;
const int posFrontClose = 10;

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
  delay(500);
  servoLeft.detach();
  servoFront.detach();
  digitalWrite(ledPin, LOW);
}

 
void loop() 
{ 
  int button = digitalRead(buttonPin);
  int incPos = 0;
  if (button == HIGH) {
    digitalWrite(ledPin, LOW);
  } else {
    digitalWrite(ledPin, HIGH);
  }
  if (button == LOW)
    return;
    
  if (pos <= posRefMax / 2 && button == HIGH)
    incPos = 1;
  if (posRefMax - pos <= posRefMax / 2 && button == HIGH)
    incPos = -1;

  if (incPos) {
    servoLeft.attach(pinServoLeft);
    servoFront.attach(pinServoFront);
  }
  while(incPos)
  {
    pos += incPos;
    updateServo(pos);
    delay(20);
    if (pos <= 0 || pos >= posRefMax)
      break;
  }
  servoLeft.detach();
  servoFront.detach();
} 


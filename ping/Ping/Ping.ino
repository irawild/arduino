#include <Servo.h>

Servo myServo;
int MAX_VAL;
const int trigPin = 12;
const int echoPin = 11;
int MIN_DISTANCE = 100;
 
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  myServo.attach(10);
  MAX_VAL = 180;
}
 
void loop()
{
  long duration, inches, cm;
      
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
   
  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
   
  duration = pulseIn(echoPin, HIGH);
   
  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
   
  //Serial.print(inches);
  //Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  if (cm < MIN_DISTANCE)
    {
      myServo.write(10);
      //Serial.print("PWM 511");
      //Serial.println();
    }
   else
   {
      myServo.write(150);
      //Serial.print("PWM 0");
      //Serial.println();
   }
   
  delay(100);
}
 
long microsecondsToInches(long microseconds)
{
// According to Parallax's datasheet for the PING))), there are
// 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
// second).  This gives the distance travelled by the ping, outbound
// and return, so we divide by 2 to get the distance of the obstacle.
// See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}
 
long microsecondsToCentimeters(long microseconds)
{
// The speed of sound is 340 m/s or 29 microseconds per centimeter.
// The ping travels out and back, so to find the distance of the
// object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

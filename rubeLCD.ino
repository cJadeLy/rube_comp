#include <Servo.h>
// Jesse made his code look nice in this header
#include "servo2button.h"

const int pingPin = 38; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 40; // Echo Pin of Ultrasonic Sensor

// Cass is this lazy right now
int one_time_please = 0;
int otherButton = 0;
int oneTwo = 0;

// Convert microseconds to inches
long microsecondsToInches(long microseconds)
{
   return microseconds / 74 / 2;
}

void setup()
{

  // Starting Serial Terminal
  Serial.begin(9600);
  // imput pin for button that Cassidys arduino will detect 
  pinMode(7, INPUT);
   
}

void loop()
{
long duration, inches;
// ultrasonic sensor pins
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   inches = microsecondsToInches(duration);
    // when object is this close the servo motor will lift wrestler to release marbles
   if(inches <= 2 && one_time_please == 0)
   {
    // we are in a loop here and don't really want to set off the motor everytime just the first time
    // this is lazy don't be like me
    one_time_please = 1;
    
    Servo marble_releaser;
    marble_releaser.attach (3);

    delay(10);
    // debug
    Serial.print("got it");
    delay(1);

int pos = 0;
for(pos = 0; pos < 180; pos++)
{
  marble_releaser.write(pos);
delay(10);
}
  for(pos = 180; pos > 0; pos--)
{
  marble_releaser.write(pos);
delay(10);
marble_releaser.detach();
} 
// yay our marbles activated the button!
if(digitalRead(7)== LOW)
{
  // also lazy here. Could use debounce but delay 200 kinda works a little
  delay(200);
  // debug
Serial.print("button!!");
// so lazy to activate other button that jesse's arduino will be waiting to read
otherButton = 1;
delay(10);

}
// first button set second button and we want this to only be true one time on our end. 
if(otherButton == 1 && oneTwo == 0)
{
    oneTwo = 1;
    ServoControl *jesse = new ServoControl(9);
    // push the button!
    jesse->Trigger();

}


   
}
}

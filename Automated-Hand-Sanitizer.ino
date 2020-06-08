/*****************************************************************************
  Author    Continental Electronics
  Version   V1.0
  Copyright www.continental.sg
  All right reserved.
  All text above must be included in any redistribution
*****************************************************************************/

#include <Servo.h>      //Include Servo library

const int servPin = 6;  //Servo receives instructions from the Arduino on Pin 6
const int trigPin = 9;  //Trig on the Ultrasonic Sensor is sent from Pin 9
const int echoPin = 10; //Echo on the Ultrasonic Sensor is received to Pin 10

long duration;          //duration will store the amount of time the ultra sonic sensor's sound wave hits the object and bounce back
int distance;           //distance will calculate the distance away the object was detected by the ultrasonic sensor

Servo myservo;          //Create a Servo object

/* function reads from the ultrasonic sensor and calculates the distance of the object detected */
void ultrasonic() {
  // Clears the trigPin and wait for 2 microseconds
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  /*speed of sound at 343m/s. Divide by 2 because sound wave travels from the sensor,
    hits the oobject and bounce back.*/
  distance = duration * 0.034 / 2;

  // Prints the distance on the Serial Monitor for debugging
  Serial.print("Distance: ");
  Serial.println(distance);
}

void setup() {
  Serial.begin(9600); // Starts the serial communication

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  myservo.attach(servPin); //servo will receive instructions on pin 6 (servPin)
  myservo.write(0); //resets the servo
}
void loop() {

  ultrasonic(); //execute

  if (distance < 20) { //Detect Someone
    myservo.write(180); //turns the servo 180 degree
    delay(1000); //wait for 1 second (1000 milliseconds)
    myservo.write(0); //turns the servo back to 0 degree
  }
  delay(200); //wait for 200 milliseconds
}

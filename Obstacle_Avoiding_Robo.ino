#include <AFMotor.h>   
#include <NewPing.h>  
#include <Servo.h>    

#define trigPin A0 
#define echoPin A1 
#define mDistance 200 
#define mSpeed 255 
#define mSpeedOffset 20

NewPing sonar(trigPin, echoPin, mDistance); 

AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(3, MOTOR12_1KHZ);
Servo myservo;   

boolean goesForward=false;
int distance = 100;
int speedSet = 0;

void setup() {

  myservo.attach(10);  
  myservo.write(115); 
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() {
 int distanceR = 0;
 int distanceL =  0;
 delay(40);
 
 if(distance<=15)
 {
  moveStop();
  delay(100);
  moveBackward();
  delay(300);
  moveStop();
  delay(200);
  distanceR = lookRight();
  delay(200);
  distanceL = lookLeft();
  delay(200);

  if(distanceR>=distanceL)
  {
    turnRight();
    moveStop();
  }else
  {
    turnLeft();
    moveStop();
  }
 }else
 {
  moveForward();
 }
 distance = readPing();
}

int lookRight()
{
    myservo.write(50); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
}

int lookLeft()
{
    myservo.write(170); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
    delay(100);
}

int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  } 
  
void moveForward() {

 if(!goesForward)
  {
    goesForward=true;
    motor1.run(FORWARD);      
    motor2.run(FORWARD);  
   for (speedSet = 0; speedSet < mSpeed; speedSet +=2) 
   {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    delay(5);
   }
  }
}

void moveBackward() {
    goesForward=false;
    motor1.run(BACKWARD);      
    motor2.run(BACKWARD);
  for (speedSet = 0; speedSet < mSpeed; speedSet +=2) 
  {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    delay(5);
  }
}  

void turnRight() {
  motor1.run(FORWARD);
  motor2.run(BACKWARD);    
  delay(450);
  motor1.run(FORWARD);      
  motor2.run(FORWARD);    
} 
 
void turnLeft() {
  motor1.run(BACKWARD);     
  motor2.run(FORWARD); 
  delay(450);
  motor1.run(FORWARD);     
  motor2.run(FORWARD);

}  

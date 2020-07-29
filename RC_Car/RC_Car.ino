/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  Warning: Bluetooth support is in beta!

  You can receive x and y coords for joystick movement within App.

  App project setup:
    Two Axis Joystick on V1 in MERGE output mode.
    MERGE mode means device will receive both x and y within 1 message
 *  ************          Connection:        ************
    HM10 VCC pin ---> Arduino 3.3V
    HM10 GND pin ---> Arduino GND
    HM10 TX pin ---> Arduino D8
    HM10 RX pin ---> 1K Ohm ---> Arduino D9
    HM10 RX pin ---> 2K Ohm ---> GND
 *************************************************************/

/* Comment this out to disable prints and save space */

#define BLYNK_PRINT Serial
#include <SoftwareSerial.h>
SoftwareSerial SwSerial(8, 9); // RX, TX
#include <BlynkSimpleSerialBLE.h>
#include <SoftwareSerial.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "6b84a5adcbbb4aea9b061d95e2b4565e"; // CHANGE THIS!!!

SoftwareSerial SerialBLE(8, 9); // RX, TX

// Clockwise and counter-clockwise definitions.
// Depending on how you wired your motors, you may need to swap.
#define FORWARD  1
#define BACKWARD 0

// Motor definitions to make life easier:
#define M_LEFT 0
#define M_RIGHT 1

// Pin Assignments //
//Default pins:
#define INA1 4
#define INA2 5
#define INB1 6
#define INB2 7
#define DIRA 12 // Direction control for motor A (Left Motor)
#define PWMA 3  // PWM control (speed) for motor A (Left Motor)
#define DIRB 13 // Direction control for motor B (Right Motor)
#define PWMB 11 // PWM control (speed) for motor B (Right Motor)

// Motor Movement variables
// LR Stop 127
// FB Stop 127
int FB = 0;
const int FBhigh = 200;
const int FBlow = 40;
int LR = 0;
const int LRhigh = 140;
const int LRlow = 115;
int leftSpeed = 0;
int rightSpeed = 0;

BLYNK_WRITE(V1) {
  LR = param[0].asInt();
  FB = param[1].asInt();

  // Do something with x and y
  Serial.print("Left/Right = ");
  Serial.print(LR);
  Serial.print("; Forward/Backward = ");
  Serial.println(FB);

  //Motor Code
  if ((LR <= LRhigh) && (LR >= LRlow)) { // not turning
    if ((FB <= FBhigh) && (FB >= FBlow)) { // not moving
      halt(M_LEFT); 
      halt(M_RIGHT); 
    } else if ( FB > FBhigh) { // Moving forward
      drive(M_LEFT, FORWARD, 255); 
      drive(M_RIGHT, FORWARD, 255); 
    } else if (FB < FBlow) { // Moving in reverse
      drive(M_LEFT, BACKWARD, 255); 
      drive(M_RIGHT, BACKWARD, 255); 
    }
  } else if (LR < LRlow) { // Turning Left, so slow left track
    if (FB > FBhigh) { // Moving forward
      drive(M_LEFT, FORWARD, 100); 
      drive(M_RIGHT, FORWARD, 255); 
    } else if (FB < FBlow) { // Moving in reverse
      drive(M_LEFT, BACKWARD, 100); 
      drive(M_RIGHT, BACKWARD, 255); 
    } else if ((FB <= FBhigh) && (FB >= FBlow)) { // Stationary
      drive(M_LEFT, BACKWARD, 200); 
      drive(M_RIGHT, FORWARD, 200); 
    }
  } else if (LR > LRhigh) { // Turning Right, so slow right track
    if (FB > FBhigh) { // Moving forward
      drive(M_LEFT, FORWARD, 255); 
      drive(M_RIGHT, FORWARD, 100); 
    } else if (FB < FBlow) { // Moving in reverse
      drive(M_LEFT, BACKWARD, 255); 
      drive(M_RIGHT, BACKWARD, 100); 
    } else if ((FB <= FBhigh) && (FB >= FBlow)) { // Stationary
      drive(M_LEFT, FORWARD, 200); 
      drive(M_RIGHT, BACKWARD, 200); 
    }
  }
}

void setup() {
  // All pins should be setup as outputs:
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);
  pinMode(INA1, OUTPUT);
  pinMode(INA2, OUTPUT);
  pinMode(INB1, OUTPUT);
  pinMode(INB2, OUTPUT);

  // Initialize all pins as low:
  digitalWrite(PWMA, LOW);
  digitalWrite(PWMB, LOW);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
  digitalWrite(INA1, LOW);
  digitalWrite(INA2, LOW);
  digitalWrite(INB1, LOW);
  digitalWrite(INB2, LOW);

  // Debug console
  Serial.begin(9600);

  SerialBLE.begin(9600);
  Blynk.begin(SerialBLE, auth);

  Serial.println("Waiting for connections...");
}

void loop()
{
  Blynk.run();
}

void drive(byte motor, byte dir, byte spd)
{
  if (motor == M_LEFT)
  {
    digitalWrite(DIRA, dir);
    if(dir && spd){
      digitalWrite(INA1, LOW);
      digitalWrite(INA2, HIGH);
      }
    else if(!dir && spd){
      digitalWrite(INA2,LOW);
      digitalWrite(INA1,HIGH);
      }
    else{
      digitalWrite(INA1, LOW);
      digitalWrite(INA2, LOW);
      }
    analogWrite(PWMA, spd);
  }
  else if (motor == M_RIGHT)
  {
    digitalWrite(DIRB, dir);
    if(dir){
      digitalWrite(INB1,LOW);
      digitalWrite(INB2,HIGH);
      }
      else if(!dir && spd){
        digitalWrite(INB2,LOW);
        digitalWrite(INB1,HIGH);
        }
      else{
        digitalWrite(INB1, LOW);
        digitalWrite(INB2, LOW);
        }
    analogWrite(PWMB, spd);
  }  
}

void halt(byte motor)
{
  drive(motor, 0, 0);
}

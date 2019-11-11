// based on
// https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v40

#include "argon_ble_setup.h"
/*
  Use Adafruit Bluefruit app
  (https://learn.adafruit.com/bluefruit-le-connect/controller)
  Connect to Argon -> controller

  CONFIGURATION
  Motor Controller
    PWMA  - D8
    AIN2  - D7
    AIN1  - D6
    BIN1  - D5
    BIN2  - D4
    PWMB  - D3
    VM - Li
    VC - 3v3
    stby - 3v3



*/

// SYSTEM_MODE(MANUAL);  //uncomment to disable wifi and use BT only

// PIN VARIABLES
// the motor will be controlled by the motor A pins on the motor driver
const int AIN1 = D6;  // control pin 1 on the motor driver for the right motor
const int AIN2 = D7;  // control pin 2 on the motor driver for the right motor
const int PWMA =
    D8;  // speed control pin on the motor driver for the right motor

// the left motor will be controlled by the motor B pins on the motor driver
const int PWMB = D3;  // speed control pin on the motor driver for the left
                      // motor
const int BIN2 = D4;  // control pin 2 on the motor driver for the left motor
const int BIN1 = D5;  // control pin 1 on the motor driver for the left motor

int pinMotorEnable = D2;  // switch to turn the robot on and off

// VARIABLES
int motorSpeed = 125;      // starting speed for the motor
int motorLOWSpeed = 125;   // starting speed for the motor
int motorHIGHSpeed = 255;  // starting speed for the motor
bool isLowSpeed = false;

unsigned long prevTime;

// onDataReceived() is event handler for incoming data via RX characteristic
// When the RXCharacteristic receives data, the event handler is called

// Note: uint8_t is a byte ("unsigned integer of length 8 bits")
void onDataReceived(const uint8_t* data, size_t len, const BlePeerDevice& peer,
                    void* context) {
  /* === START DEBUG PRINTING ===
           uncomment following loop to see commands being sent by app ==
   */
  for (size_t ii = 0; ii < len; ii++) {
    Serial.print(data[ii]);
    Serial.print(" ");
  }
  Serial.println();
  for (size_t ii = 0; ii < len; ii++) {
    Serial.write(data[ii]);
    Serial.print(" ");
  }
  Serial.println();
  /* === END DEBUG PRINTING === */

  if (len > 4) {  // make sure there at least four bytes
    // the command scheme is from the Adafruit Bluefruit app
    // ex: [‘!’] [‘B’] [‘4’] [‘1’] [CRC]
    // https://learn.adafruit.com/bluefruit-le-connect/controller
    if (data[0] == '!' && data[1] == 'B' && data[2] == '5' &&
        data[3] == '1') {  // up presssed {
      carForward(255);
    }
  }
}

void setup() {
  argon_ble_setup();

  // set the motor control pins as outputs
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  Serial.begin(9600);  // begin serial communication with the computer

  // the serial monitor.
}

/********************************************************************************/
void loop() {
  unsigned long currentTime = millis();

  if (currentTime - prevTime >= 2000) {
    carStop();
  } else {
    carForward(255);
  }
}

void leftMotor(int motorSpeed) {
  if (motorSpeed > 0) {
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  } else {
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
  }
  analogWrite(PWMB, abs(motorSpeed));
}

void rightMotor(int motorSpeed) {
  if (motorSpeed > 0) {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
  } else {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
  }
  analogWrite(PWMA, abs(motorSpeed));
}

void carForward(int motorSpeed) {
  rightMotor(motorSpeed);
  leftMotor(motorSpeed);
}
void carBackward(int motorSpeed) {
  rightMotor(-1 * motorSpeed);
  leftMotor(-1 * motorSpeed);
}

void carStop() {
  rightMotor(0);
  leftMotor(0);
}

void carLeft(int motorSpeed) {
  rightMotor(motorSpeed);
  leftMotor(0);
}

void carRight(int motorSpeed) {
  rightMotor(0);
  leftMotor(motorSpeed);
}
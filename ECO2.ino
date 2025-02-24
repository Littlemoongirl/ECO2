#include <IRremote.h>

// Motor pins connected to L298N
int motor1Pin1 = 3;  // IN1
int motor1Pin2 = 4;  // IN2
int motor2Pin1 = 5;  // IN3
int motor2Pin2 = 6;  // IN4

// IR Receiver Pin
int recv_pin = 7;  // Pin where the IR receiver is connected
IRrecv irrecv(recv_pin);
decode_results results;

// IR Codes for buttons
unsigned long forwardCode = 16718055;  // Forward button
unsigned long backwardCode = 16730805;  // Backward button
unsigned long stopCode = 16726215;  // OK button (Stop motors)

void setup() {
  // Set motor control pins as output
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  // Start IR receiver
  irrecv.enableIRIn();
}

void loop() {
  if (irrecv.decode(&results)) {
    long int decCode = results.value;
    irrecv.resume();  // Receive the next value

    // Forward button (Move both motors forward)
    if (decCode == forwardCode) {
      forward();
    }
    // Backward button (Move both motors backward)
    else if (decCode == backwardCode) {
      backward();
    }
    // OK button (Stop the motors)
    else if (decCode == stopCode) {
      stopMotors();
    }
  }
}

// Function to move motors forward
void forward() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

// Function to move motors backward
void backward() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

// Function to stop the motors
void stopMotors() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

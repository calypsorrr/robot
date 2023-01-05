const int controlPin1 = 2; // connected to pin 7 on the H-bridge
const int controlPin2 = 3; // connected to pin 2 on the H-bridge
const int enablePin = 9;   // connected to pin 1 on the H-bridge
const int directionSwitchPin = 4;  // connected to the switch for direction
const int onOffSwitchStateSwitchPin = 5; // connected to the switch for turning the motor on and off
const int potPin = A0;  // connected to the potentiometer's output

// create some variables to hold values from your inputs
int onOffSwitchState = 0;  // current state of the on/off switch
int previousOnOffSwitchState = 0; // previous position of the on/off switch
int directionSwitchState = 0;  // current state of the direction switch
int previousDirectionSwitchState = 0;  // previous state of the direction switch

int motorEnabled = 0; // Turns the motor on/off
int motorSpeed = 0; // speed of the motor
int motorDirection = 1; // current direction of the motor

int endline_check = 0;
int cal = 0;

int sensorValue = 0;

void setup() {
  // initialize the inputs and outputs
  pinMode(directionSwitchPin, INPUT);
  pinMode(onOffSwitchStateSwitchPin, INPUT);
  pinMode(controlPin1, OUTPUT);
  pinMode(controlPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);

  // pull the enable pin LOW to start
  digitalWrite(enablePin, LOW);

  pinMode(A1, INPUT);
  Serial.begin(9600);
}

void loop() {
  calibration();
}


void endline(){
  if ((sensorValue < 30) && (endline_check == 0)){
    analogWrite(enablePin, 0);
      if (directionSwitchState == HIGH) {
      motorDirection = !motorDirection;
      analogWrite(enablePin, motorSpeed);
      //endline_check = !endline_check;
      endline_check = !endline_check;
      Serial.print(endline_check);
      delay(700);
      endline_check = !endline_check;
      Serial.print(endline_check);
    }
  }
 }

void calibration(){
  sensorValue = analogRead(A1);
  Serial.println(sensorValue);
  onOffSwitchState = digitalRead(onOffSwitchStateSwitchPin);
  delay(1);
  if (onOffSwitchState != previousOnOffSwitchState) {
  // change the value of motorEnabled if pressed
    if ((onOffSwitchState == HIGH) && (cal == 0)) {
      digitalWrite(controlPin1, HIGH);
      digitalWrite(controlPin2, LOW);
      analogWrite(enablePin, 40);
      if ((sensorValue < 70) && (cal == 0)) {
          analogWrite(enablePin, 0);
          cal = !cal;
          delay(100); // Wait for 100 millisecond(s)
   }
  }
 }
// save the current on/off switch state as the previous
previousDirectionSwitchState = directionSwitchState;
// save the current switch state as the previous
previousOnOffSwitchState = onOffSwitchState;
}
 
void basic(){
  sensorValue = analogRead(A1);
  //if (cal = !cal){
  // read the value of the on/off switch
  onOffSwitchState = digitalRead(onOffSwitchStateSwitchPin);
  delay(1);
  
  // read the value of the direction switch
  directionSwitchState = digitalRead(directionSwitchPin);
  
  // read the value of the pot and divide by 4 to get a value that can be
  // used for PWM
  motorSpeed = analogRead(potPin) / 4;
  
  // if the on/off button changed state since the last loop()
  if (onOffSwitchState != previousOnOffSwitchState) {
    // change the value of motorEnabled if pressed
    if (onOffSwitchState == HIGH) {
      motorEnabled = !motorEnabled;
  }
  }
  
  // if the direction button changed state since the last loop()
  if (directionSwitchState != previousDirectionSwitchState) {
    // change the value of motorDirection if pressed
    if (directionSwitchState == HIGH) {
      motorDirection = !motorDirection;
    }
  }
  
  // change the direction the motor spins by talking to the control pins
  // on the H-Bridge
  if (motorDirection == 1) {
    digitalWrite(controlPin1, HIGH);
    digitalWrite(controlPin2, LOW);
  } else {
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, HIGH);
  }
  
  // if the motor is supposed to be on
  if (motorEnabled == 1) {
    // PWM the enable pin to vary the speed
    analogWrite(enablePin, motorSpeed);
  } else { // if the motor is not supposed to be on
    //turn the motor off
    analogWrite(enablePin, 0);
  }
  
  // save the current on/off switch state as the previous
  previousDirectionSwitchState = directionSwitchState;
  // save the current switch state as the previous
  previousOnOffSwitchState = onOffSwitchState;
  }

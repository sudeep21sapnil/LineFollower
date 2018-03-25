#define BAUD_RATE 9600
#define SENSOR_COUNT 5
#define DIRECTION_THRESHOLD 200
#define WHITE_THRESHOLD 400
#define BLACK_THRESHOLD 150
#define SPEED_MAX 255
#define SPEED_MIN 0

  int In3 = 8;
  int In4 = 6;
  int leftMotorPin = 5;

  int In1 = 4;
  int In2 = 2;
  int RightMotorPin = 3;

/**SensorPins : left to right**/
int sensorPin[SENSOR_COUNT] = {A1, A2, A3, A4, A5};
int sensorVal[SENSOR_COUNT];
int ledPin[SENSOR_COUNT] = {2,3,4,5,6};
int leftLedPin = 8;
int rightLedPin = 9;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
//  for(int i = 0; i < SENSOR_COUNT; i++) {
//    pinMode(ledPin[i],OUTPUT);
//  }
//  pinMode(leftLedPin, OUTPUT);
//  pinMode(rightLedPin, OUTPUT);
//  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

  // read sensors data
  for(int i = 0; i < SENSOR_COUNT; i++) {
    sensorVal[i] = analogRead(sensorPin[i]);
    Serial.print(sensorVal[i]); 
    Serial.print(","); 
  }
  Serial.println();
//  blinker();
  int score = getScore();
  displayLeds();
  showDirection(score);
//  steer(score);
  
//  Serial.println(analogRead(A1)); 
//  Serial.print(","); 
//  Serial.print(analogRead(A2));
//  Serial.print(","); 
//  Serial.print(analogRead(A3));
//  Serial.print(","); 
//  Serial.print(analogRead(A4));
//  Serial.print(","); 
//  Serial.print(analogRead(A5));
//  Serial.print("\n"); 
}

void displayLeds(){
  for(int i = 0; i < SENSOR_COUNT; i++) {
    if(sensorVal[i] > 400)
      digitalWrite(ledPin[i], HIGH);
    else
      digitalWrite(ledPin[i], LOW);
  }
}

int getScore(){
  return (-2) * sensorVal[0] + (-1) * sensorVal[1] + sensorVal[3] + 2 * sensorVal[4];
}

void blinker(){
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
}

void steer(int score){
  double normalizedScore = (double) score / 1500;
  analogWrite(leftMotorPin, SPEED_MAX);
  analogWrite(rightMotorPin, SPEED_MAX);
  if(score > DIRECTION_THRESHOLD){
    analogWrite(rightMotorPin, SPEED_MAX * (1 - normalizedScore));
  }else if(score < -DIRECTION_THRESHOLD){
    analogWrite(leftMotorPin, SPEED_MAX * (1 + normalizedScore));
  }
}

void showDirection(int score){
  digitalWrite(leftLedPin, LOW);
  digitalWrite(rightLedPin, LOW);
  if(score > DIRECTION_THRESHOLD){
    digitalWrite(rightLedPin, HIGH);
  } else if(score < -DIRECTION_THRESHOLD){
    digitalWrite(leftLedPin, HIGH);
  }
  
}


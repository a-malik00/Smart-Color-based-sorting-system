#include <Servo.h>
#include <math.h>

// -------------------- PIN DEFINITIONS --------------------
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define OUT_PIN 8   // TCS sensor output

#define SERVO_RED_PIN 9
#define SERVO_BLUE_PIN 10
#define MOTOR_PIN 3

// -------------------- SERVOS --------------------
Servo redServo;
Servo blueServo;

// -------------------- COLOR TARGETS (normalized) --------------------
// Replace with YOUR measured values after normalization
float targetRed[3]  = {0.29, 0.40, 0.31};   // R', G', B'
float targetBlue[3] = {0.45, 0.35, 0.20};   // R', G', B'

// -------------------- SORTING PARAMETERS --------------------
float COLOR_DISTANCE_THRESHOLD = 0.15; // smaller = stricter
int REST = 0;
int PUSH = 180;

// -------------------- FUNCTION: Read one color --------------------
unsigned int readColor(int s2State, int s3State) {
  digitalWrite(S2, s2State);
  digitalWrite(S3, s3State);
  delay(10); // sensor stabilization
  return pulseIn(OUT_PIN, LOW, 100000); // timeout 100ms
}

// -------------------- FUNCTION: Normalize RGB --------------------
void normalizeRGB(unsigned int R, unsigned int G, unsigned int B, float &nr, float &ng, float &nb) {
  unsigned int sum = R + G + B;
  if (sum == 0) sum = 1; // avoid division by zero
  nr = (float)R / sum;
  ng = (float)G / sum;
  nb = (float)B / sum;
}

// -------------------- FUNCTION: Euclidean distance --------------------
float colorDistance(float obj[3], float target[3]) {
  return sqrt(pow(obj[0]-target[0],2) + pow(obj[1]-target[1],2) + pow(obj[2]-target[2],2));
}

// -------------------- FUNCTION: Servo sorting --------------------
void activateServo(Servo &s) {
  s.write(PUSH);
  delay(500); // push object
  s.write(REST);
  delay(300); // retract
}

// -------------------- SETUP --------------------
void setup() {
  Serial.begin(115200);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT_PIN, INPUT);

  // Frequency scaling 100%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, HIGH);

  // Servos
  redServo.attach(SERVO_RED_PIN);
  blueServo.attach(SERVO_BLUE_PIN);
  redServo.write(REST);
  blueServo.write(REST);

  // Conveyor motor
  pinMode(MOTOR_PIN, OUTPUT);
  analogWrite(MOTOR_PIN, 200);

  Serial.println("TCS3200 Sorting System Ready...");
}

// -------------------- LOOP --------------------
void loop() {
  // 1. Read raw values
  unsigned int R = readColor(LOW, LOW);   // RED
  unsigned int G = readColor(HIGH, HIGH); // GREEN
  unsigned int B = readColor(LOW, HIGH);  // BLUE

  // 2. Normalize
  float nr, ng, nb;
  normalizeRGB(R, G, B, nr, ng, nb);

  float obj[3] = {nr, ng, nb};

  // 3. Compute distances
  float dRed = colorDistance(obj, targetRed);
  float dBlue = colorDistance(obj, targetBlue);

  // 4. Debug info
  Serial.print("R: "); Serial.print(R);
  Serial.print(" G: "); Serial.print(G);
  Serial.print(" B: "); Serial.print(B);
  Serial.print(" | nR: "); Serial.print(nr,3);
  Serial.print(" nG: "); Serial.print(ng,3);
  Serial.print(" nB: "); Serial.print(nb,3);
  Serial.print(" | Dist RED: "); Serial.print(dRed,3);
  Serial.print(" Dist BLUE: "); Serial.println(dBlue,3);

  // 5. Sorting decision
  if (dRed < COLOR_DISTANCE_THRESHOLD) {
    Serial.println("Detected: RED");
    activateServo(redServo);
  }
  else if (dBlue < COLOR_DISTANCE_THRESHOLD) {
    Serial.println("Detected: BLUE");
    activateServo(blueServo);
  }
  else {
    Serial.println("Unknown object...");
  }

  delay(100);
}
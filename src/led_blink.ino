// Motor A
const int IN1 = 26;
const int IN2 = 27;
// Motor B
const int IN3 = 14;
const int IN4 = 12;

void motor(int a, int b, int c, int d) {
  digitalWrite(IN1, a);
  digitalWrite(IN2, b);
  digitalWrite(IN3, c);
  digitalWrite(IN4, d);
}

void setup() {
  Serial.begin(115200);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  Serial.println("Adelante");
  motor(HIGH, LOW, HIGH, LOW);
  delay(2000);

  Serial.println("Parar");
  motor(LOW, LOW, LOW, LOW);
  delay(1000);

  Serial.println("Atras");
  motor(LOW, HIGH, LOW, HIGH);
  delay(2000);

  Serial.println("Parar");
  motor(LOW, LOW, LOW, LOW);
  delay(1000);
}
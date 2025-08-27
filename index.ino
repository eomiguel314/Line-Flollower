#define sIr1 A0
#define sIr2 A1
#define sIr3 A2
#define sIr4 A3
#define sIr5 A4
#define sIr6 A5
#define sIr7 A6

#define echo 10
#define trig 11

int limiar = 46;

long tempo;
float distancia;

class DCMotor {
  int spd = 255, pin1, pin2;

public:
  void Pinout(int in1, int in2) {
    pin1 = in1;
    pin2 = in2;
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
  }

  void Speed(int in1) {
    spd = in1;
  }

  void Forward() {
    analogWrite(pin1, spd);
    digitalWrite(pin2, LOW);
  }

  void Backward() {
    digitalWrite(pin1, LOW);
    analogWrite(pin2, spd);
  }

  void Stop() {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
  }
};

DCMotor Motor1, Motor2;

void setup() {
  Serial.begin(9600);

  Motor1.Pinout(2, 3);
  Motor2.Pinout(4, 5);

  pinMode(sIr1, INPUT);
  pinMode(sIr2, INPUT);
  pinMode(sIr3, INPUT);
  pinMode(sIr4, INPUT);
  pinMode(sIr5, INPUT);
  pinMode(sIr6, INPUT);
  pinMode(sIr7, INPUT);

  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
}

void loop() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  tempo = pulseIn(echo, HIGH);
  distancia = tempo * 0.034 / 2;
    Serial.println(distancia);
  if (distancia < 15) {
    Motor1.Forward();
    Motor2.Stop();

  } else {
    SeguirLinha();
  }

  delay(100);
}

void SeguirLinha() {
  int IR1 = analogRead(sIr1);
  int IR2 = analogRead(sIr2);
  int IR3 = analogRead(sIr3);
  int IR4 = analogRead(sIr4);
  int IR5 = analogRead(sIr5);
  int IR6 = analogRead(sIr6);
  int IR7 = analogRead(sIr7);

  int L1 = IR1 > limiar ? 1 : 0;
  int L2 = IR2 > limiar ? 1 : 0;
  int L3 = IR3 > limiar ? 1 : 0;
  int L4 = IR4 > limiar ? 1 : 0;
  int L5 = IR5 > limiar ? 1 : 0;
  int L6 = IR6 > limiar ? 1 : 0;
  int L7 = IR7 > limiar ? 1 : 0;

  Serial.print(L1); Serial.print(" ");
  Serial.print(L2); Serial.print(" ");
  Serial.print(L3); Serial.print(" ");
  Serial.print(L4); Serial.print(" ");
  Serial.print(L5); Serial.print(" ");
  Serial.print(L6); Serial.print(" ");
  Serial.println(L7);


  if (L3 == 1 && L4 == 1 && L5 == 1 && L1 == 0 && L2 == 0 && L6 == 0 && L7 == 0) {
    Motor1.Forward();
    Motor2.Forward();
    Serial.println("Seguindo em frente");
  }
  else if (L5 == 1 && L6 == 1 && L7 == 1) {
    Motor1.Backward();
    Motor2.Forward();
    Serial.println("Curva esquerda 1");
  }
  else if (L1 == 1 && L2 == 1 && L3 == 1) {
    Motor1.Forward();
    Motor2.Backward();
    Serial.println("Curva direita 1");
  }
  else if (L5 == 1 && L6 == 1 && L1 == 0 && L2 == 0) {
    Motor1.Stop();
    Motor2.Forward();
    Serial.println("Curva esquerda 0.5");
  }
  else if (L1 == 1 && L2 == 1 && L6 == 0 && L7 == 0) {
    Motor1.Forward();
    Motor2.Stop();
    Serial.println("cruva direita 0.5");
  }
  else if (L1 == 1 && L2 == 1 && L3 == 1 && L4 == 1 && L5 == 1 && L6 == 1 && L7 == 1) {
    Motor1.Stop();
    Motor2.Stop();
    Serial.println("cruzamernto detectado");
    delay(300);
  }
  else if (L2 == 1 && L3 == 1 && L4 == 1 && L5 == 1 && L6 == 1) {
    // Cruzamento em T
    Motor1.Stop();
    Motor2.Stop();
    Serial.println(" T");
    delay(300);
  }
  else if (L1 == 0 && L2 == 0 && L3 == 0 && L4 == 0 && L5 == 0 && L6 == 0 && L7 == 0) {
    // Gap ou fora da pista
    Motor1.Backward();
    Motor2.Backward();
    Serial.println("gap ou fora da linha");
    delay(200);
  }
  else {
    Motor1.Stop();
    Motor2.Stop();
    Serial.println("vermelho");
  }
}

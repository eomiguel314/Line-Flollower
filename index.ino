const int limiar = 500;  
const int sensores[] = {A0, A1, A2};
const int num_sensores = 3;
int leitura[num_sensores];

const int trigPin = 7;
const int echoPin = 8;
long tempo;
int distancia;

class DCMotor {
  int spd = 255, pin1, pin2;

public:
  void Pinout(int in1, int in2) {
    pin1 = in1;
    pin2 = in2;
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
  }

  void Speed(int vel) {
    spd = constrain(vel, 0, 255);
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

int medirDistancia() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  tempo = pulseIn(echoPin, HIGH);
  return tempo * 0.034 / 2;
}

void lerSensores(bool &esq, bool &centro, bool &dir) {
  for (int i = 0; i < num_sensores; i++) {
    leitura[i] = analogRead(sensores[i]);
  }
  esq = leitura[0] < limiar;
  centro = leitura[1] < limiar;
  dir = leitura[2] < limiar;
}

void seguirLinha(bool esq, bool centro, bool dir) {
  if (centro && !esq && !dir) {
    Motor1.Forward();
    Motor2.Forward();
  } else if (esq && !dir) {
    Motor1.Forward();
    Motor2.Stop();
  } else if (!esq && dir) {
    Motor1.Stop();
    Motor2.Forward();
  } else {
    Motor1.Stop();
    Motor2.Stop();
  }
}

void desviarObstaculo() {
  Motor1.Stop();
  Motor2.Stop();
  delay(100);
  Motor1.Backward();
  Motor2.Backward();
  delay(400);
  Motor1.Stop();
  Motor2.Forward();
  delay(500);
  Motor1.Stop();
  Motor2.Stop();
}

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < num_sensores; i++) {
    pinMode(sensores[i], INPUT);
  }
  Motor1.Pinout(5, 6);
  Motor2.Pinout(9, 10);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  bool esquerda, centro, direita;
  lerSensores(esquerda, centro, direita);
  distancia = medirDistancia();

  if (distancia < 10 && distancia > 0) {
    desviarObstaculo();
  } else {
    seguirLinha(esquerda, centro, direita);
  }

  Serial.print("E: "); Serial.print(leitura[0]);
  Serial.print(" | C: "); Serial.print(leitura[1]);
  Serial.print(" | D: "); Serial.print(leitura[2]);
  Serial.print(" | Dist: "); Serial.println(distancia);
}

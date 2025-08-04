int limiar = 500;// lucas , ajuste dps com um codigo de leitura caso nao funcione
const int sensores[] = {A0, A1, A2};
const int num_sensores = 3;
int read[num_sensores];

const int trigPin = 7;
const int echoPin = 8;
long time;
int distance;

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
  for (int i = 0; i < num_sensores; i++) {
    pinMode(sensores[i], INPUT);
  }

  Motor1.Pinout(5, 6); 
  Motor2.Pinout(9, 10);  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {a
  for (int i = 0; i < num_sensores; i++) {
    read[i] = analogRead(sensores[i]);
  }

  bool esquerda = read[0] < limiar;
  bool centro = read[1] < limiar;
  bool direita = read[2] < limiar;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  time = pulseIn(echoPin, HIGH);
  distance = time * 0.034 / 2;

  if (distance < 10) {
    Motor1.Stop();
    Motor2.Stop();
    delay(100);
    Motor1.Backward();
    Motor2.Backward();
    delay(400);
    Motor1.Stop();
    Motor2.Forward();  // virar
    delay(500);
    Motor2.Stop();
  } else {
    if (centro && !esquerda && !direita) {
      Motor1.Forward();
      Motor2.Forward();
    } else if (esquerda && !direita) {
      Motor1.Forward();
      Motor2.Stop();
    } else if (!esquerda && direita) {
      Motor1.Stop();
      Motor2.Forward();
    } else {
      Motor1.Stop();
      Motor2.Stop();
    }
  }

  Serial.print("E: "); Serial.print(read[0]);
  Serial.print(" | C: "); Serial.print(read[1]);
  Serial.print(" | D: "); Serial.print(read[2]);
  Serial.print(" | Dist: "); Serial.println(distance);

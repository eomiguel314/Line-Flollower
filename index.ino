#define sIr1 A0
#define sIr2 A1
#define sIr3 A2
#define sIr4 A3
#define sIr5 A4
#define sIr6 A5
#define sIr7 A6

int limiar = 46; // ------> Ajustar a limiar pra cada pista

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
  Motor1.Pinout(2, 3);
  Motor2.Pinout(4, 5);

  pinMode(sIr1, INPUT);
  pinMode(sIr2, INPUT);
  pinMode(sIr3, INPUT);
  pinMode(sIr4, INPUT);
  pinMode(sIr5, INPUT);
  pinMode(sIr6, INPUT);
  pinMode(sIr7, INPUT);

  Serial.begin(9600);  
}

void loop() {
  int IR1 = analogRead(sIr1);
  int IR2 = analogRead(sIr2);
  int IR3 = analogRead(sIr3);
  int IR4 = analogRead(sIr4);
  int IR5 = analogRead(sIr5);
  int IR6 = analogRead(sIr6);
  int IR7 = analogRead(sIr7);

  Serial.print(IR1); Serial.print(" ");
  Serial.print(IR2); Serial.print(" ");
  Serial.print(IR3); Serial.print(" ");
  Serial.print(IR4); Serial.print(" ");
  Serial.print(IR5); Serial.print(" ");
  Serial.print(IR6); Serial.print(" ");
  Serial.println(IR7);

  if (IR1 < limiar && IR2 < limiar && IR3 > limiar && IR4 > limiar && IR5 > limiar && IR6 < limiar && IR7 < limiar) {
    // Frente -> 0 0 1 1 1 0 0
    Motor1.Forward();
    Motor2.Forward();
    Serial.print("Frente");
  } 
  else if (IR1 < limiar && IR2 < limiar && IR3 < limiar && IR4 > limiar && IR5 > limiar && IR6 < limiar && IR7 < limiar) {
    // Frente -> 0 0 0 1 1 0 0 
    Motor1.Forward();
    Motor2.Forward();
    Serial.print("Frente");
  } 
  else if (IR1 < limiar && IR2 < limiar && IR3 > limiar && IR4 > limiar && IR5 < limiar && IR6 < limiar && IR7 < limiar) {
    // Frente -> 0 0 1 1 0 0 0
    Motor1.Forward();
    Motor2.Forward();
    Serial.print("Frente");
  } 
  else if (IR1 < limiar && IR2 < limiar && IR3 < limiar && IR4 > limiar && IR5 > limiar && IR6 > limiar && IR7 < limiar) {
    // Pouco esquerda -> 0 0 0 1 1 1 0
    Motor1.Stop();
    Motor2.Forward();
  } 
  else if (IR1 < limiar && IR2 < limiar && IR3 < limiar && IR4 < limiar && IR5 > limiar && IR6 > limiar && IR7 < limiar) {
    // Mais esquerda -> 0 0 0 0 1 1 0 
    Motor1.Backward();
    Motor2.Forward();
  }
  else if (IR1 < limiar && IR2 < limiar && IR3 < limiar && IR4 < limiar && IR5 > limiar && IR6 > limiar && IR7 > limiar) {
    // Forte esquerda -> 0 0 0 0 1 1 1 
    Motor1.Backward();
    Motor2.Forward();
  }  
  else if (IR1 < limiar && IR2 < limiar && IR3 < limiar && IR4 < limiar && IR5 < limiar && IR6 < limiar && IR7 > limiar) {
    // Linha no canto direito -> 0 0 0 0 0 0 1 
    Motor1.Backward();
    Motor2.Forward();
  }
  else if(IR1 < limiar && IR2 < limiar && IR3 < limiar && IR4 < limiar && IR5 < limiar && IR6 < limiar && IR7 < limiar){
    // Linha perdida
    Motor1.Backward();
    Motor2.Backward();
  }
  else if(IR1 > limiar && IR2 > limiar && IR3 > limiar && IR4 > limiar && IR5 > limiar && IR6 > limiar && IR7 > limiar){
    // Linha perdida
    Motor1.Backward();
    Motor2.Backward();
  }
   else {
  Motor2.Stop();
  Motor1.Stop();
  }

  delay(100);
}
 

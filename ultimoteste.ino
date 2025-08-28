


#include "Adafruit_TCS34725softi2c.h"

#define SDA1 20
#define SCL1 21

Adafruit_TCS34725softi2c tcs1 = Adafruit_TCS34725softi2c(
  TCS34725_INTEGRATIONTIME_50MS,
  TCS34725_GAIN_4X,
  SDA1, SCL1);

#define SDA2 A4
#define SCL2 A5
Adafruit_TCS34725softi2c tcs2 = Adafruit_TCS34725softi2c(
  TCS34725_INTEGRATIONTIME_50MS,
  TCS34725_GAIN_4X,
  SDA2, SCL2);


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

  Motor1.Pinout(2, 3);  // motor esquerdo
  Motor2.Pinout(4, 5);  // motor direito

  if (tcs1.begin()) Serial.println("Sensor 1 encontrado!");
  else Serial.println("Sensor 1 NAO encontrado!");
  
  if (tcs2.begin()) Serial.println("Sensor 2 encontrado!");
  else Serial.println("Sensor 2 NAO encontrado!");
}

void loop() {
  digitalWrite(trig, LOW); delayMicroseconds(2);
  digitalWrite(trig, HIGH); delayMicroseconds(10);
  digitalWrite(trig, LOW);
  tempo = pulseIn(echo, HIGH);
  distancia = tempo * 0.034 / 2;

  if(distancia < 15){
    Motor1.Stop();
    Motor2.Stop();
    Serial.println("Obstaculo detectado");
    return;
  }

  uint16_t r1,g1,b1,c1;
  uint16_t r2,g2,b2,c2;
  tcs1.getRawData(&r1,&g1,&b1,&c1);
  tcs2.getRawData(&r2,&g2,&b2,&c2);


  if(g1 > r1 && g1 > b1 && g1 > 200){
    Serial.println("Verde esquerda -> girar esquerda");
    Motor1.Stop();
    Motor2.Forward();
    return; // espera o loop atualizar a leitura
  }
  // Verde à direita
  else if(g2 > r2 && g2 > b2 && g2 > 200){
    Serial.println("Verde direita -> girar direita");
    Motor1.Forward();
    Motor2.Stop();
    return;
  }

  // Vermelho
  else if((r1>700 && g1<400 && b1<400) || (r2>700 && g2<400 && b2<400)){
    Serial.println("Vermelho -> parar");
    Motor1.Stop();
    Motor2.Stop();
    return;
  }
  SeguirLinha();
}

void SeguirLinha() {
//   int IR1 = analogRead(sIr1);
//   int IR2 = analogRead(sIr2);
//   int IR3 = analogRead(sIr3);
//   int IR4 = analogRead(sIr4);
//   int IR5 = analogRead(sIr5);
//   int IR6 = analogRead(sIr6);
//   int IR7 = analogRead(sIr7);

//   int L1 = IR1 > limiar ? 1 : 0;
//   int L2 = IR2 > limiar ? 1 : 0;
//   int L3 = IR3 > limiar ? 1 : 0;
//   int L4 = IR4 > limiar ? 1 : 0;
//   int L5 = IR5 > limiar ? 1 : 0;
//   int L6 = IR6 > limiar ? 1 : 0;
//   int L7 = IR7 > limiar ? 1 : 0;

//   Serial.print(L1); Serial.print(" ");
//   Serial.print(L2); Serial.print(" ");
//   Serial.print(L3); Serial.print(" ");
//   Serial.print(L4); Serial.print(" ");
//   Serial.print(L5); Serial.print(" ");
//   Serial.print(L6); Serial.print(" ");
//   Serial.println(L7);


//   if (L3 == 1 && L4 == 1 && L5 == 1 && L1 == 0 && L2 == 0 && L6 == 0 && L7 == 0) {
//     Motor1.Forward();
//     Motor2.Forward();
//     Serial.println("Seguindo em frente");
//   }
//   else if (L5 == 1 && L6 == 1 && L7 == 1) {
//     Motor1.Backward();
//     Motor2.Forward();
//     Serial.println("Curva esquerda 1");
//   }
//   else if (L1 == 1 && L2 == 1 && L3 == 1) {
//     Motor1.Forward();
//     Motor2.Backward();
//     Serial.println("Curva direita 1");
//   }
//   else if (L5 == 1 && L6 == 1 && L1 == 0 && L2 == 0) {
//     Motor1.Stop();
//     Motor2.Forward();
//     Serial.println("Curva esquerda 0.5");
//   }
//   else if (L1 == 1 && L2 == 1 && L6 == 0 && L7 == 0) {
//     Motor1.Forward();
//     Motor2.Stop();
//     Serial.println("cruva direita 0.5");
//   }
//   else if (L1 == 1 && L2 == 1 && L3 == 1 && L4 == 1 && L5 == 1 && L6 == 1 && L7 == 1) {
//     Motor1.Stop();
//     Motor2.Stop();
//     Serial.println("cruzamernto detectado");
//     delay(300);
//   }
//   else if (L2 == 1 && L3 == 1 && L4 == 1 && L5 == 1 && L6 == 1) {
//     // Cruzamento em T
//     Motor1.Stop();
//     Motor2.Stop();
//     Serial.println(" T");
//     delay(300);
//   }
//   else if (L1 == 0 && L2 == 0 && L3 == 0 && L4 == 0 && L5 == 0 && L6 == 0 && L7 == 0) {
//     // Gap ou fora da pista
//     Motor1.Backward();
//     Motor2.Backward();
//     Serial.println("gap ou fora da linha");
//     delay(200);
//   }
//   else {
//     Motor1.Stop();
//     Motor2.Stop();
//     Serial.println("vermelho");
//   }
// }

void

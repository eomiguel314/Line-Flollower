int limiar = 500;// ajustar por caussa da luminaçao

const int sensores[] = {A0, A1 , A2};
const int num_sensores = 3;
int read[num_sensores];

int i = 0;

//definir pinos do motor

class DCMotor {  
  int spd = 255, pin1, pin2;
  
  public:  
  
    void Pinout(int in1, int in2){ // Pinout é o método para a declaração dos pinos que vão controlar o objeto motor
      pin1 = in1;
      pin2 = in2;
      pinMode(pin1, OUTPUT);
      pinMode(pin2, OUTPUT);
      }   
    void Speed(int in1){ // Speed é o método que irá ser responsável por salvar a velocidade de atuação do motor
      spd = in1;
      }     
    void Forward(){ // Forward é o método para fazer o motor girar para frente
      analogWrite(pin1, spd);
      digitalWrite(pin2, LOW);
      }   
    void Backward(){ // Backward é o método para fazer o motor girar para trás
      digitalWrite(pin1, LOW);
      analogWrite(pin2, spd);
      }
    void Stop(){ // Stop é o metodo para fazer o motor ficar parado.
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, LOW);
      }
   };
   DCMotor Motor1, Motor2; 

void setup() {
  for(i < num_sensores, i++){
    pinMode(sensores[i], INPUT);

    Motor1.Pinout(5, 6);
    Motor1.Pinout(9, 10);
  }

  //pinout dos motor

  Serial.begin(9600);
}

void loop(){
  for(i < num_sensores, i++){
    read[i] = analogRead(sensores[i]);
  }
  
  bool esquerdo = read[0] < limiar;
  bool centro = read[1] < limiar;
  bool direito = read[2] < limiar;

  if(centro && !esquerdo && !direito ){
    Motor1.Forward();
    Motor2.Forward();
  } else if(esquerda && !direta) {
    Motor1.Forward();
    Motor2.Stop();
  }
  } else if(!esquerda && direta) {
    Motor1.Stop();
    Motor2.Forward();
  }
  else{
    Motor1.Stop();
    Motor2.Stop();
  }
  Serial.print("E: "); Serial.print(leituras[0]);
  Serial.print(" | C: "); Serial.print(leituras[1]);
  Serial.print(" | D: "); Serial.println(leituras[2]);

}

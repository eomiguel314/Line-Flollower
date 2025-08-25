#define sIr1 A0
#define sIr2 A1
#define sIr3 A2
#define sIr4 A3
#define sIr5 A4
#define sIr6 A5
#define sIr7 A6

int limiar = 30;

void setup(){
  pinMode(sIr1, INPUT);
  pinMode(sIr2, INPUT);
  pinMode(sIr3, INPUT);
  pinMode(sIr4, INPUT);
  pinMode(sIr5, INPUT);
  pinMode(sIr6, INPUT);
  pinMode(sIr7, INPUT);
}
// Branco : 20, Preto : 30
const read;
read = analogRead();
void loop(){
  if(IR1 == 20 &&  IR2 == 20 && IR3 == limiar && IR4 == limiar && IR5 == limiar && IR6 == 20 && IR7 == 20  ){
    //Motor Frente
    // 0 0 1 1 1 0 0 
  } else if(IR1 == 20 &&  IR2 == 20 && IR3 == 20 && IR4 == limiar && IR5 == limiar && IR6 == 20 && IR7 == 20 ){ 
  // Motor Frente
  //  0 0 0 1 1 0 0
}else if(IR1 == 20 &&  IR2 == 20 && IR3 == limiar && IR4 == limiar && IR5 == 20 && IR6 == 20 && IR7 == 20){
  //Motor Frente 
  // 0 0 1 1 0 0 0 
}


else if(IR1 == 20 &&  IR2 == 20 && IR3 == 20 && IR4 == limiar && IR5 == limiar && IR6 == limiar && IR7 == 20){
//0 0 0 1 1 1 0
}else if(IR1 == 20 &&  IR2 == 20 && IR3 == 20 && IR4 == 20 && IR5 == limiar && IR6 == limiar && IR7 == 20){
 // 0 0 0 0 1 1 0 
}else if(IR1 == 20 &&  IR2 == 20 && IR3 == 20 && IR4 == 20 && IR5 == limiar && IR6 == limiar && IR7 == limiar){}
 // 0 0 0 0 1 1 1

else if(IR1 == 20 &&  IR2 == 20 && IR3 == 20 && IR4 == 20 && IR5 == 20 && IR6 == 20 && IR7 == limiar){}
 // 0 0 0 0 0 0 1 girar ate pegar o meio da linha
// Inverter a logica  

else if(IR1 == 20 &&  IR2 == limiar && IR3 == limiar && IR4 == limiar && IR5 == 20 && IR6 == 20 && IR7 == 20)
 // pouco a direita 0 1 1 1 0 0 0 0 ou 
else if(IR1 == 20 &&  IR2 == limiar && IR3 == limiar && IR4 == 20 && IR5 == 20 && IR6 == 20 && IR7 == 20){}// 0 1 1  0 0 0 0 pouco a direita 

else if(IR1 == limiar &&  IR2 == limiar && IR3 == 20  && IR4 == 20 && IR5 == 20 && IR6 == 20 && IR7 == 20){} // 1 1 0 0 0 0 

else if(IR1 == limiar &&  IR2 == 20 && IR3 == 20  && IR4 == 20 && IR5 == 20 && IR6 == 20 && IR7 == 20) // 1 0 0 0 0 0 



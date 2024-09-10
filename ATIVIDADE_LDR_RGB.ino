#define R 3
#define B 5
#define G 6


int LDR = 0;
void setup()
{
  pinMode(A0, INPUT);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int LDR = analogRead(A0);
   Serial.println(LDR);
  
  // LIGA Verde
  if (LDR<100){
     analogWrite(R, 0);
     analogWrite(G, 200);
     analogWrite(B, 0);
     }
  else{
     //LIGA AZUL
    if (LDR>100 && LDR<=200){
     analogWrite(R, 0);
     analogWrite(G, 0);
     analogWrite(B, 300);
  }
  else
    // LIGA VERMELHO
    if (LDR>200 && LDR<=400){
     analogWrite(R, 200);
     analogWrite(G, 0);
     analogWrite(B, 0);
     }
  else{
     Serial.println("LED desligado");
     analogWrite(R, 0);
      analogWrite(G, 0);
      analogWrite(B, 0);
    Serial.println(LDR);
     }
     Serial.println(LDR);
     delay(1000);
}}
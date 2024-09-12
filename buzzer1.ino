#define R 3
#define B 5
#define G 6
int buzzer = 8;

void setup() {
  Serial.begin(9600);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  vermelho();
  amarelo();
  verdeLimao();
  verde();
  azulCiano();
  azul();
  rosa();
  rosaClaro();
  branco();
}

void vermelho(){
  tone(buzzer, 100, 5000);
  analogWrite(3, 255);
  analogWrite(G, 0);
  analogWrite(B, 0);
  Serial.println("Cor VERMELHO: ");
  delay(500);
  noTone(buzzer);
}

void amarelo(){
  tone(buzzer, 900, 5000);
  analogWrite(R, 255); 
  analogWrite(G, 200);
  analogWrite(B, 0);
  Serial.println("Cor AMARELO");
  delay(500);
  noTone(buzzer);
}

void verdeLimao(){
  tone(buzzer, 200, 5000);
  analogWrite(R, 100);
  analogWrite(G, 255);
  analogWrite(B, 0);
  Serial.println("Cor VERDE LIMÃO");
  delay(500);
  noTone(buzzer);
}

void verde(){ 
  tone(buzzer, 800, 5000);
  analogWrite(R, 0);
  analogWrite(B, 0);
  analogWrite(G, 200);
  Serial.println("Cor VERDE");
  delay(500);
  noTone(buzzer);
}

void azulCiano(){  
  tone(buzzer, 300, 5000);
  analogWrite(R, 0);
  analogWrite(G, 200);
  analogWrite(B, 200);
  Serial.println("Cor AZUL CIANO");
  delay(500);
  noTone(buzzer);
}

void azul(){ 
  tone(buzzer, 700, 5000);
  analogWrite(R, 0);
  analogWrite(G, 0);
  analogWrite(B, 255);
  Serial.println("Cor AZUL");
  delay(500);
  noTone(buzzer);
}

void rosa(){  
  tone(buzzer, 400, 5000);
  analogWrite(R, 255);
  analogWrite(G, 0);
  analogWrite(B, 200);
  Serial.println("Cor ROSA");
  delay(500);
  noTone(buzzer);
}

void rosaClaro(){ 
  tone(buzzer, 600, 5000);
  analogWrite(R, 255);
  analogWrite(G, 100);
  analogWrite(B, 255);
  Serial.println("Cor ROSA CLARO");
  delay(500);
  noTone(buzzer);
}

void branco(){
  tone(buzzer, 500, 5000);
  analogWrite(R, 255);
  analogWrite(G, 255);
  analogWrite(B, 255);
  Serial.println("Cor BRANCO");
  delay(500);
  noTone(buzzer);
 
}



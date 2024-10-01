//https://www.tinkercad.com/things/kdBlush437L

//Exercício - Arduino - Introdução - Semáforo - Parte 3

//Esse projeto é para ser feito usando o Tinkercad.

//Refaça o projeto do semáforo para que o LED verde dos carros fique piscando no último segundo, 
//isto é, antes de desligar o verde e ligar o amarelo. 
//Ou seja, o LED verde fica ligado durante 2 segundos e no próximo segundo começa a piscar com intervalos de 100ms. 


// C++ code/ define os pinos usados para os sinais dos semáforos// define os pinos usados para os sinais dos semáforos
const int verdeCarroPin = 2;
const int amareloCarroPin = 3;
const int vermelhoCarroPin = 4;
const int verdePedestrePin = 5;
const int vermelhoPedestrePin = 6;

void setup() {
  // inicializa os pinos como saídas
  pinMode(verdeCarroPin, OUTPUT);
  pinMode(amareloCarroPin, OUTPUT);
  pinMode(vermelhoCarroPin, OUTPUT);
  pinMode(verdePedestrePin, OUTPUT);
  pinMode(vermelhoPedestrePin, OUTPUT);
  
  // define o estado inicial dos semáforos
  digitalWrite(verdeCarroPin, HIGH);
  digitalWrite(amareloCarroPin, LOW);
  digitalWrite(vermelhoCarroPin, LOW);
  digitalWrite(verdePedestrePin, LOW);
  digitalWrite(vermelhoPedestrePin, HIGH);
}

void loop() {
  // define o semáforo de carros para amarelo por 1 segundo, depois vermelho por 2 segundos
  digitalWrite(verdeCarroPin, HIGH);
  digitalWrite(amareloCarroPin, LOW);
  digitalWrite(vermelhoCarroPin, LOW);
  digitalWrite(verdePedestrePin, LOW);
  digitalWrite(vermelhoPedestrePin, HIGH);
  delay(3000); // espera 3 segundos
  
  digitalWrite(verdeCarroPin, LOW);
  digitalWrite(amareloCarroPin, HIGH);
  digitalWrite(vermelhoCarroPin, LOW);
  digitalWrite(verdePedestrePin, LOW);
  digitalWrite(vermelhoPedestrePin, HIGH);
  delay(1000); // espera 1 segundo
  
  // pisca o LED verde por 1 segundo
  digitalWrite(verdeCarroPin, LOW);
  for (int i = 0; i < 5; i++) {
    digitalWrite(verdeCarroPin, HIGH);
    delay(100);
    digitalWrite(verdeCarroPin, LOW);
    delay(100);
  }
  
  // define o semáforo de carros para vermelho e o semáforo de pedestres para verde por 2 segundos
  digitalWrite(verdeCarroPin, LOW);
  digitalWrite(amareloCarroPin, LOW);
  digitalWrite(vermelhoCarroPin, HIGH);
  digitalWrite(verdePedestrePin, HIGH);
  digitalWrite(vermelhoPedestrePin, LOW);
  delay(2000); // espera 2 segundos
  
  // define o semáforo de pedestres para vermelho e o semáforo de carros para verde
  digitalWrite(verdeCarroPin, HIGH);
  digitalWrite(amareloCarroPin, LOW);
  digitalWrite(vermelhoCarroPin, LOW);
  digitalWrite(verdePedestrePin, LOW);
  digitalWrite(vermelhoPedestrePin, HIGH);
  delay(0); // espera 0 segundos (o loop reiniciará imediatamente)
}

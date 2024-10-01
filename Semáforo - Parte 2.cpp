//https://www.tinkercad.com/things/anKmnCLLzpe

//Exercício - Arduino - Introdução - Semáforo - Parte 2

//Esse projeto é para ser feito usando o Tinkercad.

//Refaça o projeto do semáforo para incluir um semáforo para os pedestres. 
//Ou seja, caso o semáforo dos carros esteja verde, o semáforo dos pedestres têm que estar vermelho; 
//caso o semáforo dos carros esteja vermelho, o semáforo dos pedestres têm que estar verde. 

int verde_carros = 10;    // define o pino do LED verde do semáforo de int amarelo_carros = 9;   // define o pino do LED amarelo do semáforo de carrosint amarelo_carros = 9;   // define o pino do LED amarelo do semáforo de carros// define the pins used for the traffic light signals// define os pinos usados para os sinais dos semáforos// define os pinos usados para os sinais dos semáforos// define os pinos usados para os sinais dos semáforos
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
  
  digitalWrite(verdeCarroPin, LOW);
  digitalWrite(amareloCarroPin, LOW);
  digitalWrite(vermelhoCarroPin, HIGH);
  digitalWrite(verdePedestrePin, HIGH);
  digitalWrite(vermelhoPedestrePin, LOW);
  delay(2000); // espera 2 segundos
  
  // define o semáforo de pedestres para verde por 2 segundos, depois vermelho
  digitalWrite(verdeCarroPin, LOW);
  digitalWrite(amareloCarroPin, LOW);
  digitalWrite(vermelhoCarroPin, HIGH);
  digitalWrite(verdePedestrePin, HIGH);
  digitalWrite(vermelhoPedestrePin, LOW);
  delay(2000); // espera 2 segundos
  
  digitalWrite(verdeCarroPin, HIGH);
  digitalWrite(amareloCarroPin, LOW);
  digitalWrite(vermelhoCarroPin, LOW);
  digitalWrite(verdePedestrePin, LOW);
  digitalWrite(vermelhoPedestrePin, HIGH);
  delay(0); // espera 0 segundos (o loop reiniciará imediatamente)
}

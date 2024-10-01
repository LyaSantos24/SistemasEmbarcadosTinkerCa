//https://www.tinkercad.com/things/2MzCo4yH9Eh


//Exercício de Programação Baseada em Máquinas de Estados Finitos
//Exercício em duplas, para a graduação, e individual, para a pós-graduação.
//Esse projeto é para ser feito usando o Tinkercad.
//Use máquinas de estados finitos para resolver o problema especificado abaixo.
//Faça o circuito e simule o acendimento das três lâmpadas de um semáforo (verde, amarelo e vermelho). 
//Vamos assumir que as lâmpadas são LEDs e que os tempos de cada semáforo são 3s (verde), 1s (amarelo) e 2s (vermelho). 
//A ordem de ligar e desligar será infinita de acordo com a sequência: verde, 
//amarelo, vermelho, verde, amarelo, vermelho, verde .... e assim por diante.
//Adicionalmente, incluir um semáforo para os pedestres. Ou seja, caso o semáforo dos carros esteja verde, 
//o semáforo dos pedestres têm que estar vermelho; caso o semáforo dos carros esteja vermelho, 
//o semáforo dos pedestres têm que estar verde.
//Por fim, faça com que o LED verde dos carros fique piscando no último segundo, isto é, 
//antes de desligar o verde e ligar o amarelo. Ou seja, o LED verde fica ligado durante 2 segundos 
//e no próximo segundo começa a piscar com intervalos de 100ms.

// C++ code/ define os pinos usados para os sinais dos semáforos
const int verdeCarroPin = 2;
const int amareloCarroPin = 3;
const int vermelhoCarroPin = 4;
const int verdePedestrePin = 5;
const int vermelhoPedestrePin = 6;

// define os estados da máquina de estados
enum Estados {CARROS_VERDE, CARROS_AMARELO, CARROS_PISCANDO_VERDE, PEDESTRES_VERMELHO, PEDESTRES_VERDE};

// define o estado inicial da máquina de estados
Estados estadoAtual = CARROS_VERDE;

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
switch(estadoAtual) {
case CARROS_VERDE:
digitalWrite(verdeCarroPin, HIGH);
digitalWrite(amareloCarroPin, LOW);
digitalWrite(vermelhoCarroPin, LOW);
digitalWrite(verdePedestrePin, LOW);
digitalWrite(vermelhoPedestrePin, HIGH);
delay(3000); // espera 3 segundos
estadoAtual = CARROS_AMARELO;
break;
  
case CARROS_AMARELO:
  digitalWrite(verdeCarroPin, LOW);
  digitalWrite(amareloCarroPin, HIGH);
  digitalWrite(vermelhoCarroPin, LOW);
  digitalWrite(verdePedestrePin, LOW);
  digitalWrite(vermelhoPedestrePin, HIGH);
  delay(1000); // espera 1 segundo
  estadoAtual = CARROS_PISCANDO_VERDE;
  break;
  
case CARROS_PISCANDO_VERDE:
  digitalWrite(vermelhoPedestrePin, HIGH); // desliga o sinal de pedestres
  for (int i = 0; i < 5; i++) {
    digitalWrite(verdeCarroPin, HIGH);
    delay(100);
    digitalWrite(verdeCarroPin, LOW);
    delay(100);
  }
  estadoAtual = PEDESTRES_VERMELHO;
  break;
  
case PEDESTRES_VERMELHO:
  digitalWrite(verdeCarroPin, LOW);
  digitalWrite(amareloCarroPin, LOW);
  digitalWrite(vermelhoCarroPin, HIGH);
  digitalWrite(verdePedestrePin, HIGH);
  digitalWrite(vermelhoPedestrePin, LOW);
  delay(2000); // espera 2 segundos
  estadoAtual = PEDESTRES_VERDE;
  break;
  
case PEDESTRES_VERDE:
  digitalWrite(verdeCarroPin, LOW);
  digitalWrite(amareloCarroPin, LOW);
  digitalWrite(vermelhoCarroPin, HIGH);
  digitalWrite(verdePedestrePin, LOW);
  digitalWrite(vermelhoPedestrePin, HIGH);
  delay(3000); // espera 3 segundos
  estadoAtual = CARROS_VERDE;
  break;
}
}

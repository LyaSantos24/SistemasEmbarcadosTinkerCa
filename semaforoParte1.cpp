//https://www.tinkercad.com/things/k7EyHRMmOY9

//Exercício - Arduino - Introdução - Semáforo - Parte 1

//Esse projeto é para ser feito usando o Tinkercad.

//Faça o circuito e simule o acendimento das três lâmpadas de um semáforo (verde, amarelo e vermelho). 
//Vamos assumir que as lâmpadas são LEDs e que os tempos de cada semáforo são 3s (verde), 1s (amarelo) e 2s (vermelho). 
//A ordem de ligar e desligar será infinita de acordo com a sequência: 
//verde, amarelo, vermelho, verde, amarelo, vermelho, verde .... 

int redLED = 8;    // define o pino do LED vermelho como pino 8
int yellowLED = 9; // define o pino do LED amarelo como pino 9
int greenLED = 10;  // define o pino do LED verde como pino 10

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
}

void loop() {
  digitalWrite(greenLED, HIGH); // acende o LED verde
  delay(3000);                  // aguarda 3 segundos
  digitalWrite(greenLED, LOW);  // desliga o LED verde
  digitalWrite(yellowLED, HIGH);// acende o LED amarelo
  delay(1000);                  // aguarda 1 segundo
  digitalWrite(yellowLED, LOW); // desliga o LED amarelo
  digitalWrite(redLED, HIGH);   // acende o LED vermelho
  delay(2000);                  // aguarda 2 segundos
  digitalWrite(redLED, LOW);    // desliga o LED vermelho
}

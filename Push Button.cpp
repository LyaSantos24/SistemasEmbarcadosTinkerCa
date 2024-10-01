//https://www.tinkercad.com/things/fexUdn5hhhU

//Acionar um LED apertando 2 Push Buttons (botões de pressão) como chaves liga-desliga
//Assuma que o botão de pressão funciona como uma chave liga-desliga. Criar um circuito para que um LED seja 
//acionado somente se dois botões de pressão (push button) estiverem ligados (ON).
//Neste projeto, teremos uma rotina para atribuir uma ação, no caso acender um LED, 
//somente quando dois botões forem pressionados independentemente da ordem. Caso um dos botões (ou os dois) seja desligado , 
//o LED deverá se apagar.

const int ledPin = 12; 
const int bot1Pin = 8; 
const int bot2Pin = 7; 

int estadoBotao1; 
int estadoBotao2; 

void setup() {
  pinMode(ledPin, OUTPUT); 
  pinMode(bot1Pin, INPUT_PULLUP); 
  pinMode(bot2Pin, INPUT_PULLUP);
}

void loop() {
  estadoBotao1 = digitalRead(bot1Pin); 
  estadoBotao2 = digitalRead(bot2Pin);

  if (!estadoBotao1 && !estadoBotao2 ) { 
    digitalWrite(ledPin, HIGH); 
  }
  else { 
    digitalWrite(ledPin, LOW); 
  }
}

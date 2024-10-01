//https://www.tinkercad.com/things/4YcBOFlRib1

//Faça o circuito e simule um semáforo de carros com três LEDs (verde, amarelo e vermelho) e um semáforo de pedestres com dois LEDs (verde e vermelho).

//Assuma que o LED verde dos carros, e o LED vermelho dos pedestres também, fica ligado o tempo todo, exceto se 
//algum pedestre pedir para atravessar a rua. 
//Assuma que esse pedido é feito através de um botão de pressão (push button). Ou seja, quando o botão for pressionado, 
//o LED verde dos carros é desligado e o LED amarelo dos carros é ligado por 1 segundo. Após esse tempo de 1s, 
//o LED amarelo dos carros é desligado, o LED vermelho dos carros é ligado, o LED vermelho dos pedestres é desligado 
//e o LED verde dos pedestres é ligado durante 2 segundos. Após esse tempo de 2s, o LED verde dos pedestres é desligado, 
//LED vermelho dos pedestres é ligado, LED vermelho dos carros é desligado e LED verde dos carros é ligado. Nesse caso, 
//volta tudo como era no início.

//Neste projeto, o botão deve acionar uma interrupção, cuja rotina de interrupção deve, simplesmente, alterar uma variável 
//global, que deve indicar que um pedestre solicitou atravessar a rua. Obviamente que o tratamento da 
//travessia dos pedestres tem que ser feito fora da rotina de interrupção. A sugestão é que seja feito uma 
//função só para esse tratamento.

//Considere que após o botão ter sido pressionado, e durante os 2s de travessia do pedestre, caso o botão 
//seja pressionado novamente, nada deverá ser feito. Isto é, o botão de pressão só voltará a executar a 
//ação de travessia dos pedestres com segurança após ter passado os dois segundos, que é o tempo em que o 
//LED verde dos pedestres ficará ligado (e que o LED vermelho dos carros também ficará ligado).

//Sugestão: estude a função detachInterrupt() em https://www.arduino.cc/reference/en/language/functions/external-interrupts/detachinterrupt/ e veja se você consegue resolver este problema.

//Outra boa opção é ter uma flag global associada ao sinal verde do pedestre. No caso, se já estiver verde, 
//o procedimento da interrupção não iria fazer nada

// Definição dos pinos dos LEDs dos semáforos de carros e pedestres
int verde_carros = 8;
int amarelo_carros = 3;
int vermelho_carros = 4;
int verde_pedestres = 5;
int vermelho_pedestres = 6;

// Definição do pino do botão de pedestres
int botao_pedestres = 2;

// Variável global indicando se um pedestre solicitou atravessar a rua
volatile bool pedestre_solicitou = false;

// Flag global indicando se o LED verde dos pedestres está aceso
volatile bool verde_pedestres_aceso = false;

void setup() {
  // Configuração dos pinos dos LEDs e do botão
  pinMode(verde_carros, OUTPUT);
  pinMode(amarelo_carros, OUTPUT);
  pinMode(vermelho_carros, OUTPUT);
  pinMode(verde_pedestres, OUTPUT);
  pinMode(vermelho_pedestres, OUTPUT);
  pinMode(botao_pedestres, INPUT_PULLUP);

  // Configuração da interrupção para o botão de pedestres
  attachInterrupt(digitalPinToInterrupt(botao_pedestres), pedestreSolicitado, FALLING);

  // Ligar LEDs dos carros e desligar LEDs dos pedestres
  digitalWrite(verde_carros, HIGH);
  digitalWrite(amarelo_carros, LOW);
  digitalWrite(vermelho_carros, LOW);
  digitalWrite(vermelho_pedestres, HIGH);
  digitalWrite(verde_pedestres, LOW);
}

void loop() {
  // Verifica se algum pedestre solicitou atravessar a rua
  if (pedestre_solicitou) {
    // Verifica se o LED verde dos pedestres já está aceso
    if (!verde_pedestres_aceso) {
      // Desliga LED verde dos carros e liga LED amarelo dos carros
      digitalWrite(verde_carros, LOW);
      digitalWrite(amarelo_carros, HIGH);
      delay(1000);

      // Desliga LED amarelo dos carros e liga LED vermelho dos carros
      digitalWrite(amarelo_carros, LOW);
      digitalWrite(vermelho_carros, HIGH);

      // Desliga LED vermelho dos pedestres e liga LED verde dos pedestres
      digitalWrite(vermelho_pedestres, LOW);
      digitalWrite(verde_pedestres, HIGH);

      // Atualiza flag indicando que o LED verde dos pedestres está aceso
      verde_pedestres_aceso = true;
    }

    // Aguarda o tempo de travessia dos pedestres
    delay(2000);

    // Desliga LED verde dos pedestres e liga LED vermelho dos pedestres
    digitalWrite(verde_pedestres, LOW);
    digitalWrite(vermelho_pedestres, HIGH);

    // Ligar LEDs dos carros e desligar LEDs dos pedestres
    digitalWrite(vermelho_carros, LOW);
    digitalWrite(verde_carros, HIGH);

    // Resetar variável global e flag
    pedestre_solicitou = false;
    verde_pedestres_aceso = false;
  }
}

void pedestreSolicitado() {
  if (!verde_pedestres_aceso) {
    pedestre_solicitou = true;
  }
}



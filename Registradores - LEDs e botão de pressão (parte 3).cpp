//https://www.tinkercad.com/things/6QUywQlmPah

//Este é um projeto que manipula diretamente as portas do Arduino através dos registradores DDRD e PORTD. 
//De acordo com o slide 6, da apresentação sobre REGISTRADORES, pode-se perceber que os pinos digitais D0 a D7, 
//correspondem exatamente aos mesmos bits do PORTD. Isso vai facilitar a implementação descrita a seguir.

//Faça um circuito no Tinkercad (e compartilhe de forma pública) 
//que crie um "dado eletrônico" que irá sortear números de 1 a 6. 
//Cada jogada do dado é realizada ao pressionar um botão de pressão (pode ser liga-desliga ou não, você escolhe). 
//Para o sorteio do número use a função random. 
//A forma de representação do resultado do dado será através de sete LEDs dispostos da seguinte forma:

//A vantagem de você utilizar o PORTD é que você pode mover os valores 0 e 1 
//para o registrador PORTD como um todo e, dessa forma, alternar o estado dos sete LEDs de uma 
//só vez (com um único comando). Não é obrigatório, mas verifique a possibilidade de gerar um vetor de seis bytes, 
//onde cada byte seja a representação de um dígito (de 1 até 6) através dos sete LEDs (alguns acessos e outros apagados). 
//Só use registradores, isto é, não utilize pinMode, nem digitalWrite. 
//É obrigatório que o botão de pressão seja implementado com o resistor interno de pull-up. 

byte estadoBtn = 0; 
const byte btPin = 12;

const byte face[6] = {     
  B10000000,  // Digito 1   
  B01000010,  // Digito 2   
  B11000010,  // Digito 3   
  B01011010,  // Digito 4   
  B11011010,  // Digito 5   
  B01111110   // Digito 6  
};

void setup() {
  DDRD |= B11111110; //Configura os pinos digitais de 1 até 7 como saída digital   
  PORTD = 0; // apaga todos os leds 
  pinMode(btPin, INPUT_PULLUP); // difine entrada do push button como pull up interno 
  randomSeed(analogRead(0)); // inicializa o ramdom sem repetição de séries
}

void loop() { 
  estadoBtn = digitalRead(btPin);
  if(!estadoBtn){    
    rodadada(); // gera a rodada do dado 
    delay(150);
  }
}

void rodadada(){
  byte result = 0; // inicializa a variável "result" com 0
  byte rodada = random(15, 35); // gera comprimento da rodada, quantos números passarão
  for (byte i = 0; i < rodada; i++) // loop de 0 até comprimento da rodada
  {
    result = random(0, 6); // gera número de 0 a 6, devido à matriz face começar em 0                             
    show(result); // mostra resultado
    delay(50 + i * 10); // espera para passar cada número (varia velocidade)
  }
}

// mostra o resultado da face do dado no display
void show(int result) {
  PORTD = face[result];   
}

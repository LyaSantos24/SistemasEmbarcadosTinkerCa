//https://www.tinkercad.com/things/bRjH036LBLA  

//Faça um circuito no Tinkercad que alterne ligar e desligar um LED. 
//A especificação diz que o LED deve ficar ligado durante 4s e desligado durante 3s.
//É necessário usar a interrupção do Timer 1.

// Define o pino do LED
const int LED_PIN = 13;

// Define as variáveis de tempo
unsigned long previousMillis = 0;
const unsigned long onInterval = 4000;
const unsigned long offInterval = 3000;

void setup() {
  // Configura o pino do LED como saída
  pinMode(LED_PIN, OUTPUT);

  // Configura o Timer 1
  cli();             // Desabilita interrupção global
  TCCR1A = 0;        // Seta TCCR1A igual a 0
  TCCR1B = 0;        // Seta TCCR1B igual a 0 
  TCNT1  = 0x00;     // Inicia o Timer1 em 0
  TCCR1B |= (1 << CS12); // Prescaler de 256
  TIMSK1 |= 0x01;    // Habilita interrupção de estouro do Timer1
  sei();             // Habilita interrupção global
}

void loop() {
  // Nada a fazer aqui hihihiihi
}

// Função de interrupção do Timer1
ISR(TIMER1_OVF_vect) {
  // Obtém o tempo atual
  unsigned long currentMillis = millis();

  // Verifica se o LED deve ser ligado ou desligado
  if (currentMillis - previousMillis < onInterval) {
    digitalWrite(LED_PIN, HIGH);  // Liga o LED
  } else if (currentMillis - previousMillis < onInterval + offInterval) {
    digitalWrite(LED_PIN, LOW);   // Desliga o LED
  } else {
    previousMillis = currentMillis;  // Salva o tempo atual
  }
}

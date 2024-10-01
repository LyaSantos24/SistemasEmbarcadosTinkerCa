////https://www.tinkercad.com/things/cdseJtpJ8sc

///De acordo com o slide da apresentação sobre REGISTRADORES, 
//pode-se perceber que os pinos 
//A0 está associado com o pino D14, o A1 com o D15, o A2 com o D16, o A3 com o D17, o A4 com o D18 e o A5 com o D19.

//Faça um circuito no Tinkercad 
//(e compartilhe de forma pública) que simplesmente faça um LED piscar com intervalo de 700ms ligado e 700ms desligado. 
//O LED deve estar ligado em um desses 6 pinos acima (D14 a D19). Só use registradores e interrupção do TIMER. Isto é, 
//não use delay, millis, nem digitalWrite. Se você não seguir a especificação acima (uso de registradores e interrupção do timer) 
//a nota será zero.

//Inclua nos comentários os resultados dos cálculos dos valores a serem movidos para os registradores para garantir 
//que o valor do estouro do timer está de acordo com o valor de 700 ms.

void setup() {
  DDRB |= (1 << DDB5); // Define o pino D19 como saída
  TCCR1A = 0; // Zera as configurações do timer 1
  TCCR1B = 0; // Zera as configurações do timer 1
  TCCR1B |= (1 << WGM12); // Modo de comparação CTC
  TCCR1B |= (1 << CS12) | (1 << CS10); // Prescaler de 1024
  OCR1A = 10937; // Define o número de ciclos do timer para interrupção
  TIMSK1 |= (1 << OCIE1A); // Habilita interrupção por comparação
}

void loop() {
}

ISR(TIMER1_COMPA_vect) {
  static bool led_on = false; // Variável para armazenar o estado do LED
  if (led_on) {
    PORTB &= ~(1 << PORTB5); // Desliga o LED
    led_on = false; // Atualiza o estado do LED
  } else {
    PORTB |= (1 << PORTB5); // Liga o LED
    led_on = true; // Atualiza o estado do LED
  }
}



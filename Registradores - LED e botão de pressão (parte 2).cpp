//https://www.tinkercad.com/things/fJpBTQLdcxN

//De acordo com o slide da apresentação sobre REGISTRADORES, pode-se perceber que os pinos A0 
está associado com o pino D14, o A1 com o D15, o A2 com o D16, o A3 com o D17, o A4 com o D18 e o A5 com o D19.


//Faça um circuito no Tinkercad (e compartilhe de forma pública) que simplesmente alterne o estado de um LED 
//(ligado para desligado ou desligado para ligado) conforme um botão de pressão (push button) seja pressionado, 
//como se fosse uma chave liga-desliga. Tanto o LED quanto o botão de pressão devem estar ligados em dois desses 
//6 pinos acima (D14 a D19). Só use registradores (nada de usar pinmode, digitalWrite, nem digitalRead). 
//É obrigatório que o botão de pressão seja implementado com o resistor interno de pull-up. 
const byte LED_PIN = 0; // Pino D14 (bit 0 da Porta D)
const byte BUTTON_PIN = 1; // Pino D15 (bit 1 da Porta D)

void setup() {
  DDRD |= (1 << LED_PIN); // Define o pino do LED como saída
  DDRD &= ~(1 << BUTTON_PIN); // Define o pino do botão como entrada
  PORTD |= (1 << BUTTON_PIN); // Habilita o resistor interno de pull-up do botão
}

void loop() {
  if (!(PIND & (1 << BUTTON_PIN))) { // Se o botão for pressionado
    PORTD ^= (1 << LED_PIN); // Alterna o estado do LED
    while (!(PIND & (1 << BUTTON_PIN))) { } // Aguarda o botão ser solto
  }
}

//Exercício - Arduino - TinkerCad
//1) Faça um LED piscar a cada 600 ms. Use o pino 12 de saída digital.
//2) Faça um LED acender com brilho gradual, ou seja, de 0 até 255, e depois, apagar de forma gradual, 
//de 255 até 0. Use qualquer um dos pinos digitais PWM. Dê um intervalo de 100 ms entre cada alternância de acendimento e apagamento.
//3) Leia um valor inteiro via Serial e imprima a metade desse valor, também via Serial
//4) Controlar o brilho do LED através de um potenciômetro. Use o comando analogRead() para ler os dados 
//do potenciômetro (0 até 1023). Use o comando analogWrite() para escrever a luminosidade do LED (0 até 255). 
//O LED deve ser ligado em um pino PWM. Pesquise sobre e use a função map para mapear entre os dois intervalos. 
//Imprimir tanto o valor lido do potenciômetro quanto a luminosidade do LED (calculada) na porta serial.

//https://www.tinkercad.com/things/2mdGZU3hv0n

// C++ code
//


void setup() {
  pinMode(12, OUTPUT); // led
}

void loop() {
  digitalWrite(12, HIGH); // liga o LED
  delay(600); // espera por 600ms
  digitalWrite(12, LOW); // desliga o LED
  delay(600); // espera por mais 600ms 
}

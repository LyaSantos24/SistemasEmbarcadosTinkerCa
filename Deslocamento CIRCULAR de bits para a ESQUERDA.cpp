//https://www.tinkercad.com/things/aifptv9tLDP

//Fazer um programa no TinkerCad que leia via SERIAL um 
//valor inteiro de 16 bits (unsigned int) e imprima esse inteiro após ter feito o 
//deslocamento de 4 bits para a ESQUERDA. Entretanto, o deslocamento dever ser circular, 
//ou seja, o deslocamento é feito mas o bit mais  significativo não é perdido, 
//mas esse mesmo bit mais significativo deve ser o novo bit menos significativo.

//Por exemplo, se o valor inteiro de 16 bits for "33344" o resultado deve ser "9224".

//Explicação
//33344
//1000 0010 0100 0000
//0000 0100 1000 0001 (<< 1)
//0000 1001 0000 0010 (<< 1)
//0001 0010 0000 0100 (<< 1)
//0010 0100 0000 1000 (<< 1)
//= 8 + 1024 + 8192 = 9224

//Este problema pode ser resolvido somente com operações bit-a-bit.

unsigned int circularShiftLeft(unsigned int value, int shift) {
  // Verifica se o valor de shift é maior que 16
  shift %= 16;

  // Realiza o deslocamento circular à esquerda
  value = (value << shift) | (value >> (16 - shift));

  return value;
}

void setup() {
  Serial.begin(115200);
}

void loop() {
  if (Serial.available() > 0) {
    // Lê o valor inteiro de 16 bits enviado via SERIAL
    unsigned int value = Serial.read();
    Serial.print("Valor lido: ");
    Serial.println(value, HEX);
    
    value |= Serial.read() << 8;
    Serial.print("Valor lido (completo): ");
    Serial.println(value, HEX);

    // Realiza o deslocamento circular à esquerda de 4 bits
    unsigned int shiftedValue = circularShiftLeft(value, 4);
    Serial.print("Valor deslocado: ");
    Serial.println(shiftedValue, HEX);

    // Imprime o valor deslocado
    Serial.println(shiftedValue);
  }
}

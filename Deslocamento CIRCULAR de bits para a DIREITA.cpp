//https://www.tinkercad.com/things/hJWb312jp1Y

//Fazer um programa no TinkerCad que leia via SERIAL um valor inteiro de 16 bits (unsigned int) e 
imprima esse inteiro após ter feito o deslocamento de 4 bits para a DIREITA. Entretanto, o deslocamento 
dever ser circular, ou seja, o deslocamento é feito mas o bit menos significativo não é perdido, mas esse 
mesmo bit menos significativo deve ser o novo bit mais significativo.



//Por exemplo, se o valor inteiro de 16 bits for "33344" o resultado deve ser "2084".

//Explicação
//33344
//1000 0010 0100 0000
//0100 0001 0010 0000 (>> 1)
//0010 0000 1001 0000 (>> 1)
//0001 0000 0100 1000 (>> 1)
//0000 1000 0010 0100 (>> 1)
//= 4 + 32 + 2048 = 2084

//Este problema pode ser resolvido somente com operações bit-a-bit.


unsigned int circularShiftRight(unsigned int value, int shift) {
  // Verifica se o valor de shift é maior que 16
  shift %= 16;

  // Realiza o deslocamento circular à direita
  value = (value >> shift) | (value << (16 - shift));

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

    // Realiza o deslocamento circular à direita de 4 bits
    unsigned int shiftedValue = circularShiftRight(value, 4);
    Serial.print("Valor deslocado: ");
    Serial.println(shiftedValue, HEX);

    // Imprime o valor deslocado
    Serial.println(shiftedValue);
  }
}

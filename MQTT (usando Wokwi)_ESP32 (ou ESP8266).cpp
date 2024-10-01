//https://wokwi.com/projects/366274644719886337

//Exercício sobre MQTT (usando Wokwi)

//Faça um circuito simples com um ESP32 (ou ESP8266), dois LEDs e dois resistores (330 ohms).

//Este exercício pode ser subdividido em duas partes:

//Na primeira parte, use o protocolo MQTT para que o ESP 
//assine um tópico, onde, se a mensagem recebida for "1L" ele ligue o LED1; 
//se for "1D" ele desligue o LED1; se for "2L" ele ligue o LED2; e se for "2D" ele desligue o LED2. 
//Qualquer outra mensagem recebida deve ser só impressa na serial.

//Na segunda parte, o ESP32 deve publicar o estado de cada um dos dois LED's (se ligado ou desligado) 
//em um tópico específico. Por exemplo, a mensagem poderia ser "Led1: on Led2: off". 
//É claro que essa publicação só deve ser feita caso o estado de algum dos LEDs for modificado.

//Para facilitar a correção, por favor mantenha o broker test.mosquitto.org, que está disponível gratuitamente, 
//e foi o o broker utilizado nas aulas. Da mesma forma, mantenha os mesmos tópicos que foram utilizado nas aulas, 
//isto é, "inInTopic" e "outOutTopic".

#include <WiFi.h>
#include <PubSubClient.h>

// Parâmetros da Rede WiFi de Testes do WOKWI
const char* WIFI_SSID = "Wokwi-GUEST";
const char* WIFI_PASSWORD = "";

// Parâmetros do MQTT Server
const char* MQTT_CLIENT_ID = "";
const char* MQTT_BROKER = "test.mosquitto.org";
const int MQTT_PORT = 1883;
const char* MQTT_USER = "";
const char* MQTT_PASSWORD = "";
const char* MQTT_TOPIC = "outOutTopic";

// Configurações de pinos e estados dos LEDs
const int LED1_PIN = 15; 
const int LED2_PIN = 13;  
const int RESISTOR = 330;
const int LED_OFF = HIGH; 
const int LED_ON = LOW;   


// Objeto WiFiClient e PubSubClient
WiFiClient espClient;
PubSubClient client(espClient);

// Variáveis para controle de tempo
unsigned long lastMsg = 0;
const unsigned long interval = 3000;  // Intervalo de envio de mensagens MQTT (em milissegundos)

// Variáveis para controle do estado dos LEDs
bool led1State = false;
bool led2State = false;

void setup_wifi() {
  delay(10);
  // Conexão à rede Wi-Fi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println(message);

  if (message == "1L") {
    digitalWrite(LED1_PIN, HIGH);
    led1State = true;
  } else if (message == "1D") {
    digitalWrite(LED1_PIN, LOW);
    led1State = false;
  } else if (message == "2L") {
    digitalWrite(LED2_PIN, HIGH);
    led2State = true;
  } else if (message == "2D") {
    digitalWrite(LED2_PIN, LOW);
    led2State = false;
  } else {
    // Imprimir outras mensagens recebidas
    Serial.println(message);
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.publish("outOutTopic", "starting....");
      client.subscribe("inInTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);

  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  digitalWrite(LED1_PIN, LED_OFF);
  digitalWrite(LED2_PIN, LED_OFF);

  Serial.begin(115200);
  setup_wifi();
  client.setServer(MQTT_BROKER, MQTT_PORT);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > interval) {
    lastMsg = now;

    String ledStatus = "Led1(VERMELHO): ";
    ledStatus += (led1State ? "on " : "off ");
    ledStatus += "Led2(AZUL): ";
    ledStatus += (led2State ? "on" : "off");

    // Publicar o status dos LEDs se houver alteração
    static String previousLedStatus = "";
    if (ledStatus != previousLedStatus) {
      previousLedStatus = ledStatus;
      client.publish(MQTT_TOPIC, ledStatus.c_str());
    }
  }
}


//https://wokwi.com/projects/366909321651204097

//a) gere um circuito que inclua um LED, um sensor de umidade e temperatura (DHT11 ou DHT22) 
//e um sensor de movimento (motion sensor);

//b) gere um bot no Telegram que acesse o circuito no ESP e: 
//(i) ligue ou desligue o LED; (ii) o Telegram solicite e receba a umidade e a temperatura; 
//e (iii) o Telegram receba uma mensagem sempre que for detectado algum movimento no sensor de movimento do ESP.

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

#include <UniversalTelegramBot.h>
#include "DHT.h"

#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""
#define BOTtoken "6104119925:AAFT_NpXvfiR8Y1Sj5v94rT2kKpTqC9naLA"

#define LED_PIN 2
#define DHT_PIN 5
#define MOTION_SENSOR_PIN 4
#define DHTTYPE DHT22

#define BOT_SCAN 1000 
long lastTimeScan;
bool ledStatus;
bool motionDetected;

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
DHT dht(DHT_PIN, DHTTYPE);

void handleNewMessages(int numNewMessages) {
  float humidity, temperature;
  String message, chat_id, text, from_name;

  for (int i=0; i<numNewMessages; i++) {
    chat_id = String(bot.messages[i].chat_id);
    from_name = bot.messages[i].from_name;    
    text = bot.messages[i].text;
    Serial.println(text);

    if (text == "/ledon") {
      digitalWrite(LED_PIN, HIGH);
      ledStatus = true;
      bot.sendMessage(chat_id, "Led está ligado", "");
      Serial.println("Led está ligado");
    }

    if (text == "/ledoff") {
      ledStatus = false;
      digitalWrite(LED_PIN, LOW);
      bot.sendMessage(chat_id, "Led está desligado", "");
      Serial.println("Led está desligado");
    }

    if (text == "/env") {
      humidity = dht.readHumidity();
      temperature = dht.readTemperature();
      message = "A temperatura é de " + String(temperature, 2) + " graus celsius.\n";
      message += "A umidade relativa do ar é de " + String(humidity, 2)+ "%.\n";
      bot.sendMessage(chat_id, message, "Markdown");
      Serial.println(message);      
    }

    if (text == "/status") {
      String message = "Led está ";
      if(ledStatus){
        message += "ligado";
      }else{
        message += "desligado";
      }
      message += ". \n";
      humidity = dht.readHumidity();
      temperature = dht.readTemperature();
      message += "A temperatura é de " + String(temperature, 2) + " graus celsius.\n";
      message += "A umidade relativa do ar é de " + String(humidity, 2)+ "%.\n";

        if (motionDetected) {
        message += "Movimento foi detectado!\n";
       } else {
        message += "Nenhum movimento foi detectado.\n";
        }
  
      bot.sendMessage(chat_id, message, "");
      Serial.println(message);      
    }

    if (text == "/start") {
      String welcome = from_name + ", bem-vindo ao Bot da lya.\n";
      welcome += "Para interagir, use um dos comandos a seguir:\n";
      welcome += "/ledon: para ligar o Led\n";
      welcome += "/ledoff: para desligar o Led\n";
      welcome += "/env: saber a temperatura e umidade do ambiente\n";
      welcome += "/motion: Saber se foi detectado alguma movimento\n";
      welcome += "/status: para saber o status dos sensores e atuadores\n";
      bot.sendMessage(chat_id, welcome, "");
    }

 if (text == "/motion") {
      if (motionDetected) {
        bot.sendMessage(chat_id, "Movimento detectado!", "");
      } else {
        bot.sendMessage(chat_id, "Nenhum movimento detectado.", "");
      }
    }
  }
}

void handleMotion() {
  if (digitalRead(MOTION_SENSOR_PIN) == HIGH) {
    motionDetected = true;
  } else {
    motionDetected = false;
  }
}

void setupWifi(){  
  Serial.print("Connecting Wifi: ");
  Serial.println(WIFI_SSID);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT); 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
}

void setupPins(){
  pinMode(LED_PIN, OUTPUT); 
  pinMode(DHT_PIN, INPUT_PULLUP); 
  pinMode(MOTION_SENSOR_PIN, INPUT_PULLUP);
  digitalWrite(LED_PIN, LOW);
  ledStatus = false;
  dht.begin();
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  setupWifi();
  setupPins();
  lastTimeScan = millis();
}

void loop() {
  handleMotion(); // Verificar o sensor de movimento
  if (millis() > lastTimeScan + BOT_SCAN)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);  
    while(numNewMessages) {
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeScan = millis();
  }
}


#include <WiFi.h>
#include <PubSubClient.h>

//Atualize esses valores para de adaptar a sua rede WiFi
const char* ssid = "AshesToAshes"; //Moto One Vision
const char* password = "Vidval118"; //VanessaPerfeita
const char* mqtt_server = "broker.mqttdashboard.com";
#define mqtt_port         1883
#define MQTT_USER         ""
#define MQTT_PASSWORD     ""
#define MQTT_SERIAL_PUBLISH_CH   "/Calaza/Tx"
#define MQTT_SERIAL_RECEIVER_CH  "/Calaza/Rx" //pode ser o topico TX de outro grupo
//-------------------------------------------------------------------------------------------------------------------------
int estado = LOW;
int semaforo = 0;
unsigned long previousMillis = 0;
const long interval = 5000; //1 hora = 3600000
const long interval2 = 2000; //5 minutos = 300000

bool c = false; // c stands for "eh plausivel passar ambulancia agora?"
int g, y, r;
int led = 2, button = 23,
    green1 = 14, yellow1 = 12, red1 = 13,
    green2 = 25, yellow2 = 26, red2 = 27;
//-------------------------------------------------------------------------------------------------------------------------
WiFiClient wifiClient;
PubSubClient client(wifiClient);

//cofigura uma conexao wifi - assegure-se de colocar SSID e password no inicio do programa
void setup_wifi() {
    delay(10);
    Serial.println();
    Serial.println("## ExemploMQTT started");
    //Serial.println("## Build: " _DATE_ "-" _TIME_ );
    //Serial.println("## File:  [" _FILE_ "]");
    Serial.print("## Connecting to ");
    Serial.print(ssid);
    Serial.print("-");
    Serial.print(password);
    Serial.print(" ");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    randomSeed(micros());
    Serial.println("");
    Serial.println("## WiFi connected");
    Serial.print("## My IP address at local network: ");
    Serial.println(WiFi.localIP());
}

void reconnect() {
  //Fica em loop enquanto nao se conecta
  while (!client.connected()) {
    //Cria um identificador para o cliente MQTT. Deve ser unico!
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    Serial.print("## Client Id = [");
    Serial.print(clientId.c_str()); Serial.println("]");

    //Tenta conectar ao broker
    Serial.println("## Attempting MQTT connectiont to broker");
    if (client.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("## Client connected");
      
      //Se conectou faz uma publicacao de algo no topico desejado
      client.publish(MQTT_SERIAL_PUBLISH_CH, "Conectado com Sucesso\n");
      
      //e subscreve ao topico desejado
      client.subscribe(MQTT_SERIAL_RECEIVER_CH);
      
      Serial.println("## Connected ok. Published and subscribed OK");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("## Trying again in 5 seconds");
      //Aguarda algum tempo antes de tentar novamente
      delay(5000);
    }
  }
}

//rotina que eh chamada a cada publicacao num topico subscrito
void callback(char* topic, byte *payload, unsigned int length) {
    Serial.print("<< new message from broker. Topic:[");
    Serial.print(topic);
    Serial.print("] data length:");
    Serial.print(length);
    Serial.println(". Data follows...");
    Serial.write(payload, length);
    Serial.println(" ");
    //data received -------------------------------------------------------------------------------------------------
    char* str = reinterpret_cast<char *>(payload);
    char* str2 = "1";
    char* str3 = "2";
      if (str[0] != str2[0])
        if (str[0] == str3[0])
          semaforo = 2;
        else
          semaforo = 0;
      else
        semaforo = 1;
}

//setup do kit ESP32
void setup() {
  pinMode(green1, OUTPUT);
  pinMode(yellow1, OUTPUT);
  pinMode(red1, OUTPUT);
  pinMode(green2, OUTPUT);
  pinMode(yellow2, OUTPUT);
  pinMode(red2, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  
  Serial.begin(115200);     //velocidade da serial
  Serial.setTimeout(500);   //timeout da porta para informacoes recebidas
  setup_wifi();
  Serial.print("## MQTT Broker at [");
  Serial.print(mqtt_server);
  Serial.print(":");
  Serial.print(mqtt_port);
  Serial.println("]");
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  reconnect();
}

//rotina principal
int len = 0; //tamanho de uma mensagem recebida
long eventcnt = 0;
void loop() { 
   client.loop(); //aqui ocorre uma varredura das comunicacoes, checando se o broker enviou alguma informacao nova
   //-----------------------------------------------------------------------------------------------------------------
   if (!digitalRead(button) and c) {
    client.publish(MQTT_SERIAL_PUBLISH_CH, "Ambulancia ja passou\n");
    semaforo = 0;
    c = false;
   }
   //-----------------------------------------------------------------------------------------------------------------
  switch (semaforo) {
  case 1:
    c = true;
    digitalWrite(led, HIGH);
    trajeto (true);
    funciona ();
    break;
  case 2:
    c = true;
    digitalWrite(led, HIGH);
    trajeto(false);
    funciona ();
    break;
  case 0:
  digitalWrite(led, LOW);
    unsigned long currentMillis = millis();
  
  if (previousMillis > currentMillis)
    previousMillis = 0;
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    troca();
    funciona();
  }
  
  if (semaforo == 0 && currentMillis - previousMillis >= interval2){
    digitalWrite(yellow1, HIGH);
    digitalWrite(green1, LOW);
  }
    break;
  }
   //-----------------------------------------------------------------------------------------------------------------
   //checa se ha dados na serial. Se houver pega ate 500 bytes digitados pelo usuario 
   //e publica no topico para quem quiser escutar e estiver assinando
   if (Serial.available() > 0) {
     char bfr[501];
     memset(bfr,0, 501);
     len = Serial.readBytesUntil( '\n',bfr,500);
     if (!client.connected()) {
        Serial.println("## Broker not connected. Reconnecting");
        reconnect();
     }
     client.publish(MQTT_SERIAL_PUBLISH_CH, bfr);

     bfr[len]=0;
     Serial.print(">> Published to topic: [");
     Serial.print(MQTT_SERIAL_PUBLISH_CH);
     Serial.print("] Data: [");
     Serial.print(bfr);
     Serial.println("]");
   }
   {
    if (!client.connected()) {
      Serial.println("## Broker not connected. Reconnecting");
      reconnect();
    }
    
   }
 }

 void troca (){
  g = green1;
  y = yellow1;
  r = red1;
  green1 = green2;
  yellow1 = yellow2;
  red1 = red2;
  green2 = g;
  yellow2 = y;
  red2 = r;
}

void funciona (){
  digitalWrite(red1, LOW);
  digitalWrite(yellow1, LOW);
  digitalWrite(green1, HIGH);
  digitalWrite(red2, HIGH);
  digitalWrite(yellow2, LOW);
  digitalWrite(green2, LOW);
}

void trajeto (bool j){
  if (j) {
    green1 = 14,
    yellow1 = 12,
    red1 = 13,
    green2 = 25,
    yellow2 = 26,
    red2 = 27;
  } else {
    green2 = 14;
    yellow2 = 12;
    red2 = 13;
    green1 = 25;
    yellow1 = 26;
    red1 = 27;
  }
}

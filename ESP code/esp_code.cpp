#include <PubSubClient.h> //library for MQTT
#include <WiFi.h> //library for using ESP8266 WiFi 
#include <Adafruit_Sensor.h> //Library for Adafruit sensors , we are using for DHT
#include <DHT_U.h> //DHT library which uses some func from Adafruit Sensor library
#include <string.h>


#include <ArduinoJson.h> //library for Parsing JSON


//defining Pins
#define DHTPIN 5
#define LED 2
#define RELE 23

 
//DHT parameters
#define DHTTYPE    DHT11     // DHT 11
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
 
//MQTT Credentials
const char* ssid = "KOFUJI_2022";//setting your ap ssid
const char* password = "b0r@b0r@";//setting your ap psk
const char* mqttServer = "broker.mqttdashboard.com"; //MQTT URL
const char* mqttUserName = "mqtt username";  // MQTT username
const char* mqttPwd = "mqtt password";  // MQTT password
const char* clientID = "username0001"; // client id username+0001
const char* topic = "Tempdata2"; //publish topic
 
//parameters for using non-blocking delay
unsigned long previousMillis = 0;
const long interval = 5000;
String topic2;
 
String msgStr = "";      // MQTT message buffer
 
float temp, hum;
 
 
//setting up wifi and mqtt client
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup_wifi() {
  delay(10);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 
}
 
void reconnect() {
  while (!client.connected()) {
    if (client.connect(clientID, mqttUserName, mqttPwd)) {
      Serial.println("MQTT connected");
 
      client.subscribe("Luzes");
      client.subscribe("Travas");
      Serial.println("Topic Subscribed");
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);  // wait 5sec and retry
    }
 
  }
 
}
 
//subscribe call back
void callback(char*topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  String data = "";
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    data += (char)payload[i];
  }
  Serial.print("Message size :");
  Serial.println(length);
  Serial.println();
  Serial.println("-----------------------");
  Serial.println(data);
 Serial.println(topic);

 topic2 = String(topic);
if(data=="ON" and (topic2 == "Luzes")){
  Serial.println("LED");
 digitalWrite(LED, HIGH);
}
else{
  digitalWrite(LED, LOW);
}

if(data=="ON" and  (topic2 == "Travas")){
  Serial.println("RELEZUDO");
 digitalWrite(RELE, HIGH);
}
else{
  digitalWrite(RELE, LOW);
}
}
 
 
void setup() {
  Serial.begin(115200);
  // Initialize device.
  // get temperature sensor details.
 
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  pinMode(RELE, OUTPUT);
  digitalWrite(RELE, LOW);
 
  setup_wifi();
 
  client.setServer(mqttServer, 1883); //setting MQTT server
  client.setCallback(callback); //defining function which will be called when message is received.
 
}
 
void loop() {
  if (!client.connected()) { //if client is not connected
    reconnect(); //try to reconnect
  }
  client.loop();

 
}

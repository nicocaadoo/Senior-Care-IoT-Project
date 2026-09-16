#include <WiFi.h>
#include <PubSubClient.h>
#include <DFRobot_DHT11.h>
#include <LCD_I2C.h>

#define boton1 23

#define DHT11_PIN 33
#define trigger 23
#define echo 18
#define pulso 32

#define frec 10000
#define resolucion 12

int horas = 0;
int minutos = 0;

LCD_I2C lcd(0x27, 16, 2);
DFRobot_DHT11 DHT;
float duracion, distancia;

void setup_wifi();
void procesar_mensajes(char *topic, byte *mensaje, unsigned int longitud);
int potenciometro();

WiFiClient BoardESP32;
PubSubClient client_mqtt(BoardESP32);

// WiFi network
const char* ssid="Tec-IoT";
const char* password="spotless.magnetic.bridge";

// MQTT Broker de ThingSpeak
const char *broker = "mqtt3.thingspeak.com";
int puerto = 1883;
const char *id_cliente = "JjM1BichLzwNIQQhOQAtFiU";  //Id_client del MQTT device del canal donde se publica
const char* mqttUser = "JjM1BichLzwNIQQhOQAtFiU";    // Nombre de usuario de ThingSpeak del MQTT device donde se publica
const char* mqttPass = "ZQPPukKX0kdfyHBnNmzWXafx";    // Contraseña de ThingSpeak del MQTT device donde se publica
unsigned long channelID =3171935;  // Reemplaza con tu número de canal donde se publica
const char* writeAPIKey = "QV2B9J4VXBN4FC9L";  // TU_API_KEYClave de escritura de ThingSpeak donde publicas
// Tópico MQTT para publicar datos
const char* mqttTopic = "channels/3171935/publish"; // Reemplaza con tu número de canal donde publicas
// Tópico MQTT para suscribirse
const char* mqttTopicListen = "channels/3156518/subscribe/fields/field1"; // Reemplaza con tu número de canal donde recibes
const char* mqttTopicListen2 = "channels/3156518/subscribe/fields/field2"; // Reemplaza con tu número de canal donde recibes

// Global variables
unsigned long lastConnectionTime = 0;
// Constants
const unsigned long postingInterval = 20L * 1000L;


int muestras = 50000;

void setup() {
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  pinMode(DHT11_PIN, INPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(115200);
  setup_wifi();
  //Configuracion PWM
  //Conexion al broker
  client_mqtt.setServer(broker, puerto);
  connectToMQTT();
  client_mqtt.setCallback(procesar_mensajes);
  if (client_mqtt.subscribe(mqttTopicListen)) {
    Serial.printf("Suscrito a topico %s\n", mqttTopicListen);
  }

  if (client_mqtt.subscribe(mqttTopicListen2)) {
    Serial.printf("Suscrito a topico %s\n", mqttTopicListen2);
  }
}
void loop() {
  //DHT.read(DHT11_PIN);
  if (!client_mqtt.connected()) {
    connectToMQTT();
  }
  //Esta funcion se debe llamar para mantener activa la conexion con el broker
  client_mqtt.loop();
  publicar();
  //delay(1000);
}

void connectToMQTT()
{
  Serial.println("Conectando al broker ThingSpeak...");
   if (client_mqtt.connect(id_cliente, mqttUser, mqttPass)) {
    Serial.println("Connected to MQTT Broker!");
   }
  else {
    Serial.println("Connected to MQTT failed...");
   }
   
  if (client_mqtt.connect(id_cliente)) {
    Serial.print("Conectado con broker ");
    Serial.println(broker);
   }
  else {
    Serial.print("No se pudo conectar con broker");
   }
}
void publicar()
{
    if (millis() - lastConnectionTime > postingInterval) {
    // Simulamos datos de temperatura y humedad

       char *itoa(int valor, char *cadena, int base);

       digitalWrite(trigger, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigger, LOW);
      duracion = pulseIn(echo, HIGH,30000);
      distancia = 0.017 * duracion;
       DHT.read(DHT11_PIN);
       lcd.setCursor(0,1);
       int bpm = analogRead(pulso);
       bpm = bpm/35;
       Serial.println(bpm);
      lcd.print("T:"+String(DHT.temperature)+"   ");
      if(DHT.temperature > 38){
        lcd.setCursor(0,1);
        lcd.print("!T ALTA!");
      }
      if(DHT.temperature < 20){
        lcd.setCursor(0,1);
        lcd.print("!T BAJA!");
      }
      lcd.setCursor(8,1);
      lcd.print("P:"+String(bpm)+"    ");
      if(bpm < 60){
        lcd.setCursor(8,1);
        lcd.print("!P BAJO!");
      }
      if(bpm > 100){
        lcd.setCursor(8,1);
        lcd.print("!P ALTO!");
      }
      Serial.println("Dist: "+String(distancia));
      
       float temperatura = DHT.temperature;
       float humedad = DHT.humidity;
       delay(10);

   // Formato de datos para ThingSpeak (field1, field2, field3)
       String datos = "field1=" + String(temperatura) + "&field2=" + String(bpm)+ "&field3=" + String(distancia);

  // Publicar en el tópico MQTT
       if (client_mqtt.publish(mqttTopic, datos.c_str())) {
         Serial.println("Datos publicados en ThingSpeak");
       } else {
         Serial.println("Error al publicar datos");
       }
       lastConnectionTime = millis();
    }
}

void setup_wifi() {
  delay(50);
  // Connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected - ESP IP address: ");
  Serial.println(WiFi.localIP());
}
/*
void procesar_mensajes(char *topic, byte *mensaje, unsigned int longitud) {
  char mensaje_local[100] = {0};

  Serial.print("Topic: ");
  Serial.println(topic);
  Serial.print("Mensaje recibido: ");
  for (int i = 0; i < longitud; i++) {
    Serial.write(mensaje[i]);
    mensaje_local[i] = mensaje[i];
  }
  Serial.println();
//Convierto el string recibido a long
  int pwm = strtol(mensaje_local, 0, 10);
}
*/
void procesar_mensajes(char *topic, byte *mensaje, unsigned int longitud) {
  char mensaje_local[100] = {0};

  Serial.print("Topic: ");
  Serial.println(topic);
  Serial.print("Mensaje recibido: ");

  for (int i = 0; i < longitud; i++) {
    Serial.write(mensaje[i]);
    mensaje_local[i] = mensaje[i];
  }
  Serial.println();

  int valor = strtol(mensaje_local, NULL, 10);

  // ------------------------------
  //      Procesar cada campo
  // ------------------------------
  if (strcmp(topic, mqttTopicListen) == 0) {
      horas = valor;      // ← Guarda el field1 en horas
      Serial.print("→ Field1 (horas) = ");
      Serial.println(horas);
      lcd.setCursor(5,0);
      lcd.print(horas);
      lcd.setCursor(7,0);
      lcd.print(":");

  }

  else if (strcmp(topic, mqttTopicListen2) == 0) {
      minutos = valor;    // ← Guarda el field2 en minutos
      Serial.print("→ Field2 (minutos) = ");
      Serial.println(minutos);
      lcd.setCursor(8,0);
      lcd.print(minutos);
  }
}

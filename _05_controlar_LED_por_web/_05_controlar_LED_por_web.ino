#include <ESP8266WiFi.h>
#define LED_GPIO 2

const char* ssid = "Orange-152A";
const char* password = "3EE529C4";

bool LED_estado = LOW;

WiFiServer server(80); //objeto servidor que inicializaremos en el puerto 80
 
void setup() {
  Serial.begin(115200);

  // Poner el módulo WiFi en modo station y desconectar de cualquier red a la que pudiese estar previamente conectado
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(2000);

  pinMode(LED_GPIO, OUTPUT);
  digitalWrite(LED_GPIO, LOW);
 
  //Conectar a la red WiFi
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Conectado, la IP del dispositivo es: ");
  Serial.println(WiFi.localIP());
 
  //Iniciar server
  server.begin();
  Serial.println("Servidor iniciado");
}
 
void loop() {
  //chequeamos si se ha conectado un cliente, en caso contrario terminar (se reiniciaría)
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  //Esperar hasta que el cliente envíe algún dato
  while(!client.available()){
    delay(1);
  }
 
  //Lee la request del cliente
  String request = client.readStringUntil('\r');
  client.flush(); //vacía por seguridad

  //Request en un objeto String que contiene la URL compelta, incluyendo parámetros. Buscamos si contien la cadena "/LED=ON"
  if (request.indexOf("/LED=ON") != -1){
    digitalWrite(LED_GPIO, LOW); //debería ser HIGH, pero el LED funciona en modo inverso en algunas placas, includo la nodemcu
    LED_estado=HIGH;
  }
  else
    if (request.indexOf("/LED=OFF") != -1){
      digitalWrite(LED_GPIO, HIGH); //debería ser HIGH, pero el LED funciona en modo inverso en algunas placas, includo la nodemcu
      LED_estado=HIGH;
    }
      
  //Parte "response" del servidor hacia el cliente, una página Web
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //requerido
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("LED ");
   if(LED_estado == HIGH)
    client.print("On");
  else
    client.print("Off");

  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED=OFF\"><button>Turn Off </button></a><br />");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}

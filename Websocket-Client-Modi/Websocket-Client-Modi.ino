/*
  Esp8266 Websockets Client
  This sketch:
        1. Connects to a WiFi network
        2. Connects to a Websockets server
        3. Sends the websockets server a message ("Hello Server")
        4. Prints all incoming messages while the connection is open
  Hardware:
        For this sketch you only need an ESP8266 board.
  Created 15/02/2019
  By Gil Maimon
  https://github.com/gilmaimon/ArduinoWebsockets
*/
// 2020-02-21 Ejemplo tomado de:
// https://github.com/gilmaimon/ArduinoWebsockets/blob/master/examples/Esp8266-Client/Esp8266-Client.ino
// Modificado 2020-02-25
// Para sacar la funcion que recibe los mensajes desde el server fuera de la funcion setup()


#include <ArduinoWebsockets.h>
#include <ESP8266WiFi.h>

const char* ssid = "nopalin_lab"; //Enter SSID
const char* password = "l1234567890"; //Enter Password
const char* websockets_server_host = "192.168.200.169"; //Enter server adress
const uint16_t websockets_server_port = 8888; // Enter server port

const int pinSensor = 2;
//const int pinLED = 13;

using namespace websockets;

WebsocketsClient client;

void onMessageCallback(WebsocketsMessage message) {
//    Serial.print("Got Message: ");
//    Serial.println(message.data());
//}
    
// run callback when messages are received
//    client.onMessage([&](WebsocketsMessage message) {
      String mensaje = message.data();
      Serial.println("Ha llegado un mensaje: ");
      //Serial.println(message.data());
      Serial.println(">" + mensaje + "<");
      if (mensaje == "1"){
        digitalWrite(LED_BUILTIN, HIGH);
        delay(1000);
        digitalWrite(LED_BUILTIN, LOW);
        client.send("A");
        
      } else if (mensaje == "2"){
        digitalWrite(LED_BUILTIN, HIGH);
        delay(1000);
        digitalWrite(LED_BUILTIN, LOW);
        client.send("B");
        
      } else if (mensaje == "3"){
        digitalWrite(LED_BUILTIN, HIGH);
        delay(1000);
        digitalWrite(LED_BUILTIN, LOW);
        client.send("C");
        
      } else if (mensaje == "4"){
        digitalWrite(LED_BUILTIN, HIGH);
        delay(1000);
        digitalWrite(LED_BUILTIN, LOW);

        client.send("D");
      }
        
//    });
}

void onEventsCallback(WebsocketsEvent event, String data) {
  Serial.println(data);
  if(event == WebsocketsEvent::ConnectionOpened) {
      Serial.println("Connnection Opened");
  } else if(event == WebsocketsEvent::ConnectionClosed) {
      Serial.println("Conexion cerrada!");
  } else if(event == WebsocketsEvent::GotPing) {
      Serial.println("Got a Ping!");
  } else if(event == WebsocketsEvent::GotPong) {
      Serial.println("Got a Pong!");
  }
}

void setup() {
    
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(pinSensor, INPUT_PULLUP);
    
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    // Connect to wifi
    WiFi.begin(ssid, password);
    

    // Wait some time to connect to wifi
    for(int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++) {
        Serial.print(".");
        delay(1000);
    }
    while(WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
    }
    // Check if connected to wifi
    /*
    if(WiFi.status() != WL_CONNECTED) {
        Serial.println("No Wifi!");
        return;
    }
    */
    
    Serial.println("Connection status: ");
    Serial.println(WiFi.status());
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    
    Serial.println("Connectado a la red Wifi, Intentando conexion al websocket server.");
    // try to connect to Websockets server
    bool connected = client.connect(websockets_server_host, websockets_server_port, "/conectar");
    if(connected) {
        Serial.println("Conectado!");
        //client.send("{" + char(34) +  "CMD" + char(34) +  ":" + char(34) + "SALUDAR" + char(34) + "," + char(34) + "MSG" +  char(34) + ":" + char(34) + "HOLA SERVER" + char(34) + "}");
        client.send("Hello Server");
    } else {
        Serial.println("No hay conexion al server!");
    }
    client.onMessage(onMessageCallback);
    client.onEvent(onEventsCallback);

}

void loop() {
    // let the websockets client check for incoming messages
    if(client.available()) {
        client.poll();
    }
    int value = digitalRead(pinSensor);
    //Serial.println(value);
    if (value == LOW){
      digitalWrite(LED_BUILTIN, HIGH);
    } else {
      digitalWrite(LED_BUILTIN, LOW);
    }
    delay(500);

}

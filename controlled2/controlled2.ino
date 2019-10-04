#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid ="AngieM";
const char* password = "angieM17";
const int led = D1; 

ESP8266WebServer server(80);

void geton(){
String html="<html><body><center><h1> led encendido </h1></center> <br> <a href=\"/control\"\"> <button > inicio </button> </a></body></html>";
  digitalWrite(led,HIGH);
  server.send(200,"text/html",html);
}

void getoff(){
  digitalWrite(led,0);
  String html="<html><body><center><h1> led apagado </h1></center> <br> <a href=\"/control\"\"> <button > inicio </button> </a></body></html>";
  
  server.send(50,"text/html",html);
}

void inicio() {
 String html="<html><title>bienvenido</title><body><center><h1>BIENVENIDO</h1><br><br><h3> encender o apagar un led con un boton><a href=\"/control\"\"> <button > controlar led </button> </a> <br>";
  html+="</body></center></html>";
  server.send(200, "text/html", html);
}
void getboton(){

  String html="<html><title>boton</title> <body><a href=\"/on\"\"> <button > LED ON </button> </a><a href=\"/off\"\"> <button > LED OFF </button> </a><br><br><a href=\"/\"\"> <button > pagina inicial </button> </a></body></html>";
   server.send(200, "text/html", html);
}


void setup() {
 //inicializa el puerto serie
 Serial.begin(115200);
 delay(10);
 //inicializa el led
 pinMode(led,OUTPUT);
 
 //Inicializa el módulo wifi
 WiFi.mode(WIFI_STA); 
 WiFi.disconnect(); 
 Serial.println();  
 //conecta con la red wifi
 Serial.print("Connecting to ");
 Serial.println(ssid);
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {   
    delay(500);
    Serial.print(".");
 }
 Serial.println("");
 Serial.println("WiFi connected");
 Serial.print("IP address: ");
 Serial.println(WiFi.localIP());
 
 
 server.on("/",inicio);
 server.on("/control",getboton);
 server.on("/on",geton);
 server.on("/off",getoff);
 //inicializa el servidor web
 server.begin();
 Serial.println("Servidor HTTP activo");
}

void loop() {
 server.handleClient();
}

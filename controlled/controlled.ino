/*enciende y apaga un led cada vez que se recarga la pagina web del servidor AP*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>


#define APSSID "AngieM"
#define APPSK  "angieM17"
#define led D1
/* nota en caso de cambiar la red (APSSID) asegurese de que el APPSK sea de 8 o mas caracteres*/

/* asigna los valores de red */
const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer server(80);

/* El punto de acceso es por la ip http://192.168.4.1 en el navegador
   .
*/

boolean est=true;
String estado=" ";
void handleRoot() {
  digitalWrite(led,est);
  Serial.println(est);
  if (est){
    estado="encendido";
   }else{
    estado="apagado";
  }
  est=!est;
  
 String html="<!DOCTYPE html ><head><meta http-equiv='Content-Type' content='text/html; charset=iso-8859-1' /><title>paginas</title></head><body><h1>con esta pagina puedes encender o apagar un led solo haciendo la recarga de la misma</h1><br>estado del led: ";
 html+=estado;
 
 html+="<br><br><a href=\"/\"\"> <button > pagina inicial </button> </a></body></html>";
  
  server.send(200, "text/html", html);
  
}

void getboton(){

  String html="<html><title>boton</title> <body><a href=\"/on\"\"> <button > LED ON </button> </a><a href=\"/off\"\"> <button > LED OFF </button> </a><br><br><a href=\"/\"\"> <button > pagina inicial </button> </a></body></html>";
   server.send(200, "text/html", html);
}
void getestado(){
  String html="<html><title>bienvenido</title><body><center><h1>BIENVENIDO</h1><br><br>en este servidor puedes realizar 2 opciones: <br><h3>opcion1: encender o apagar un led con un boton><a href=\"/boton\"\"> <button > opcion 1 </button> </a> <br>";
  html+="<h3>opcion 2: encender o apagar un led recargando la pagina <a href=\"/recarga\"\"> <button > opcion 2 </button> </a> </body></center></html>";
  server.send(200, "text/html", html);
}

void geton(){
String html="<html><body><center><h1> led encendido </h1></center> <br> <a href=\"/boton\"\"> <button > inicio </button> </a></body></html>";
  digitalWrite(led,HIGH);
  server.send(200,"text/html",html);
}

void getoff(){
  digitalWrite(led,0);
  String html="<html><body><center><h1> led apagado </h1></center> <br> <a href=\"/boton\"\"> <button > inicio </button> </a></body></html>";
  
  server.send(50,"text/html",html);
}
void setup() {
  pinMode(led,OUTPUT);
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configurando punto de acceso...");
  /*inicia el punto de acceso wifi*/
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.println(ssid);
  Serial.print("direccion IP del AP: ");
  Serial.println(myIP);
  server.on("/", getestado);
  server.on("/boton",getboton);
  server.on("/on",geton);
  server.on("/off",getoff);
  server.on("/recarga", handleRoot);
  server.begin();
  Serial.println("servidor HTTP iniciado");
}

void loop() {
  server.handleClient();


}

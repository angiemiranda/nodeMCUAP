/*cuenta las veces que se recarga la pagina web del servidor AP*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>


#define APSSID "AngieM"
#define APPSK  "angieM17"
/* nota en caso de cambiar la red (APSSID) asegurese de que el APPSK sea de 8 o mas caracteres*/

/* asigna los valores de red */
const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer server(80);

/* El punto de acceso es por la ip http://192.168.4.1 en el navegador
   .
*/
void handleRoot() {
 String html="<!DOCTYPE html ><head><meta http-equiv='Content-Type' content='text/html; charset=iso-8859-1' /><title>numero de refresh</title><script>var contador=isNaN(parseInt(window.name))?1:parseInt(window.name);document.write('usted actualizo la pagina: '+contador+ ' veces');contador++;window.name=contador;</script></head><body></body></html>";
  server.send(200, "text/html", html);
  
}

void setup() {
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
  server.on("/", handleRoot);
  server.begin();
  Serial.println("servidor HTTP iniciado");
}

void loop() {
  server.handleClient();
 


}

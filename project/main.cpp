#include <ESP8266WiFi.h>

const char* ssid     = "LOGA-9";
const char* password = "iwowt3ga";

WiFiServer server(80);

String header;

String frente = "off";
String re = "off";
String direita = "off";
String esquerda = "off";


String output5State = "off";

String output4State = "off";
String output14State = "off";

String output12State = "off";
String output13State = "off";



const int output5 = 5;

const int output4 = 4;
const int output14 = 14;


const int output12 = 12;
const int output13 = 13;


unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  
  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);
  pinMode(output14, OUTPUT);
  pinMode(output12, OUTPUT);
  pinMode(output13, OUTPUT);
  
  // Set outputs to LOW
  digitalWrite(output5, LOW);
  digitalWrite(output4, LOW);
  digitalWrite(output14, LOW);
  digitalWrite(output12, LOW);
  digitalWrite(output13, LOW);

 
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();  

  if (client) {                         
    Serial.println("New Client.");         
    String currentLine = "";                
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { 
      currentTime = millis();         
      if (client.available()) {            
        char c = client.read();          
        Serial.write(c);                   
        header += c;
        if (c == '\n') {                    
          
          if (currentLine.length() == 0) {
            
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("GPIO 5 on");
              output5State = "on";
              digitalWrite(output5, HIGH);
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("GPIO 5 off");
              output5State = "off";
              digitalWrite(output5, LOW);
            } else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("GPIO 4 on");
              frente = "on";
              digitalWrite(output4, LOW);
              digitalWrite(output14, HIGH);

              digitalWrite(output12, LOW);
              digitalWrite(output13, HIGH);
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("GPIO 4 off");
              frente = "off";
              digitalWrite(output4, LOW);
              digitalWrite(output14, LOW);
              digitalWrite(output12, LOW);
              digitalWrite(output13, LOW);
            } else if (header.indexOf("GET /re/on") >= 0) {
              Serial.println("GPIO 4 on");
              re = "on";
              digitalWrite(output14, LOW);
              digitalWrite(output4, HIGH);

              digitalWrite(output13, LOW);
              digitalWrite(output12, HIGH);
            } else if (header.indexOf("GET /re/off") >= 0) {
              Serial.println("GPIO 4 off");
              re = "off";
              digitalWrite(output4, LOW);
              digitalWrite(output14, LOW);
              digitalWrite(output12, LOW);
              digitalWrite(output13, LOW);
            } else if (header.indexOf("GET /direita/on") >= 0) {
              Serial.println("GPIO 4 on");
              direita = "on";
              digitalWrite(output12, LOW);
              digitalWrite(output13, HIGH);
            } else if (header.indexOf("GET /direita/off") >= 0) {
              Serial.println("GPIO 4 off");
              direita = "off";
              digitalWrite(output4, LOW);
              digitalWrite(output14, LOW);
              digitalWrite(output12, LOW);
              digitalWrite(output13, LOW);
            } else if (header.indexOf("GET /esquerda/on") >= 0) {
              Serial.println("GPIO 4 on");
              esquerda = "on";
              digitalWrite(output4, LOW);
              digitalWrite(output14, HIGH);
            } else if (header.indexOf("GET /esquerda/off") >= 0) {
              Serial.println("GPIO 4 off");
              esquerda = "off";
              digitalWrite(output4, LOW);
              digitalWrite(output14, LOW);
              digitalWrite(output12, LOW);
              digitalWrite(output13, LOW);
            }
            
           
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;width: 100%;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button3 { background-color: #195B6A; border: none; color: white; padding: 16px 40px;width: 48%;float:left;");
            client.println("text-decoration: none; font-size: 25px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            
            
            
            
            client.println("<body><h1>tezla</h1>");
            
            
            client.println("<p>GPIO 5 - State " + output5State + "</p>");
               
            if (output5State=="off") {
              client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
            
            client.println("<p>State " + frente + "</p>");
              
            if (frente=="off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">frente ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">frente OFF</button></a></p>");
            }

            
            

                  
            if (direita=="off") {
              client.println("<p><a href=\"/direita/on\"><button class=\"button3\">direita ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/direita/off\"><button class=\"button3 button2\">direita OFF</button></a></p>");
            }

            if (esquerda=="off") {
              client.println("<p><a href=\"/esquerda/on\"><button class=\"button3\">esquerda ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/esquerda/off\"><button class=\"button3 button2\">esquerda OFF</button></a></p>");
            }

            client.println("<p>State " + re + "</p>");
                
            if (re=="off") {
              client.println("<p><a href=\"/re/on\"><button class=\"button\">re ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/re/off\"><button class=\"button button2\">re OFF</button></a></p>");
            }

            client.println("</body></html>");
            
            
            client.println();
            
            break;
          } else { 
            currentLine = "";
          }
        } else if (c != '\r') {  
          currentLine += c;      
        }
      }
    }
    header = "";
    
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
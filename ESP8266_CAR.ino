#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

String command;             // String to store app command state.
int speedCar = 800;         // 400 - 1023.

const char* ssid = "NodeMCU Car";
ESP8266WebServer server(80);

void setup() {
  pinMode(14, OUTPUT);  // ENA
  pinMode(12, OUTPUT);  // ENB
  pinMode(15, OUTPUT);  // IN_1
  pinMode(13, OUTPUT);  // IN_2
  pinMode(2, OUTPUT);   // IN_3
  pinMode(0, OUTPUT);   // IN_4
  
  Serial.begin(115200);
  
  // Connecting WiFi
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
  // Starting WEB-server 
  server.on("/", HTTP_handleRoot);
  server.onNotFound(HTTP_handleRoot);
  server.begin();
}

void goForward() {
  digitalWrite(15, LOW);
  digitalWrite(13, HIGH);
  analogWrite(14, speedCar);

  digitalWrite(2, HIGH);
  digitalWrite(0, LOW);
  analogWrite(12, speedCar);
}

void goBackward() {
  digitalWrite(15, HIGH);
  digitalWrite(13, LOW);
  analogWrite(14, speedCar);

  digitalWrite(2, LOW);
  digitalWrite(0, HIGH);
  analogWrite(12, speedCar);
}

void goLeft() {
  digitalWrite(15, LOW);
  digitalWrite(13, HIGH);
  analogWrite(14, speedCar);

  digitalWrite(2, LOW);
  digitalWrite(0, HIGH);
  analogWrite(12, speedCar);
}

void goRight() {
  digitalWrite(15, HIGH);
  digitalWrite(13, LOW);
  analogWrite(14, speedCar);

  digitalWrite(2, HIGH);
  digitalWrite(0, LOW);
  analogWrite(12, speedCar);
}

void stopRobot() {
  digitalWrite(15, LOW);
  digitalWrite(13, LOW);
  analogWrite(14, speedCar);

  digitalWrite(2, LOW);
  digitalWrite(0, LOW);
  analogWrite(12, speedCar);
}

void loop() {
  server.handleClient();
  
  command = server.arg("State");
  if (command == "Forward") goForward();
  else if (command == "Backward") goBackward();
  else if (command == "Left") goLeft();
  else if (command == "Right") goRight();
  else if (command == "Stop") stopRobot();
}

void HTTP_handleRoot(void) {
  if (server.hasArg("State")) {
    Serial.println(server.arg("State"));
  }
  
  String htmlContent = "<!DOCTYPE html>\n"
    "<html>\n"
    "<head>\n"
    "<title>NodeMCU Car Control</title>\n"
    "<style>\n"
    ".container {\n"
    "  text-align: center;\n"
    "  margin-top: 50px;\n"
    "}\n"
    ".button {\n"
    "  display: inline-block;\n"
    "  width: 80px;\n"
    "  height: 80px;\n"
    "  margin: 10px;\n"
    "  background-color: #e7e7e7;\n"
    "  border: 2px solid #777777;\n"
    "  border-radius: 50%;\n"
    "  text-decoration: none;\n"
    "  font-size: 18px;\n"
    "  color: #333333;\n"
    "  line-height: 80px;\n"
    "}\n"
    "</style>\n"
    "<script>\n"
    "function sendCommand(command) {\n"
    "  var xhr = new XMLHttpRequest();\n"
    "  xhr.open('GET', '/?State=' + command, true);\n"
    "  xhr.send();\n"
    "}\n"
    "</script>\n"
    "</head>\n"
    "<body>\n"
    "<div class='container'>\n"
    "<a class='button' href='#' onclick='sendCommand(\"Forward\")'>Forward</a><br>\n"
    "<a class='button' href='#' onclick='sendCommand(\"Left\")'>Left</a>\n"
    "<a class='button' href='#' onclick='sendCommand(\"Stop\")'>Stop</a>\n"
    "<a class='button' href='#' onclick='sendCommand(\"Right\")'>Right</a><br>\n"
    "<a class='button' href='#' onclick='sendCommand(\"Backward\")'>Backward</a>\n"
    "</div>\n"
    "</body>\n"
    "</html>\n";

  server.send(200, "text/html", htmlContent);
  delay(1);
}
/**********************************************************************
* Filename    : Blink
* Description : Make an led blinking.
* Auther      : www.freenove.com
* Modification: 2024/06/18
**********************************************************************/

// Import required libraries
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "./finger.h"

// // Replace with your network credentials
const char* ssid     = "ESP32-Access-Point";
const char* password = "123456789";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

Finger* thumb;
Finger* indx;
Finger* middle;
Finger* ring;
Finger* pinky;

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);

  // initalizing fingers
  thumb = new Finger(180, 12);
  indx = new Finger(180, 14);
  middle = new Finger(180, 27);
  ring = new Finger(180, 26);
  pinky = new Finger(180, 25);

  Serial.print("Setting AP (Access Point)…");
  // creating wifi access point
  WiFi.softAP(ssid, password);

IPAddress IP = WiFi.softAPIP();
  Serial.print("AP (short for access point btw) IP address: ");
  Serial.println(IP);

  // Route for moving fingers
  server.on("/fingers/angle/set", HTTP_GET, [] (AsyncWebServerRequest *request) {
    request->

    if (request->hasParam("thumb")) {
      Serial.println("Request to move thumb!");
      thumb->setAngle(request->getParam("thumb")->value().toInt());
    }

    if (request->hasParam("index")) {
      Serial.println("Request to move index!");
      indx->setAngle(request->getParam("index")->value().toInt());
    }

    if (request->hasParam("middle")) {
      Serial.println("Request to move middle!");
      middle->setAngle(request->getParam("middle")->value().toInt());
    }

    if (request->hasParam("ring")) {
      Serial.println("Request to move ring!");
      ring->setAngle(request->getParam("ring")->value().toInt());
    }

    if (request->hasParam("pinky")) {
      Serial.println("Request to move pinky!");
      pinky->setAngle(request->getParam("pinky")->value().toInt());
    }

    AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", "Ok");
    response->addHeader("Access-Control-Allow-Origin", "*"); // Allow requests from any origin
    request->send(response);
  });
  
  // Start server
  server.begin();
}

void loop() {

}

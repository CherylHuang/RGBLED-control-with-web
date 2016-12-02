#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Wire.h>

#define SSID "Cheryl"                                   
#define PASS "CherylH825"

ESP8266WebServer server(80);

const int led = 13;
char led_status[25];
String webSite;
byte x = 0;


//#define LEDR 5
//#define LEDG 4
//#define LEDB 14

//void turnoff(){
//  digitalWrite(LEDR, LOW);
//  digitalWrite(LEDG, LOW);
//  digitalWrite(LEDB, LOW);
//}

void buildWeb(){
  webSite += "<html>";
  webSite+="<head>\n";
  webSite+="<meta charset='UTF-8'/>\n";
  webSite+="<title>Form Control RGB_LED</title>\n";
  webSite+="<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js\"></script>";
  webSite+="<script>";
  webSite+="$(document).ready(function(){";
  webSite+="$(\"[type = range]\").change(function(){";
  webSite+="var redval = $(\"#red\").val();";
  webSite+="$(\"#red-text\").text(redval);";
   webSite+="var greenval = $(\"#green\").val();";
  webSite+="$(\"#green-text\").text(greenval);";
   webSite+="var blueval = $(\"#blue\").val();";
  webSite+="$(\"#blue-text\").text(blueval);";
  webSite+="});";
  webSite+="});";
  webSite+="</script>";
  webSite+="</head>\n";
  webSite += "<body>";
  webSite += "<h1>RGB LED Control form</h1>";
  webSite += "<form action=\"/form1\">";
  webSite += "<p>Red Color : <span id = \"red-text\">0</span></p>";
  webSite += "<input type=\"range\" id=\"red\" name=\"R-led\" min=\"0\" max=\"255\" value=\"0\">";
webSite += "<p>Green Color : <span id = \"green-text\">0</span></p>";
  webSite += "<input type=\"range\" id=\"green\" name=\"G-led\" min=\"0\" max=\"255\" value=\"0\">";
  webSite += "<p>Blue Color : <span id = \"blue-text\">0</span></p>";
  webSite += "<input type=\"range\" id=\"blue\" name=\"B-led\" min=\"0\" max=\"255\" value=\"0\" ><br><br>";
  webSite += "<input type=\"submit\" value=\"submit\"></form>";
  webSite += "</body></html>";
}

void handleRoot(){
  server.send(200,"text/html",webSite);
}

void handleLEDStatus() {
  Wire.beginTransmission(8); // transmit to device #8
  int red_color = server.arg("R-led").toInt();
  int green_color = server.arg("G-led").toInt();
  int blue_color = server.arg("B-led").toInt();
  
  Wire.write(red_color);       
  Wire.write(green_color);              // sends one byte
  Wire.write(blue_color);
  Wire.endTransmission();    // stop transmitting
  server.send(200,"text/html",webSite);
}

//void ColorPicker(){
//  int red_color = server.arg("R-led").toInt();
//  int green_color = server.arg("G-led").toInt();
//  int blue_color = server.arg("B-led").toInt();
//  
//  analogWrite(LEDR,red_color);
//  analogWrite(LEDG,green_color);
//  analogWrite(LEDB,blue_color);
//
//  server.send(200,"text/html",webSite);
//}

void handleNotFound(){
  server.send(404,"text/html","404 Error!");
}

void setup() {
  buildWeb();

  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.begin(SSID, PASS);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(SSID);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());



  server.on("/", handleRoot);
  server.on("/form1",handleLEDStatus);

//  server.on("/inline", [](){
//    server.send(200, "text/plain", "this works as well");
//  });

  server.onNotFound(handleNotFound);
Wire.begin(4,5);

  server.begin();
  Serial.println("HTTP server started");
}
void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();  
}


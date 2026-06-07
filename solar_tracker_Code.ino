#include <ESP32Servo.h>
#include <WiFi.h>

// wifi setup
const char* ssid     = "UW MPSK";
const char* password = "rRLzuXpVcwpPzKpr";

WiFiServer server(80);

String header;

String valueString = String(160);
String indexString = "";

String xposValueString = String(160);
String xnegValueString = String(160);
String yposValueString = String(160);
String ynegValueString = String(160);

int pos1 = 0;
int pos2 = 0;

unsigned long currentTime  = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;

static const float epsilon = 0.000001;

// system parameters; add a way to change them from a server
static const float pi = 3.14159;

static const float servoRange = 120;

static const int xServoPin = 14;
static const int yServoPin = 13;

static const int xposPin = 32;
static const int xnegPin = 34;
static const int yposPin = 33;
static const int ynegPin = 35;

float xposRb = 330.0;
float xnegRb = 330.0;
float yposRb = 330.0;
float ynegRb = 330.0;

float xposM = 0.85;
float xnegM = 0.85;
float yposM = 0.85;
float ynegM = 0.85;

float xposR10 = 160.0;
float xnegR10 = 160.0;
float yposR10 = 160.0;
float ynegR10 = 160.0;

// motor setup
Servo xservo;
Servo yservo;

// variables to be calculated in the main loop
float xposV = 0.0;
float xnegV = 0.0;
float yposV = 0.0;
float ynegV = 0.0;

float xposR = 0.0;
float xnegR = 0.0;
float yposR = 0.0;
float ynegR = 0.0;

float xposI = 0.0;
float xnegI = 0.0;
float yposI = 0.0;
float ynegI = 0.0;

float xtheta = 0.0;
float ytheta = 0.0;

// servo position
int azimuth = 60;
int elevation = 60;

void setup() {
  Serial.begin(115200);

  xservo.attach(xServoPin);
  yservo.attach(yServoPin);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();   // Listen for incoming clients
  
  if (client){
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // Display the web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS style
            client.println("<style>body { text-align: center; font-family: \"Trebuchet MS\", Arial; margin-left:auto; margin-right:auto;}");
            client.println(".slider { width: 300px; }</style>");
            client.println("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>");

            // Web page
            client.println("</head><body><h1>ESP32 Solar Tracker</h1>");

            // X+
            client.println("<p>X+ R10: <span id=\"xpos\"></span></p>");
            client.println("<input type=\"range\" min=\"80\" max=\"240\" class=\"slider\" id=\"xposSlider\" onchange=\"reportxpos(this.value)\" value=\""+xposValueString+"\"/>");
            client.println("<script>var sliderXP = document.getElementById(\"xposSlider\");");
            client.println("var xPos = document.getElementById(\"xpos\"); xPos.innerHTML = sliderXP.value;");
            client.println("sliderXP.oninput = function() { sliderXP.value = this.value; xPos.innerHTML = this.value; }");

            client.println("$.ajaxSetup({timeout:1000}); function reportxpos(pos) { ");
            client.println("$.get(\"/?value=\" + pos + \"&x+\"); {Connection: close};}</script>");

            // X-
            client.println("<p>X- R10: <span id=\"xneg\"></span></p>");
            client.println("<input type=\"range\" min=\"80\" max=\"240\" class=\"slider\" id=\"xnegSlider\" onchange=\"reportxneg(this.value)\" value=\""+xnegValueString+"\"/>");
            client.println("<script>var sliderXN = document.getElementById(\"xnegSlider\");");
            client.println("var xNeg = document.getElementById(\"xneg\"); xNeg.innerHTML = sliderXN.value;");
            client.println("sliderXN.oninput = function() { sliderXN.value = this.value; xNeg.innerHTML = this.value; }");

            client.println("$.ajaxSetup({timeout:1000}); function reportxneg(pos) { ");
            client.println("$.get(\"/?value=\" + pos + \"&x-\"); {Connection: close};}</script>");

            // Y+
            client.println("<p>Y+ R10: <span id=\"ypos\"></span></p>");
            client.println("<input type=\"range\" min=\"80\" max=\"240\" class=\"slider\" id=\"yposSlider\" onchange=\"reportypos(this.value)\" value=\""+yposValueString+"\"/>");
            client.println("<script>var sliderYP = document.getElementById(\"yposSlider\");");
            client.println("var yPos = document.getElementById(\"ypos\"); yPos.innerHTML = sliderYP.value;");
            client.println("sliderYP.oninput = function() { sliderYP.value = this.value; yPos.innerHTML = this.value; }");

            client.println("$.ajaxSetup({timeout:1000}); function reportypos(pos) { ");
            client.println("$.get(\"/?value=\" + pos + \"&y+\"); {Connection: close};}</script>");

            // Y-
            client.println("<p>Y- R10: <span id=\"yneg\"></span></p>");
            client.println("<input type=\"range\" min=\"80\" max=\"240\" class=\"slider\" id=\"ynegSlider\" onchange=\"reportyneg(this.value)\" value=\""+ynegValueString+"\"/>");
            client.println("<script>var sliderYN = document.getElementById(\"ynegSlider\");");
            client.println("var yNeg = document.getElementById(\"yneg\"); yNeg.innerHTML = sliderYN.value;");
            client.println("sliderYN.oninput = function() { sliderYN.value = this.value; yNeg.innerHTML = this.value; }");

            client.println("$.ajaxSetup({timeout:1000}); function reportyneg(pos) { ");
            client.println("$.get(\"/?value=\" + pos + \"&y-\"); {Connection: close};}</script>");
            
            //GET /?value=180& HTTP/1.1
            if (header.indexOf("GET /?value=")>=0) {
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');
              valueString = header.substring(pos1+1,pos2);
              indexString = header.substring(pos2+1, pos2+3);

              if (indexString == "x+") {
                xposValueString = valueString;
                xposR10 = xposValueString.toFloat();
              } else if (indexString == "x-"){
                xnegValueString = valueString;
                xnegR10 = xnegValueString.toFloat();
              } else if (indexString == "y+"){
                yposValueString = valueString;
                yposR10 = yposValueString.toFloat();
              } else if (indexString == "y-"){
                ynegValueString = valueString;
                ynegR10 = ynegValueString.toFloat();
              } else {Serial.println("Invalid input");}

              Serial.println("X+ R10: " + String(xposR10));
              Serial.println("X- R10: " + String(xnegR10));
              Serial.println("Y+ R10: " + String(yposR10));
              Serial.println("Y- R10: " + String(ynegR10));
            }
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }

  xposV = analogRead(xposPin) / 4095.0;
  xnegV = analogRead(xnegPin) / 4095.0;
  yposV = analogRead(yposPin) / 4095.0;
  ynegV = analogRead(ynegPin) / 4095.0;

  xposR = xposRb * ((1/(xposV + epsilon)) - 1);
  xnegR = xnegRb * ((1/(xnegV + epsilon)) - 1);
  yposR = yposRb * ((1/(yposV + epsilon)) - 1);
  ynegR = ynegRb * ((1/(ynegV + epsilon)) - 1);

  xposI = pow((xposR10 * 1000.0)/(xposR + epsilon), 1.0/xposM);
  xnegI = pow((xnegR10 * 1000.0)/(xnegR + epsilon), 1.0/xnegM);
  yposI = pow((yposR10 * 1000.0)/(yposR + epsilon), 1.0/yposM);
  ynegI = pow((ynegR10 * 1000.0)/(ynegR + epsilon), 1.0/ynegM);
  
  xtheta = atan((xposI + epsilon)/(xnegI + epsilon))*180.0/pi - 45.0;
  ytheta = atan((yposI + epsilon)/(ynegI + epsilon))*180.0/pi - 45.0;
  
  azimuth += 0.05 * xtheta;
  elevation += 0.05 * ytheta;

  if (azimuth < 0) {
    azimuth = 0;
  } else if (azimuth > servoRange) {
    azimuth = servoRange;
  }

  if (elevation < 0) {
    elevation = 0;
  } else if (elevation > servoRange) {
    elevation = servoRange;
  }

  Serial.println("------------------------------------");
  Serial.println(WiFi.localIP());
  Serial.println("");
  Serial.println("xtheta: "+String(xtheta));
  Serial.println("ytheta: "+String(ytheta));
  Serial.println("");
  Serial.println("azimuth: "+String(azimuth));
  Serial.println("elevation: "+String(elevation));

  xservo.write(int(azimuth));
  yservo.write(int(elevation));
  
  delay(200);  
}

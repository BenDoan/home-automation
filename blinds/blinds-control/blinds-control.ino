// Device: Wemos D1 mini w/ relay shield
// Board in arduino IDE: WeMos D1 R1

#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

const int relayPin = 5;

char ssid[] = "Netgear35";
char password[] = "freebird";

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(relayPin, OUTPUT);
  
  WiFi.begin(ssid,password);
  Serial.begin(115200);
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.print(WiFi.localIP());

  server.on("/", [](){server.send(200,"text/plain","Hello Relay! Navigate to /pulse-relay to turn the Relay On/Off.");});
  server.on("/pulse-relay", pulseRelay);
  server.begin();
}

void loop(void){
  server.handleClient();
}

void pulseRelay()
{
  server.send(200,"text/plain", "Pulsing...");
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(relayPin, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(relayPin, LOW);
}

void toggleRelay()
{
  uint8_t new_state = !digitalRead(relayPin);
  String new_state_str = (new_state ? "ON" : "OFF");
  digitalWrite(relayPin, new_state);
  server.send(200, "text/plain", "Relay is now " + new_state_str + "!");
}

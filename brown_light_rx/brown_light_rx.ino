#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <String>

int lightsOnStatus = 0;    // status for whether the lights are on
int lightsOnStatusOld = 0; // old status

int redLEDpin = 14;
int greenLEDpin = 13;

WiFiUDP Udp;
unsigned int localUdpPort = 4210;  // local port to listen on
unsigned int remoteUdpPort = 4210; // remote to port to listen on
char incomingPacket[255];          // buffer for incoming packets

void setup()
{
  // Setup LEDS
  pinMode(redLEDpin, OUTPUT);
  pinMode(greenLEDpin, OUTPUT);

  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // Setup WiFi
  WiFi.begin("Donnelly-Private", "ColdTea!");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
}

void loop()
{

  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }
    Serial.println("Test");
    Serial.printf("UDP packet contents: %c\n", incomingPacket[0]);
    lightsOnStatus = incomingPacket[0];
    Serial.println(lightsOnStatus);
    if (lightsOnStatus)
    {
      Serial.println("Red light on");
      digitalWrite(greenLEDpin, LOW);
      digitalWrite(redLEDpin, HIGH);
    }
    else
    {
      Serial.println("Green light on");
      digitalWrite(redLEDpin, LOW);
      digitalWrite(greenLEDpin, HIGH);
    }
  }

  delay(500);
}

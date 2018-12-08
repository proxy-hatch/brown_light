#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

int photocellPin = 0;		   // the cell and 10K pulldown are connected to a0
int photocellReading;		   // the analog reading from the sensor divider
int brightnessThreshold = 500; // brightness level above which to consider the lights on
int lightsOnStatus = 0;		   // status for whether the lights are on

WiFiUDP Udp;
unsigned int localUdpPort = 4210;  // local port to listen on
unsigned int remoteUdpPort = 4210; // remote to port to listen on
auto remoteIP = IPAddress(192, 168, 1, 94);
char incomingPacket[255]; // buffer for incoming packets

void setup()
{

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

	// Setup UDP
	Udp.begin(localUdpPort);
	Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
}

void loop()
{

	// read photocell
	photocellReading = analogRead(A0);
	Serial.print("Analog reading = ");
	Serial.println(photocellReading); // the raw analog reading

	// set lights on status
	if (photocellReading > brightnessThreshold)
	{
		Serial.println("Lights are on");
		lightsOnStatus = 1;
	}
	else
	{
		Serial.println("Lights are off");
		lightsOnStatus = 0;
	}

	Udp.beginPacket(remoteIP, remoteUdpPort);
	Udp.write(lightsOnStatus);
	Udp.endPacket();

	delay(2000);
}

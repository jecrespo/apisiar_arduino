//Configuración de red para placa ethernet shield 2 e IP fija

#include <Ethernet2.h>
#include <SPI.h>

//Network Config
byte mac[] = {
  0x90, 0xA2, 0xDA, 0x10, 0xB3, 0xBD
};
byte ip[] = {
  192, 168, 1, 10
};
byte DNS[] = {
  8, 8, 8, 8
};
byte gateway[] = {
  192, 168, 1, 1
};
byte subnet[] = {
  255, 255, 255, 0
};

char api[] = "apisiar.larioja.org";

EthernetClient client;
String webString = "";

void setup()
{
  String cadenaLeida = "";
  Ethernet.begin(mac, ip, DNS, gateway, subnet);
  Serial.begin(9600);

  Serial.println("inicializando red...");

  delay(1000);

  if (client.connect(api, 80)) {
    Serial.println("connected");
    client.println("GET /ultima-hora/id/MI_ID HTTP/1.1");
    client.println("Host: apisiar.larioja.org");
    client.println();
  }
  else {
    Serial.println("connection failed");
  }
}

void loop()
{
  if (client.available()) {
    char c = client.read();
    webString += c;
    Serial.print(c);
  }

  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    for (;;)
      ;
  }
}


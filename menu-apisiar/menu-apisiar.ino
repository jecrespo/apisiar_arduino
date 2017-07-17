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

String ID = "";
String webString = "";	//ID necesario para acceso a datos

void setup()
{

  Ethernet.begin(mac, ip, DNS, gateway, subnet);
  Serial.begin(9600);
  Serial.println("Ejemplo de acceso desde Arduino a apisiar");
  Serial.println("inicializando red...");

  delay(1000);

  Serial.println("Introduce ID");
  while (Serial.available() == 0) {
    //nada
  }
  do {
    char caracter_leido = Serial.read();
    ID += caracter_leido;
    delay(5);
  }  while (Serial.available() > 0);
  Serial.print("ID: ");
  Serial.println(ID);
}

void loop()
{
  muestra_menu();
}

int muestra_menu() {
  String cadenaLeida = "";
  String ruta = "";

  Serial.println("MENU - APISIAR");
  Serial.println("1 - ultima hora");
  Serial.println("2 - estaciones disponibles");
  Serial.println("3 - parametros disponibles");
  Serial.println("4 - obtener datos diarios estacion");
  while (Serial.available() == 0) {
    //nada
  }
  do {
    char caracter_leido = Serial.read();
    cadenaLeida += caracter_leido;
    delay(5);
  }  while (Serial.available() > 0);

  int respuesta = cadenaLeida.toInt();

  if ((respuesta > 0) && (respuesta < 5)) {
    Serial.println("Opcion seleccionada: " + cadenaLeida);
  }
  else {
    Serial.println("Respuesta incorrecta");
    return 0;
  }
  String estacion = "";
  switch (respuesta) {
    case 1:
      ruta = "GET /ultima-hora/id/" + ID + " HTTP/1.0";
      break;
    case 2:
      ruta = "GET /estaciones-disponibles/id/" + ID + " HTTP/1.0";
      break;
    case 3:
      Serial.println("Introduce número de estación");
      while (Serial.available() == 0) {
        //nada
      }
      do {
        char caracter_leido = Serial.read();
        estacion += caracter_leido;
        delay(5);
      }  while (Serial.available() > 0);
      Serial.println("estación seleccionada: " + estacion);
      ruta = "GET /estacion/" + estacion + "/parametros-disponibles/id/" + ID + " HTTP/1.0";
      break;
    case 4:
      Serial.println("Introduce número de estación");
      while (Serial.available() == 0) {
        //nada
      }
      do {
        char caracter_leido = Serial.read();
        estacion += caracter_leido;
        delay(5);
      }  while (Serial.available() > 0);
      Serial.println("estación seleccionada: " + estacion);

      String fecha = "";
      Serial.println("Introduce fecha (formato aaaammdd)");
      while (Serial.available() == 0) {
        //nada
      }
      do {
        char caracter_leido = Serial.read();
        fecha += caracter_leido;
        delay(5);
      }  while (Serial.available() > 0);
      Serial.println("fecha seleccionada: " + fecha);
      ruta = "GET /estacion/" + estacion + "/tipo/diario/fechain/" + fecha + "/fechafin/" + fecha + "/salida/json/niveles/no/id/" + ID + " HTTP/1.0";
      break;
  }

  EthernetClient client;
  if (client.connect(api, 80)) {
    Serial.println("connected");
    client.println(ruta);
	client.println("Host: apisiar.larioja.org");
    client.println();

    while (client.available() == 0) {
        //nada
      }
    do {
      char c = client.read();
      webString += c;
      Serial.print(c);
    } while (client.available() > 0);

    if (!client.connected()) {
      Serial.println();
      Serial.println("disconnecting.");
      client.stop();
    }
    return 1;
  }
  else {
    Serial.println("connection failed");
    return 0;
  }

}

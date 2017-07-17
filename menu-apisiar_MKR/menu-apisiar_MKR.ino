//Configuración de red para placa Arduino MKR1000

#include <SPI.h>
#include <WiFi101.h>

//Network Config
char ssid[] = "SSID"; //  your network SSID (name)
char pass[] = "password";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

char api[] = "apisiar.larioja.org";

String ID = "";
String webString = "";	//ID necesario para acceso a datos

void setup()
{
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Ejemplo de acceso desde Arduino a apisiar");
  Serial.println("inicializando red...");

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to wifi");
  printWifiStatus();

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

  WiFiClient client;
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

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

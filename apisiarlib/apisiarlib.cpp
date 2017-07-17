//
// FILE: apisiar-lib.cpp
// VERSION: 1.0
// PURPOSE: connect API REST apisiar http://apisiar.larioja.org/help
// aprendiendoarduino by jecrespo Jan 2017
//

#include "apisiarlib.h"

void apisiar::set_ID(String ID)
{
	_ID = ID;
}

String apisiar::get_ultimahora()
{	
	EthernetClient client;
	String response = "";
	String ruta = "GET /ultima-hora/id/" + _ID + " HTTP/1.0";
	if (client.connect(_api, 80)) {
		Serial.println("connected");
		client.println(ruta);
		client.println("Host: " + String(_api));
		client.println();

		while (client.available() == 0) {
			//nada
		  }
		do {
		  char c = client.read();
		  response += c;
		  Serial.print(c);
		} while (client.available() > 0);

		if (!client.connected()) {
		  Serial.println();
		  Serial.println("disconnected");
		  client.stop();
		}
		return response;
	}
	  else {
		Serial.println("connection failed");
		return "connection failed";
	  }
}
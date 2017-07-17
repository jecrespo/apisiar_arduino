/*----------------------------------------------------------------------*
 * apisiar library example sketch.                                      *
 * connect API REST apisiar http://apisiar.larioja.org/help             *
 * aprendiendoarduino by jecrespo May 2016                              *
 *                                                                      *
 * This work is licensed under the Creative Commons Attribution-        *
 * ShareAlike 3.0 Unported License. To view a copy of this license,     *
 * visit http://creativecommons.org/licenses/by-sa/3.0/ or send a       *
 * letter to Creative Commons, 171 Second Street, Suite 300,            *
 * San Francisco, California, 94105, USA.                               *
 *----------------------------------------------------------------------*/

#include <Ethernet2.h>
#include <MsTimer2.h>
#include "apisiarlib.h"

apisiar api;
byte mac[] = {0x90, 0xA2, 0xDA, 0x0F, 0x00, 0x00};
byte ip[] = {192, 168, 1, 10};
byte DNS[] = {8, 8, 8, 8};
byte gateway[] = {192, 168, 1, 1};
byte subnet[] = {255, 255, 255, 0};

void setup()
{
  Serial.begin(9600);
  Ethernet.begin(mac, ip, DNS, gateway, subnet);
  api.set_ID("MI_ID");
  delay(500);
  MsTimer2::set(10000, consulta); // 10000ms period
  MsTimer2::start();
  
}

void loop()
{
}

void consulta(){
	Serial.println("Requesting Data...");
	String respuesta = api.get_ultimahora();
	Serial.println(respuesta);
}

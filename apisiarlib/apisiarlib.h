// 
// FILE: apisiar_lib.h
// VERSION: 1.0
// PURPOSE: connect API REST apisiar http://apisiar.larioja.org/help
// aprendiendoarduino by jecrespo Jan 2017
//

#ifndef apisiarlib_h
#define apisiarlib_h

#include <Arduino.h>
#include <Ethernet.h>

#define APISIAR_LIB_VERSION "1.0"

class apisiar
{
	public:
		void set_ID(String ID);
		String get_ultimahora();
		//String get_estaciones();
		//String get_parametros(int estacion);
		//String get_datos_diarios(int estacion, String fecha); //fecha con formato aaaammdd

	private:
		String _ID;
		char _api[] = "apisiar.larioja.org";

};
#endif	//apisiar-lib
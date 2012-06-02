#include "KeyFactory.h"
#include "Linea.h"
#include "FranjaHoraria.h"
#include "Falla.h"
#include "Accidente.h"
#include "Formacion.h"

#include <stdlib.h>
#include <string>
#include <cstring>

unsigned KeyFactory::k = 5;

Key* KeyFactory::getKey(unsigned level) {
    if (k != 5)
        return new IntKey(8);
    else {
        switch (level % k) {
            case LINEA:     return new Linea();
            case FRANJA:    return new FranjaHoraria();
            case FALLA:     return new Falla();
            case ACCIDENTE: return new Accidente();
            case FORMACION: return new Formacion();
            default: return NULL;
        }
    }
}

Key* KeyFactory::getKey(unsigned level, std::string value)
{
   if (k != 5)
        return new IntKey(8, atoi(value.c_str()));
    else {
        switch (level % k) {
            case LINEA:     return new Linea(value);
            case FALLA:     return new Falla(value);
            case ACCIDENTE: return new Accidente(value);
            case FORMACION: return new Formacion(atoi(value.c_str()));
            case FRANJA: {    
				//buffer example => 12:01 - 12:31 20/05/2012, transforma a timestamp del 12:16 20/05/2012
				char buffer[30];
				strcpy(buffer, value.c_str());
				int posBarraCero[7] = {2, 5, 10, 13, 16, 19, 24};

				for (int i = 0; i <7; ++i ) {
					buffer[posBarraCero[i]] = '\0';
				}

				struct tm tm_low;
				struct tm tm_hi;

				tm_low.tm_sec = 0;
				tm_hi.tm_sec = 0;
				tm_low.tm_hour = atoi(buffer + posBarraCero[0] - 2);
				tm_low.tm_min  = atoi(buffer + posBarraCero[1] - 2);
				tm_hi.tm_hour  = atoi(buffer + posBarraCero[2] - 2);
				tm_hi.tm_min   = atoi(buffer + posBarraCero[3] - 2);
				tm_low.tm_mday = atoi(buffer + posBarraCero[4] - 2);
				tm_low.tm_mon  = atoi(buffer + posBarraCero[5] - 2) - 1;
				tm_low.tm_year = atoi(buffer + posBarraCero[6] - 4) - 1900;
				tm_hi.tm_mday = tm_low.tm_mday;
				tm_hi.tm_mon = tm_low.tm_mon;
				tm_hi.tm_year = tm_low.tm_year;

				time_t t_med = mktime(&tm_low) + 15*60;

				if (t_med == mktime(&tm_hi) - 15*60)
				std::cout << "bien" << std::endl;

	            return new FranjaHoraria(t_med);
            }
            default: return NULL;
        }
    }
}

void KeyFactory::setDimensions(unsigned _k) {
    k = _k;
}

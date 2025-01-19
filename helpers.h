#ifndef HELPERS_H
#define HELPERS_H

#include "funciones.h"
#define CO_LIMIT 10.0    // CO límite diario OMS (24 horas)
#define SO2_LIMIT 20.0   // SO2 límite diario OMS (24 horas)
#define NO2_LIMIT 30.0   // NO2 límite diario OMS (24 horas)
#define PM25_LIMIT 40.0  // PM2.5 límite diario OMS (24 horas)



void mostrarContaminante(double contaminante, int *alerta);
double calcularAQI(double PM25, double NO2, double SO2, double CO, double temperatura, double humedad, double velocidad_aire);
void sugerencias(int *alerta, char *nombreArchivo);
void verificarLimites(Dia promedio);
Dia calcularPromedioZonaHistorico(char *nombreArchivo);


#endif // HELPERS_H

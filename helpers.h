#ifndef HELPERS_H
#define HELPERS_H

#include "funciones.h"

#define CO_LIMIT 10.0
#define SO2_LIMIT 20.0
#define NO2_LIMIT 30.0
#define PM25_LIMIT 40.0

void verificarLimites(Dia promedio);
void sugerencias(Dia promedio);
double calcularAQI(double PM25, double NO2, double SO2, double CO, double temperatura, double humedad, double velocidad_aire);
void mostrarContaminante(double contaminante, int *alerta, FILE *reporte);

#endif

//void mostrarContaminante(double contaminante, int *alerta);
//double calcularAQI(double PM25, double NO2, double SO2, double CO, double temperatura, double humedad, double velocidad_aire);
//void sugerencias(int *alerta, char *nombreArchivo);
//void verificarLimites(Dia promedio);
//Dia calcularPromedioZonaHistorico(char *nombreArchivo);


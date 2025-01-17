#ifndef HELPERS_H
#define HELPERS_H

void mostrarContaminante(double contaminante, int *alerta);
double calcularAQI(double PM25, double NO2, double SO2, double CO, double temperatura, double humedad, double velocidad_aire);
void sugerencias(int *alerta, char *nombreArchivo);

#endif // HELPERS_H
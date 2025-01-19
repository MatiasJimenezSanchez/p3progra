#ifndef FUNCIONES_H
#define FUNCIONES_H

#define MAX_DIAS 100

typedef struct Dia {
    int numDia;
    double CO2;
    double SO2;
    double NO2;
    double PM25;
    double temperatura;
    double humedad;
    double velocidad_aire;
    double AQI;
} Dia;

void crearArchivo(char *nombre, int *num_dias);
void leercadena(char *cadena, int longitud);
void addDia(char *nombre, int *num_dias);
void leerDatosZona(char *nombre, int *num_dias, Dia dias[]);
void exportarReporte(char *nombreArchivo, Dia promedio);

#endif // FUNCIONES_H

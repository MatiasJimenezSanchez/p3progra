#include <stdio.h>
#include <string.h>
#include "helpers.h"


// Límites máximos recomendados por la OMS (µg/m³ o mg/m³) - Directrices más estrictas
#define PM25_LIMIT 15.0 // PM2.5 límite diario OMS (24 horas)
#define NO2_LIMIT 25.0  // NO2 límite diario OMS (24 horas)
#define SO2_LIMIT 40.0  // SO2 límite diario OMS (24 horas)
#define CO_LIMIT 4.0    // CO límite diario OMS (24 horas)


void mostrarContaminante(double contaminante, int *alerta)
{
    if (contaminante >= 0 && contaminante <= 50)
    {
        printf("Nivel del Indice de Calidad del Aire: BUENO\n");
    }
    else if (contaminante >= 51 && contaminante <= 100)
    {
        printf("Nivel del Indice de Calidad del Aire: MODERADO\n");
    }
    else if (contaminante >= 101 && contaminante <= 150)
    {
        printf("Nivel del Indice de Calidad del Aire: NOCIVO PARA GRUPOS SENSIBLES\n");
        *alerta = 1;
    }
    else if (contaminante >= 151 && contaminante <= 200)
    {
        printf("Nivel del Indice de Calidad del Aire: NOCIVO\n");
        *alerta = 1;
    }
    else if (contaminante >= 201 && contaminante <= 300)
    {
        printf("Nivel del Indice de Calidad del Aire: MUY NOCIVO\n");
        *alerta = 1;
    }
    else if (contaminante >= 301 && contaminante <= 400)
    {
        printf("Nivel del Indice de Calidad del Aire: PELIGROSO\n");
        *alerta = 1;
    }
    else if (contaminante >= 401 && contaminante <= 500)
    {
        printf("Nivel del Indice de Calidad del Aire: PELIGROSO\n");
        *alerta = 1;
    }
    else
    {
        printf("Nivel del Indice de Calidad del Aire: PELIGROSO\n");
        *alerta = 1;
    }
}

void sugerencias(int *alerta, char *nombreArchivo)
{
    FILE *archivo = fopen("sugerencias.txt", "w");
    if (archivo == NULL)
    {
        printf("Error al crear el archivo de sugerencias\n");
        return;
    }

    if (*alerta)
    {
        fprintf(archivo, "Medidas de mitigación sugeridas para el archivo %s:\n", nombreArchivo);
        fprintf(archivo, "- Reducción del tráfico vehicular\n");
        fprintf(archivo, "- Cierre temporal de industrias\n");
        fprintf(archivo, "- Suspensión de actividades al aire libre\n");
    }
    else
    {
        fprintf(archivo, "Los niveles de contaminación en el archivo %s están dentro de los límites recomendados.\n", nombreArchivo);
    }

    fclose(archivo);
}

double calcularAQI(double PM25, double NO2, double SO2, double CO,double temperatura, double humedad, double velocidad_aire)
{
    double coef_temp = 0.02; // Coeficiente de temperatura
    double coef_hum = 0.01;  // Coeficiente de humedad
    double coef_vel = 0.05;  // Coeficiente de velocidad del aire
    
    // Normalización de contaminantes con respecto a los límites OMS
    double PM25_norm = PM25 / PM25_LIMIT;
    double NO2_norm = NO2 / NO2_LIMIT;
    double SO2_norm = SO2 / SO2_LIMIT;
    double CO_norm = CO / CO_LIMIT;

    // Calcular el AQI ponderando los contaminantes
    double aqi_base = (PM25_norm + NO2_norm + SO2_norm + CO_norm) / 4.0 * 100.0;

    double aqi = aqi_base * (1 + (temperatura * coef_temp) + (humedad * coef_hum) + (velocidad_aire * coef_vel));
    // Limitar el AQI a un máximo de 500 (estándar internacional)
    if (aqi_base > 500)
        aqi_base = 500;

    return aqi_base;
}

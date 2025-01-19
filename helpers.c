#include <stdio.h>
#include "helpers.h"
#include "funciones.h"

double calcularAQI(double PM25, double NO2, double SO2, double CO, double temperatura, double humedad, double velocidad_aire)
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
    if (aqi > 500)
        aqi = 500;

    return aqi;
}

void verificarLimites(Dia promedio) {
    printf("\nEstado de la contaminacion:");
    
    if (promedio.CO2 > CO_LIMIT) {
        printf("\nCO2: %.2f ⚠️ EXCEDE el limite permitido (%.2f)", promedio.CO2, CO_LIMIT);
    } else {
        printf("\nCO2: %.2f ✅ Dentro del limite permitido (%.2f)", promedio.CO2, CO_LIMIT);
    }
    
    if (promedio.SO2 > SO2_LIMIT) {
        printf("\nSO2: %.2f ⚠️ EXCEDE el limite permitido (%.2f)", promedio.SO2, SO2_LIMIT);
    } else {
        printf("\nSO2: %.2f ✅ Dentro del limite permitido (%.2f)", promedio.SO2, SO2_LIMIT);
    }
    
    if (promedio.NO2 > NO2_LIMIT) {
        printf("\nNO2: %.2f ⚠️ EXCEDE el limite permitido (%.2f)", promedio.NO2, NO2_LIMIT);
    } else {
        printf("\nNO2: %.2f ✅ Dentro del limite permitido (%.2f)", promedio.NO2, NO2_LIMIT);
    }
    
    if (promedio.PM25 > PM25_LIMIT) {
        printf("\nPM2.5: %.2f ⚠️ EXCEDE el limite permitido (%.2f)", promedio.PM25, PM25_LIMIT);
    } else {
        printf("\nPM2.5: %.2f ✅ Dentro del limite permitido (%.2f)", promedio.PM25, PM25_LIMIT);
    }
}

void sugerencias(Dia promedio)
{
    if (promedio.CO2 > CO_LIMIT || promedio.SO2 > SO2_LIMIT || promedio.NO2 > NO2_LIMIT || promedio.PM25 > PM25_LIMIT)
    {
        printf("Se recomienda reducir el trafico vehicular, cerrar temporalmente industrias y suspender actividades al aire libre.\n");
    }
}
#include <stdio.h>
#include <string.h>
#include "helpers.h"
#include "funciones.h"

double CO2[MAX_DIAS];
double SO2[MAX_DIAS];
double NO2[MAX_DIAS];
double PM25[MAX_DIAS];
double temperatura[MAX_DIAS];
double humedad[MAX_DIAS];
double velocidad_aire[MAX_DIAS];

void crearArchivo(char *nombre, int *num_dias)
{
    *num_dias = 0; // Reiniciar num_dias a 0
    FILE *archivo;
    strcat(nombre, ".txt");
    archivo = fopen(nombre, "w");
    if (archivo == NULL)
    {
        printf("Error al crear el archivo %s\n", nombre);
        return;
    }
    fprintf(archivo, "%d\n", *num_dias); // Escribir num_dias en el archivo
    fclose(archivo);

    // Registrar zona en indice
    FILE *indice = fopen("zonas_indice.txt", "a");
    if (indice == NULL)
    {
        printf("Error al abrir el archivo indice.\n");
        return;
    }
    fprintf(indice, "%s\n", nombre);
    fclose(indice);
}

void leercadena(char *cadena, int longitud)
{
    fflush(stdin);
    fgets(cadena, longitud, stdin);
    int len = strlen(cadena) - 1;
    cadena[len] = '\0';
}

Dia promedioPonderadoContaminacionZona(Dia dias[], int num_dias)
{
    Dia res = {0};
    double totalPeso = 0.0;

    if (num_dias <= 0) {
        return res;
    }

    if (num_dias > 30) {
        num_dias = 30;
    }

    for (int i = 0; i < num_dias; i++)
    {
        double peso = (double)(num_dias - i) / num_dias; // Peso mayor para dias recientes
        totalPeso += peso;
        res.CO2 += dias[i].CO2 * peso;
        res.SO2 += dias[i].SO2 * peso;
        res.NO2 += dias[i].NO2 * peso;
        res.PM25 += dias[i].PM25 * peso;
        res.temperatura += dias[i].temperatura * peso;
        res.humedad += dias[i].humedad * peso;
        res.velocidad_aire += dias[i].velocidad_aire * peso;
    }

    res.CO2 /= totalPeso;
    res.SO2 /= totalPeso;
    res.NO2 /= totalPeso;
    res.PM25 /= totalPeso;
    res.temperatura /= totalPeso;
    res.humedad /= totalPeso;
    res.velocidad_aire /= totalPeso;

    res.AQI = calcularAQI(res.PM25, res.NO2, res.SO2, res.CO2, res.temperatura, res.humedad, res.velocidad_aire);

    return res;
}

void addDia(char *nombre, int *num_dias, Dia nuevoDia)
{
    Dia dia = nuevoDia;

    // Solicitar datos del nuevo dia
    printf("Ingrese el nivel de CO2: ");
    scanf("%lf", &dia.CO2);

    printf("Ingrese el nivel de SO2: ");
    scanf("%lf", &dia.SO2);

    printf("Ingrese el nivel de NO2: ");
    scanf("%lf", &dia.NO2);

    printf("Ingrese el nivel de PM25: ");
    scanf("%lf", &dia.PM25);

    printf("Ingrese la temperatura: ");
    scanf("%lf", &dia.temperatura);

    printf("Ingrese la humedad: ");
    scanf("%lf", &dia.humedad);

    printf("Ingrese la velocidad del aire: ");
    scanf("%lf", &dia.velocidad_aire);

    FILE *archivo;
    strcat(nombre, ".txt");
    archivo = fopen(nombre, "r+");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo\n");
        return;
    }
    fscanf(archivo, "%d", num_dias); // Leer num_dias del archivo
    *num_dias = *num_dias + 1;
    fseek(archivo, 0, SEEK_SET);
    fprintf(archivo, "%d\n", *num_dias); // Actualizar num_dias en el archivo
    fseek(archivo, 0, SEEK_END);

    dia.numDia = *num_dias;
    dia.AQI = calcularAQI(dia.PM25, dia.NO2, dia.SO2, dia.CO2, dia.temperatura, dia.humedad, dia.velocidad_aire);
    fprintf(archivo, "%d %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf\n", dia.numDia, dia.CO2, dia.SO2, dia.NO2, dia.PM25, dia.temperatura, dia.humedad, dia.velocidad_aire);
    fclose(archivo);
}

void leerDatosZona(char *nombre, int *num_dias, Dia dias[])
{
    FILE *archivo;
    strcat(nombre, ".txt");
    archivo = fopen(nombre, "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo\n");
        return;
    }

    fscanf(archivo, "%d", num_dias); // Leer num_dias del archivo

    for (int i = 0; i < *num_dias; i++)
    {
        fscanf(archivo, "%d %lf %lf %lf %lf %lf %lf %lf",
               &dias[i].numDia, &dias[i].CO2, &dias[i].SO2, &dias[i].NO2,
               &dias[i].PM25, &dias[i].temperatura, &dias[i].humedad, &dias[i].velocidad_aire);
        dias[i].AQI = calcularAQI(dias[i].PM25, dias[i].NO2, dias[i].SO2, dias[i].CO2, dias[i].temperatura, dias[i].humedad, dias[i].velocidad_aire);
    }

    fclose(archivo);

    // Imprimir datos en consola
    printf("\nDatos de la zona '%s':\n", nombre);
    for (int i = 0; i < *num_dias; i++)
    {
        printf("Dia %d: CO2: %.2f ppm, SO2: %.2f ppm, NO2: %.2f ppm, PM2.5: %.2f µg/m³, Temperatura: %.2f °C, Humedad: %.2f %%, Velocidad del aire: %.2f m/s, AQI: %.2f\n",
               dias[i].numDia, dias[i].CO2, dias[i].SO2, dias[i].NO2, dias[i].PM25, dias[i].temperatura, dias[i].humedad, dias[i].velocidad_aire, dias[i].AQI);
    }
}

void exportarReporte(char *nombreArchivo, Dia promedio)
{
    char reporteNombre[100];
    snprintf(reporteNombre, sizeof(reporteNombre), "%s_reporte.txt", nombreArchivo);

    FILE *reporte = fopen(reporteNombre, "w");
    if (reporte == NULL) {
        printf("Error al crear el archivo de reporte para %s.\n", nombreArchivo);
        return;
    }

    fprintf(reporte, "Reporte de Contaminacion - Zona %s\n\n", nombreArchivo);
    fprintf(reporte, "Promedios de los ultimos 30 dias:\n");
    fprintf(reporte, "CO2: %.2f ppm\nSO2: %.2f ppm\nNO2: %.2f ppm\nPM2.5: %.2f µg/m³\nAQI: %.2f\n\n",
            promedio.CO2, promedio.SO2, promedio.NO2, promedio.PM25, promedio.AQI);

    fprintf(reporte, "Recomendaciones:\n");
    if (promedio.CO2 > CO_LIMIT) fprintf(reporte, "- Reducir el trafico vehicular.\n");
    if (promedio.SO2 > SO2_LIMIT) fprintf(reporte, "- Cerrar temporalmente industrias.\n");
    if (promedio.NO2 > NO2_LIMIT) fprintf(reporte, "- Fomentar el uso de transporte publico.\n");
    if (promedio.PM25 > PM25_LIMIT) fprintf(reporte, "- Suspender actividades al aire libre.\n");
    if (promedio.CO2 <= CO_LIMIT && promedio.SO2 <= SO2_LIMIT &&  
        promedio.NO2 <= NO2_LIMIT && promedio.PM25 <= PM25_LIMIT) {
        fprintf(reporte, "- Los niveles estan dentro de los limites recomendados.\n");
    }

    fclose(reporte);
}
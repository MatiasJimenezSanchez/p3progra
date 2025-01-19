
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


void crearArchivo(char *nombre, int *num_dias) {
    *num_dias = 0; // Reiniciar num_dias a 0
    FILE *archivo;
    strcat(nombre, ".txt");
    archivo = fopen(nombre, "w");
    if (archivo == NULL) {
        printf("Error al crear el archivo %s\n", nombre);
        return;
    }
    fprintf(archivo, "%d\n", *num_dias); // Escribir num_dias en el archivo
    fclose(archivo);

    // Registrar zona en índice
    FILE *indice = fopen("zonas_indice.txt", "a");
    if (indice == NULL) {
        printf("Error al abrir el archivo índice.\n");
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

void addDia(char *nombre, int *num_dias)
{
    struct Dia dia;
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
    printf("Ingrese el nivel de CO: ");
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
}

Dia calcularPromedioZonaHistorico(char *nombreArchivo) {
    Dia promedio = {0};
    FILE *archivo;

    archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo '%s'. Verifique que el archivo exista y tenga el nombre correcto.\n", nombreArchivo);
        return promedio;
    }

    int num_dias;
    fscanf(archivo, "%d", &num_dias);

    Dia dia;
    for (int i = 0; i < num_dias; i++) {
        fscanf(archivo, "%d %lf %lf %lf %lf %lf %lf %lf",
               &dia.numDia, &dia.CO2, &dia.SO2, &dia.NO2,
               &dia.PM25, &dia.temperatura, &dia.humedad, &dia.velocidad_aire);
        dia.AQI = calcularAQI(dia.PM25, dia.NO2, dia.SO2, dia.CO2,
                              dia.temperatura, dia.humedad, dia.velocidad_aire);

        // Sumar valores para el promedio
        promedio.CO2 += dia.CO2;
        promedio.SO2 += dia.SO2;
        promedio.NO2 += dia.NO2;
        promedio.PM25 += dia.PM25;
        promedio.AQI += dia.AQI;
    }

    if (num_dias > 0) {
        promedio.CO2 /= num_dias;
        promedio.SO2 /= num_dias;
        promedio.NO2 /= num_dias;
        promedio.PM25 /= num_dias;
        promedio.AQI /= num_dias;
    }

    fclose(archivo);
    return promedio;
}

void exportarReporte(char *nombreArchivo, Dia promedio) {
    FILE *reporte;
    char reporteNombre[100];
    snprintf(reporteNombre, sizeof(reporteNombre), "%s_reporte.txt", nombreArchivo);

    reporte = fopen(reporteNombre, "w");
    if (reporte == NULL) {
        printf("Error al crear el archivo de reporte para %s.\n", nombreArchivo);
        return;
    }

    fprintf(reporte, "Reporte de Contaminación - Zona %s\n\n", nombreArchivo);
    fprintf(reporte, "Promedios de los últimos 30 días:\n");
    fprintf(reporte, "CO2: %.2f ppm\nSO2: %.2f ppm\nNO2: %.2f ppm\nPM2.5: %.2f µg/m³\nAQI: %.2f\n\n",
            promedio.CO2, promedio.SO2, promedio.NO2, promedio.PM25, promedio.AQI);

    fprintf(reporte, "Recomendaciones:\n");
    if (promedio.CO2 > CO_LIMIT) fprintf(reporte, "- Reducir el tráfico vehicular.\n");
    if (promedio.SO2 > SO2_LIMIT) fprintf(reporte, "- Cerrar temporalmente industrias.\n");
    if (promedio.NO2 > NO2_LIMIT) fprintf(reporte, "- Fomentar el uso de transporte público.\n");
    if (promedio.PM25 > PM25_LIMIT) fprintf(reporte, "- Suspender actividades al aire libre.\n");
    if (promedio.CO2 <= CO_LIMIT && promedio.SO2 <= SO2_LIMIT &&  
        promedio.NO2 <= NO2_LIMIT && promedio.PM25 <= PM25_LIMIT) {
        fprintf(reporte, "- Los niveles están dentro de los límites recomendados.\n");
    }

    fclose(reporte);
    printf("Reporte generado: %s\n", reporteNombre);
}
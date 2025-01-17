#include <stdio.h>
#include "funciones.h"
#include <string.h>
#include "helpers.h"

#define MAX_DIAS 100

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
        printf("Error al crear el archivo\n");
        return;
    }
    fprintf(archivo, "%d\n", *num_dias); // Escribir num_dias en el archivo
    fclose(archivo);
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

    dia.AQI = calcularAQI(dia.PM25, dia.NO2, dia.SO2, dia.CO2, dia.temperatura, dia.humedad, dia.velocidad_aire);

    fprintf(archivo, "%d %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf\n", dia.numDia, dia.CO2, dia.SO2, dia.NO2, dia.PM25, dia.temperatura, dia.humedad, dia.velocidad_aire);
    fclose(archivo);
}

/*
void leerDatosZona(char *nombre)
{
    FILE *archivo;
    strcat(nombre, ".txt");
    archivo = fopen(nombre, "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo\n");
        return;
    }

    num_dias = 0;
    while (fscanf(archivo, "%lf %lf %lf %lf %lf %lf %lf",
                  &CO2[num_dias], &SO2[num_dias], &NO2[num_dias], &PM25[num_dias],
                  &temperatura[num_dias], &humedad[num_dias], &velocidad_aire[num_dias]) != EOF)
    {
        num_dias++;
        if (num_dias >= MAX_DIAS)
        {
            break;
        }
    }

    fclose(archivo);
}

void agregarFechasHistoricas(char *nombre)
{
    FILE *archivo;
    strcat(nombre, "_historico.txt");
    archivo = fopen(nombre, "w");
    if (archivo == NULL)
    {
        printf("Error al crear el archivo historico\n");
        return;
    }

    for (int i = num_dias - 5; i < num_dias; i++)
    {
        if (i >= 0)
        {
            fprintf(archivo, "%d %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf\n",
                    i + 1, CO2[i], SO2[i], NO2[i], PM25[i], temperatura[i], humedad[i], velocidad_aire[i]);
        }
    }

    fclose(archivo);
}
*/
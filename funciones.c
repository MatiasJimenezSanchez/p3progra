#include <stdio.h>
#include <string.h>
#include "funciones.h"
#include "helpers.h"

void crearArchivo(char* nombre)
{
    FILE *archivo;
    strcat(nombre, ".dat");
    archivo = fopen(nombre, "w");
    if (archivo == NULL)
    {
        printf("Error al crear el archivo\n");
    }
    else
    {
        printf("Archivo creado con exito\n");
    }
    fclose(archivo);
}

void addDia(char* nombre)
{
    struct Dia dia;
    FILE *archivo;
    strcat(nombre, ".dat");
    archivo = fopen(nombre, "a");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo\n");
        return;
    }
    else
    {
        dia.numDia = encontrarUltimoDia(nombre) + 1;

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

        dia.AQI = calcularAQI(dia.NO2, dia.CO2, dia.PM25, dia.SO2, dia.temperatura, dia.humedad, dia.velocidad_aire);

        fwrite(&dia, sizeof(struct Dia), 1, archivo);
        fclose(archivo);
    }
}

void leerDatos(char* nombre)
{
    struct Dia dia;
    FILE *archivo;
    strcat(nombre, ".dat");
    archivo = fopen(nombre, "rb");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo\n");
        return;
    }
    else
    {
        while (fread(&dia, sizeof(struct Dia), 1, archivo))
        {
            printf("Dia %d\n", dia.numDia);
            printf("CO2: %lf\n", dia.CO2);
            printf("SO2: %lf\n", dia.SO2);
            printf("NO2: %lf\n", dia.NO2);
            printf("PM25: %lf\n", dia.PM25);
            printf("Temperatura: %lf\n", dia.temperatura);
            printf("Humedad: %lf\n", dia.humedad);
            printf("Velocidad del aire: %lf\n", dia.velocidad_aire);
            printf("AQI: %lf\n", dia.AQI);
            mostrarContaminante(dia.AQI);
            printf("\n");
        }
        fclose(archivo);
    }
}

void mostrarContaminante(double contaminante)
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
    }
    else if (contaminante >= 151 && contaminante <= 200)
    {
        printf("Nivel del Indice de Calidad del Aire: NOCIVO\n");
    }
    else if (contaminante >= 201 && contaminante <= 300)
    {
        printf("Nivel del Indice de Calidad del Aire: MUY NOCIVO\n");
    }
    else if (contaminante >= 301 && contaminante <= 400)
    {
        printf("Nivel del Indice de Calidad del Aire: PELIGROSO\n");
    }
    else if (contaminante >= 401 && contaminante <= 500)
    {
        printf("Nivel del Indice de Calidad del Aire: PELIGROSO\n");
    }
    else
    {
        printf("Nivel del Indice de Calidad del Aire: PELIGROSO\n");
    }
}

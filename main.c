#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include "helpers.h" // Incluir helpers.h

struct Dia dias[MAX_DIAS]; // Define un tamaño máximo para el array

int main()
{
    int opcion;
    int num_dias = 0;
    do
    {
        printf("Seleccione una opcion: \n");
        printf("1. Crear archivo\n");
        printf("2. Ingresar datos de la zona\n");
        printf("3. Leer datos de la zona\n");
        printf("4. Encontrar zona por dia\n");
        printf("5. Leer Datos historicos\n");
        printf("6. Salir\n");
        scanf("%d", &opcion);

        char nombreArchivo[100];

        switch (opcion)
        {
        case 1:
            printf("Ingrese el nombre del archivo a crear: ");
            leercadena(nombreArchivo, 100);
            crearArchivo(nombreArchivo, &num_dias);
            break;
        case 2:
            printf("Ingrese el nombre del archivo: ");
            leercadena(nombreArchivo, 100);
            addDia(nombreArchivo, &num_dias);
            break;
        case 3:
            printf("Ingrese el nombre del archivo: ");
            leercadena(nombreArchivo, 100);
            leerDatosZona(nombreArchivo, &num_dias, dias);
            printf("\n");
            for (int i = 0; i < num_dias; i++)
            {
                printf("Dia %d:\nCO2 = %.2lf\nSO2 = %.2lf\nNO2 = %.2lf\nPM25 = %.2lf\nTemp = %.2lf\nHumedad = %.2lf\nVelocidad Aire = %.2lf\nAQI = %.2lf\n",
                       dias[i].numDia, dias[i].CO2, dias[i].SO2, dias[i].NO2, dias[i].PM25, dias[i].temperatura, dias[i].humedad, dias[i].velocidad_aire, dias[i].AQI);
                mostrarContaminante(dias[i].AQI);
                printf("\n");
            }

            break;
        case 4:
            printf("Ingrese el nombre del archivo: ");
            // leercadena(nombreArchivo, 100);
            // leerDatosZona(nombreArchivo);
            // agregarFechasHistoricas(nombreArchivo);
            break;
        case 5:
            printf("Saliendo del programa\n");
            return 0;
            break;
        default:
            printf("Opcion no valida\n");
            break;
        }
    } while (opcion != 6);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include "helpers.h"

int main() {
    int opcion;
    int num_dias = 0;

    do {
        printf("\nSeleccione una opcion: \n");
        printf("1. Crear zona\n");
        printf("2. Ingresar datos de la zona\n");
        printf("3. Leer datos de la zona\n");
        printf("4. Calcular promedio y generar reporte\n");
        printf("5. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        char nombreArchivo[100];

        switch (opcion) {
        case 1:
            printf("Ingrese el nombre de la nueva zona: ");
            leercadena(nombreArchivo, 100);
            crearArchivo(nombreArchivo, &num_dias);
            break;
        case 2:
            printf("Ingrese el nombre de la zona: ");
            leercadena(nombreArchivo, 100);
            addDia(nombreArchivo, &num_dias);
            break;
        case 3:
            printf("Ingrese el nombre de la zona: ");
            leercadena(nombreArchivo, 100);
            Dia dias[MAX_DIAS];
            leerDatosZona(nombreArchivo, &num_dias, dias);
            for (int i = 0; i < num_dias; i++) {
                printf("\nDía %d:\nCO2: %.2lf ppm\nSO2: %.2lf ppm\nNO2: %.2lf ppm\nPM2.5: %.2lf µg/m³\n",
                       dias[i].numDia, dias[i].CO2, dias[i].SO2, dias[i].NO2, dias[i].PM25);
                mostrarContaminante(dias[i].AQI, &(int){0});
            }
            break;
       case 4:
            printf("Ingrese el nombre de la zona: ");
            leercadena(nombreArchivo, 100);
            strcat(nombreArchivo, ".txt"); // Agrega la extensión
            Dia promedioHistorico = calcularPromedioZonaHistorico(nombreArchivo);

            break;

        case 5:
            printf("Saliendo del programa...\n");
            return 0;
        default:
            printf("Opción no válida. Intente de nuevo.\n");
        }
    } while (1);

    return 0;
}

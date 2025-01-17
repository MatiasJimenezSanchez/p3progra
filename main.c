#include <stdio.h>
#include "funciones.h"

int main () {
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
            //leerDatosZona(nombreArchivo);
            break;
        case 4:
            printf("Ingrese el nombre del archivo: ");
            //leercadena(nombreArchivo, 100);
            //leerDatosZona(nombreArchivo);
            //agregarFechasHistoricas(nombreArchivo);
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
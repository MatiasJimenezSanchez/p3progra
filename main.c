#include <stdio.h>
#include "funciones.h"

int main () {
    int opcion;
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
            scanf("%s", nombreArchivo);
            crearArchivo(nombreArchivo);
            break;
        case 2:
            printf("Ingrese el nombre del archivo: ");
            scanf("%s", nombreArchivo);
            addDia(nombreArchivo);
            break;
        case 3:
            printf("Ingrese el nombre del archivo: ");
            scanf("%s", nombreArchivo);
            leerDatos(nombreArchivo);
            break;
        case 4:
            
            break;
        case 5:
            printf("Saliendo del programa\n");
            return 0;
            break;
        default:
            printf("Opcion no valida\n");
            break;
        }
    } while (opcion != 5);
    return 0;
}
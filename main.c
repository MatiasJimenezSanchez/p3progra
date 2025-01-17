#include <stdio.h>
#include "funciones.h"
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
            for (int i = 0; i < num_dias; i++)
            {
                printf("Dia %d: CO2=%.2lf, SO2=%.2lf, NO2=%.2lf, PM25=%.2lf, Temp=%.2lf, Humedad=%.2lf, Velocidad Aire=%.2lf, AQI=%.2lf\n",
                       dias[i].numDia, dias[i].CO2, dias[i].SO2, dias[i].NO2, dias[i].PM25, dias[i].temperatura, dias[i].humedad, dias[i].velocidad_aire, dias[i].AQI);
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
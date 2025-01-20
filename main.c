#include <stdio.h>
#include "funciones.h"
#include "helpers.h"

int main()
{
    int opcion;
    char nombreArchivo[100];
    int num_dias;
    Dia dias[MAX_DIAS];

    do
    {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Crear archivo\n");
        printf("2. Ingresar datos\n");
        printf("3. Leer datos de zona\n");
        printf("4. Calcular promedios historicos y generar reporte\n");
        printf("5. Salir\n");
        printf("----------------------\n");
        do
        {
            printf("Seleccione una opcion: ");
            while (scanf("%d", &opcion) != 1)
            {
                printf("Error: Debe ingresar un numero entero positivo.\n");
                while (getchar() != '\n')
                    ; // Limpiar el buffer de entrada
            }
        } while (opcion <= 0);

        switch (opcion)
        {
        case 1:
            printf("Ingrese el nombre del archivo: ");
            leercadena(nombreArchivo, 100);
            crearArchivo(nombreArchivo, &num_dias);
            break;

        case 2:
            printf("Ingrese el nombre del archivo: ");
            leercadena(nombreArchivo, 100);
            Dia nuevoDia;
            addDia(nombreArchivo, &num_dias, nuevoDia);
            break;

        case 3:
            printf("Ingrese el nombre del archivo: ");
            leercadena(nombreArchivo, 100);
            leerDatosZona(nombreArchivo, &num_dias, dias);
            printf("Datos leidos correctamente.\n");
            break;

        case 4:
            printf("Ingrese el nombre del archivo: ");
            leercadena(nombreArchivo, 100);
            leerDatosZona(nombreArchivo, &num_dias, dias);

            if (num_dias < 30)
            {
                printf("No hay suficientes datos para calcular promedios historicos (se requieren al menos 30 dias).\n");
                break;
            }

            Dia promedio = promedioPonderadoContaminacionZona(dias, 30); // Ultimos 30 dias
            printf("\nPromedios de contaminacion calculados.\n");

            printf("Generando reporte...\n");
            exportarReporte(nombreArchivo, promedio);

            printf("Reporte generado en '%s_reporte.txt'.\n", nombreArchivo);
            break;

        case 5:
            printf("Saliendo del programa...\n");
            break;

        default:
            printf("Opcion no valida. Por favor, intente de nuevo.\n");
            break;
        }
    } while (opcion != 5);

    return 0;
}
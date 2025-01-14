
#include <stdio.h>
#include <string.h>
#include "funciones.h"

void crearArchi()
{
    struct Zonas zona;
    char nombre[50];
    printf("Ingrese el nombre del archivo: ");
    leercadena(nombre, 50);
    strcat(nombre, ".dat");
    FILE *file = fopen(nombre, "ab+");
    if (file == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
    }
    else
    {
        printf("Archivo creado correctamente.\n");
        fclose(file);
    }
}

double calcularSumaPonderada(double datos, int dias) {
    double suma = 0;
    double pesoTotal = 0;
    for (int i = 0; i < dias; i++) {
        double peso = 1.0 / (i + 1); // Peso inversamente proporcional al día
        suma += datos[i] * peso;
        pesoTotal += peso;
    }
    return suma / pesoTotal;
}

void crearDatosHistoricos(double pm25, int indice){
    struct Zonas zona;
    
    zona.cpPM25 = pm25;
    zona.Dias = indice;
    FILE *file = fopen("historicos.dat", "ab+");
    if (file == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
    }
    else
    {
        printf("Archivo creado correctamente.\n");
        fclose(file);
    }

    fwrite(&zona, sizeof(struct Zonas), 1, file);

}

void saveDatZona(struct Zonas *zona, const char *filename)
{
    FILE *file = fopen(filename, "ab+");

    if (file == NULL)
    {
        printf("Error al abrir el archivo %s\n", filename);
        return;
    }
    else
    {
        fwrite(zona, sizeof(struct Zonas), 1, file);
        printf("Archivo %s abierto correctamente\n", filename);
    }
    fclose(file);
}



void leercadena(char *cadena, int longitud)
{
    fflush(stdin);
    fgets(cadena, longitud, stdin);
    int len = strlen(cadena) - 1;
    cadena[len] = '\0';
}

void creatDatZona()
{
    char nombre[50];
    struct Zonas zona;
    int numMedPM2 = 0, numMedNO2 = 0, numMedSO2 = 0, numMedCO = 0;
    double sumaPM25 = 0, sumaNO2 = 0, sumaSO2 = 0, sumaCO = 0;
    printf("Ingrese el nombre de la zona: \n");
    leercadena(nombre, 50);
    strcat(nombre, ".dat");

    FILE *file = fopen(nombre, "r+");
    if (file == NULL)
    {
        printf("El archivo %s no existe.\n", nombre);
        return;
    }else{
        printf("El archivo %s existe.\n", nombre);
        fclose(file);
    }

    if (fread(&zona, sizeof(struct Zonas), 1, file))
    {
        printf("El archivo %s ya tiene datos.\n", nombre);
        fclose(file);
        return;
    }

    fclose(file);

    printf("\t\tPM2.5\t\t\n");
    printf("\n");
    do
    {
        printf("Cuantas mediciones de PM2.5 deseas ingresar: ");
        while (scanf("%d", &numMedPM2) != 1)
        {
            printf("Por favor ingrese un numero valido\n");
            while (getchar() != '\n')
                ;
        }

    } while (numMedPM2 <= 0);

    zona.TotalMediciones = 0;
    for (int i = 0; i < numMedPM2; i++)
    {

        printf("Ingrese la concentracion %d de PM2.5: ", i + 1);
        while (scanf("%lf", &zona.contaminantes[i].PM25) != 1)
        {
            printf("Por favor ingrese un numero valido\n");
            while (getchar() != '\n')
                ;
        }

        sumaPM25 += zona.contaminantes[i].PM25;
    }

    zona.cpPM25 = CpPM25(numMedPM2, sumaPM25, &zona);
    zona.TotalMediciones += numMedPM2;
    printf("\n");
    printf("\t\tNO2\t\t\n");
    printf("\n");
    printf("!Ten encuenta que las mediciones de NO2 tienen que estar en un rango de 1 hora¡\n");

    do
    {
        printf("Cuantas mediciones de NO2 deseas ingresar: ");
        while (scanf("%d", &numMedNO2) != 1)
        {
            printf("Por favor ingrese un numero valido\n");
            while (getchar() != '\n')
                ;
        }
    } while (numMedNO2 <= 0);

    for (int i = 0; i < numMedNO2; i++)
    {
        printf("Ingrese la concentracion %d de NO2: ", i + 1);
        while (scanf("%lf", &zona.contaminantes[i].NO2) != 1)
        {
            printf("Por favor ingrese un numero valido\n");
            while (getchar() != '\n')
                ;
        }

        sumaNO2 += zona.contaminantes[i].NO2;
    }
    zona.cpNO2 = CpNO2(numMedNO2, sumaNO2, &zona);
    zona.TotalMediciones += numMedNO2;
    printf("\n");
    printf("\t\tSO2\t\t\n");
    printf("\n");

    do
    {
        printf("Cuantas mediciones de SO2 deseas ingresar: ");
        while (scanf("%d", &numMedSO2) != 1)
        {
            printf("Por favor ingrese un numero valido\n");
            while (getchar() != '\n')
                ;
        }
    } while (numMedSO2 <= 0);

    for (int i = 0; i < numMedSO2; i++)
    {
        printf("Ingrese la concentracion %d de SO2: ", i + 1);
        while (scanf("%lf", &zona.contaminantes[i].SO2) != 1)
        {
            printf("Por favor ingrese un numero valido\n");
            while (getchar() != '\n')
                ;
        }

        sumaSO2 += zona.contaminantes[i].SO2;
    }
    zona.cpSO2 = CpSO2(numMedSO2, sumaSO2, &zona);
    zona.TotalMediciones += numMedSO2;
    printf("\n");
    printf("\t\tCO\t\t\n");
    printf("\n");
    printf("!Ten encuenta que las mediciones de CO tienen que estar en un rango de 8 hora¡\n");
    do
    {
        printf("Cuantas mediciones de CO deseas ingresar: ");
        while (scanf("%d", &numMedCO) != 1)
        {
            printf("Por favor ingrese un numero valido\n");
            while (getchar() != '\n')
                ;
        }
    } while (numMedCO <= 0);

    for (int i = 0; i < numMedCO; i++)
    {
        printf("Ingrese la concentracion %d de CO: ", i + 1);
        while (scanf("%lf", &zona.contaminantes[i].CO) != 1)
        {
            printf("Por favor ingrese un numero valido\n");
            while (getchar() != '\n')
                ;
        }
        sumaCO += zona.contaminantes[i].CO;
    }
    zona.cpCO = CpCO(numMedCO, sumaCO, &zona);
    zona.TotalMediciones += numMedCO;
    saveDatZona(&zona, nombre);
}

void leerDatZona()
{

    FILE *file;
    struct Zonas zona;
    char nombre[50];
    int i = 0;
    double PM25;
    printf("Ingrese el nombre de la zona: ");
    leercadena(nombre, 50);
    strcat(nombre, ".dat");
    file = fopen(nombre, "rb");

    if (file == NULL)
    {
        printf("Error al abrir el archivo\n");
        return;
    }
    else
    {
        printf("Archivo abierto correctamente\n");
        while (fread(&zona, sizeof(struct Zonas), 1, file))
        {   
            zona.Dias = i + 1;

            if (zona.TotalMediciones != 0)
            {
                printf("\n");
                printf("*---------------Dias %d---------------*\n", zona.Dias);
                printf("Nombre de la zona: %s\n", nombre);
                printf("Total de mediciones: %d\n", zona.TotalMediciones);
                printf("\n");
                printf("--------------------------------\n");
                printf("Concentracion promedio de PM2.5: %lf\n", zona.cpPM25);
                mostrarContaminante(zona.cpPM25);
                printf("--------------------------------\n");
                printf("Concentracion promedio de NO2: %lf\n", zona.cpNO2);
                mostrarContaminante(zona.cpNO2);
                printf("--------------------------------\n");
                printf("Concentraciones promedio de SO2 : %lf\n", zona.cpSO2);
                mostrarContaminante(zona.cpSO2);
                printf("--------------------------------\n");
                printf("Concentraciones promedio de CO: %lf\n", zona.cpCO);
                mostrarContaminante(zona.cpCO);
                printf("--------------------------------\n");
                i++;
            }
        }
    }
    for (int i = 0; i < 30; i++)
    {
        printf("Concentracion de PM2.5 en el dia %d: %lf\n", i + 1, zona.PM25[i]);
    }
    fclose(file);
    printf("Archivo cerrado correctamente\n");
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

double calcularAQI(double C, double I_low, double I_high, double AQI_low, double AQI_high)
{
    return ((C - I_low) / (I_high - I_low)) * (AQI_high - AQI_low) + AQI_low;
}

double CpPM25(double numMediciones, double sumaConcentraciones, struct Zonas *zona)
{
    double promedio = 0;
    double cpm25 = 0;

    promedio = sumaConcentraciones / numMediciones;
    printf("La suma de las concentraciones es: %lf\n", sumaConcentraciones);
    printf("El promedio de las concentraciones es: %lf\n", promedio);

    if (promedio >= 0 && promedio <= 12)
    {
        zona->contaminantes->I_low = 0;
        zona->contaminantes->I_high = 12;
        zona->contaminantes->AQI_low = 0;
        zona->contaminantes->AQI_high = 50;
    }
    else if (promedio >= 12.1 && promedio <= 35.4)
    {
        zona->contaminantes->I_low = 12.1;
        zona->contaminantes->I_high = 35.4;
        zona->contaminantes->AQI_low = 51;
        zona->contaminantes->AQI_high = 100;
    }
    else if (promedio >= 35.5 && promedio <= 55.4)
    {
        zona->contaminantes->I_low = 35.5;
        zona->contaminantes->I_high = 55.4;
        zona->contaminantes->AQI_low = 101;
        zona->contaminantes->AQI_high = 150;
    }
    else if (promedio >= 55.5 && promedio <= 150.4)
    {
        zona->contaminantes->I_low = 55.5;
        zona->contaminantes->I_high = 150.4;
        zona->contaminantes->AQI_low = 151;
        zona->contaminantes->AQI_high = 200;
    }
    else if (promedio >= 150.5 && promedio <= 250.4)
    {
        zona->contaminantes->I_low = 150.5;
        zona->contaminantes->I_high = 250.4;
        zona->contaminantes->AQI_low = 201;
        zona->contaminantes->AQI_high = 300;
    }
    else if (promedio >= 250.5 && promedio <= 350.4)
    {
        zona->contaminantes->I_low = 250.5;
        zona->contaminantes->I_high = 350.4;
        zona->contaminantes->AQI_low = 301;
        zona->contaminantes->AQI_high = 400;
    }
    else if (promedio >= 350.5 && promedio <= 500.4)
    {
        zona->contaminantes->I_low = 350.5;
        zona->contaminantes->I_high = 500.4;
        zona->contaminantes->AQI_low = 401;
        zona->contaminantes->AQI_high = 500;
    }
    else
    {
        printf("El promedio de las concentraciones no es valido, se ajustara al mas cercano\n");
        zona->contaminantes->I_low = 350.5;
        zona->contaminantes->I_high = 500.4;
        zona->contaminantes->AQI_low = 401;
        zona->contaminantes->AQI_high = 500;
    }

    cpm25 = calcularAQI(promedio, zona->contaminantes->I_low, zona->contaminantes->I_high, zona->contaminantes->AQI_low, zona->contaminantes->AQI_high);
    printf("Indice calculado del contaminante PM2.5: %lf\n", cpm25);
    return cpm25;
}

double CpNO2(double numMediciones, double suma, struct Zonas *zona)
{
    double promedio = 0;
    double cpNO2 = 0;

    promedio = suma / numMediciones;
    printf("La suma de las concentraciones es: %lf\n", suma);
    printf("El promedio de las concentraciones es: %lf\n", promedio);

    if (promedio >= 0 && promedio <= 0.053)
    {
        zona->contaminantes->I_low = 0;
        zona->contaminantes->I_high = 0.053;
        zona->contaminantes->AQI_low = 0;
        zona->contaminantes->AQI_high = 50;
    }
    else if (promedio >= 0.054 && promedio <= 0.100)
    {
        zona->contaminantes->I_low = 0.054;
        zona->contaminantes->I_high = 0.100;
        zona->contaminantes->AQI_low = 51;
        zona->contaminantes->AQI_high = 100;
    }
    else if (promedio >= 0.101 && promedio <= 0.360)
    {
        zona->contaminantes->I_low = 0.101;
        zona->contaminantes->I_high = 0.360;
        zona->contaminantes->AQI_low = 101;
        zona->contaminantes->AQI_high = 200;
    }
    else if (promedio >= 0.361 && promedio <= 0.649)
    {
        zona->contaminantes->I_low = 0.361;
        zona->contaminantes->I_high = 0.649;
        zona->contaminantes->AQI_low = 201;
        zona->contaminantes->AQI_high = 300;
    }
    else if (promedio >= 0.650 && promedio <= 1.249)
    {
        zona->contaminantes->I_low = 0.650;
        zona->contaminantes->I_high = 1.249;
        zona->contaminantes->AQI_low = 301;
        zona->contaminantes->AQI_high = 400;
    }
    else if (promedio >= 1.250 && promedio <= 1.649)
    {
        zona->contaminantes->I_low = 1.250;
        zona->contaminantes->I_high = 1.649;
        zona->contaminantes->AQI_low = 401;
        zona->contaminantes->AQI_high = 500;
    }
    else if (promedio >= 1.650 && promedio <= 2.049)
    {
        zona->contaminantes->I_low = 1.650;
        zona->contaminantes->I_high = 2.049;
        zona->contaminantes->AQI_low = 401;
        zona->contaminantes->AQI_high = 500;
    }
    else
    {
        printf("El promedio de las concentraciones no es valido, se ajustara al mas cercano\n");
        zona->contaminantes->I_low = 1.650;
        zona->contaminantes->I_high = 2.049;
        zona->contaminantes->AQI_low = 401;
        zona->contaminantes->AQI_high = 500;
    }
    cpNO2 = calcularAQI(promedio, zona->contaminantes->I_low, zona->contaminantes->I_high, zona->contaminantes->AQI_low, zona->contaminantes->AQI_high);
    printf("Indice calculado del contaminante NO2: %lf\n", cpNO2);
    return cpNO2;
}

double CpSO2(double numMediciones, double suma, struct Zonas *zona)
{
    double promedio = 0;
    double cpSO2 = 0;

    promedio = suma / numMediciones;
    printf("La suma de las concentraciones es: %lf\n", suma);
    printf("El promedio de las concentraciones es: %lf\n", promedio);

    if (promedio >= 0 && promedio <= 0.035)
    {
        zona->contaminantes->I_low = 0;
        zona->contaminantes->I_high = 0.035;
        zona->contaminantes->AQI_low = 0;
        zona->contaminantes->AQI_high = 50;
    }
    else if (promedio >= 0.036 && promedio <= 0.075)
    {
        zona->contaminantes->I_low = 0.036;
        zona->contaminantes->I_high = 0.075;
        zona->contaminantes->AQI_low = 51;
        zona->contaminantes->AQI_high = 100;
    }
    else if (promedio >= 0.076 && promedio <= 0.185)
    {
        zona->contaminantes->I_low = 0.076;
        zona->contaminantes->I_high = 0.185;
        zona->contaminantes->AQI_low = 101;
        zona->contaminantes->AQI_high = 150;
    }
    else if (promedio >= 0.186 && promedio <= 0.304)
    {
        zona->contaminantes->I_low = 0.186;
        zona->contaminantes->I_high = 0.304;
        zona->contaminantes->AQI_low = 151;
        zona->contaminantes->AQI_high = 200;
    }
    else if (promedio >= 0.305 && promedio <= 0.604)
    {
        zona->contaminantes->I_low = 0.305;
        zona->contaminantes->I_high = 0.604;
        zona->contaminantes->AQI_low = 201;
        zona->contaminantes->AQI_high = 300;
    }
    else if (promedio >= 0.605 && promedio <= 0.804)
    {
        zona->contaminantes->I_low = 0.605;
        zona->contaminantes->I_high = 0.804;
        zona->contaminantes->AQI_low = 301;
        zona->contaminantes->AQI_high = 400;
    }
    else if (promedio >= 0.805 && promedio <= 1.004)
    {
        zona->contaminantes->I_low = 0.805;
        zona->contaminantes->I_high = 1.004;
        zona->contaminantes->AQI_low = 401;
        zona->contaminantes->AQI_high = 500;
    }
    else
    {
        printf("El promedio de las concentraciones no es valido, se ajustara al mas cercano\n");
        zona->contaminantes->I_low = 0.805;
        zona->contaminantes->I_high = 1.004;
        zona->contaminantes->AQI_low = 401;
        zona->contaminantes->AQI_high = 500;
    }
    cpSO2 = calcularAQI(promedio, zona->contaminantes->I_low, zona->contaminantes->I_high, zona->contaminantes->AQI_low, zona->contaminantes->AQI_high);
    printf("Indice calculado del contaminante SO2: %lf\n", cpSO2);
    return cpSO2;
}

double CpCO(double numMediciones, double suma, struct Zonas *zona)
{
    double promedio = 0;
    double cpCO = 0;

    promedio = suma / numMediciones;
    printf("La suma de las concentraciones es: %lf\n", suma);
    printf("El promedio de las concentraciones es: %lf\n", promedio);

    if (promedio >= 0.0 && promedio <= 4.4)
    {
        zona->contaminantes->I_low = 0;
        zona->contaminantes->I_high = 4.4;
        zona->contaminantes->AQI_low = 0;
        zona->contaminantes->AQI_high = 50;
    }
    else if (promedio >= 4.5 && promedio <= 9.4)
    {
        zona->contaminantes->I_low = 4.5;
        zona->contaminantes->I_high = 9.4;
        zona->contaminantes->AQI_low = 51;
        zona->contaminantes->AQI_high = 100;
    }
    else if (promedio >= 9.5 && promedio <= 12.4)
    {
        zona->contaminantes->I_low = 9.5;
        zona->contaminantes->I_high = 12.4;
        zona->contaminantes->AQI_low = 101;
        zona->contaminantes->AQI_high = 150;
    }
    else if (promedio >= 12.5 && promedio <= 15.4)
    {
        zona->contaminantes->I_low = 12.5;
        zona->contaminantes->I_high = 15.4;
        zona->contaminantes->AQI_low = 151;
        zona->contaminantes->AQI_high = 200;
    }
    else if (promedio >= 15.5 && promedio <= 30.4)
    {
        zona->contaminantes->I_low = 15.5;
        zona->contaminantes->I_high = 30.4;
        zona->contaminantes->AQI_low = 201;
        zona->contaminantes->AQI_high = 300;
    }
    else if (promedio >= 30.5 && promedio <= 40.4)
    {
        zona->contaminantes->I_low = 30.5;
        zona->contaminantes->I_high = 40.4;
        zona->contaminantes->AQI_low = 301;
        zona->contaminantes->AQI_high = 400;
    }
    else if (promedio >= 40.5 && promedio <= 50.4)
    {
        zona->contaminantes->I_low = 40.5;
        zona->contaminantes->I_high = 50.4;
        zona->contaminantes->AQI_low = 401;
        zona->contaminantes->AQI_high = 500;
    }
    else
    {
        printf("El promedio de las concentraciones no es valido, se ajustara al mas cercano\n");
        zona->contaminantes->I_low = 40.5;
        zona->contaminantes->I_high = 50.4;
        zona->contaminantes->AQI_low = 401;
        zona->contaminantes->AQI_high = 500;
    }

    cpCO = calcularAQI(promedio, zona->contaminantes->I_low, zona->contaminantes->I_high, zona->contaminantes->AQI_low, zona->contaminantes->AQI_high);
    printf("Indice calculado del contaminante CO: %lf\n", cpCO);
    return cpCO;
}

int findByZoneDia()
{
    char nombre[50];
    int posicion = 0, f = 0;
    int dia;
    FILE *file;
    struct Zonas zona;
    printf("Ingrese el nombre de la zona que desea buscar: ");
    leercadena(nombre, 50);
    strcat(nombre, ".dat");
    file = fopen(nombre, "rb");
    if (file == NULL)
    {
        printf("Error al abrir el archivo\n");
        return -1;
    }
    else
    {
        printf("Ingrese el numero de dia que desea buscar: ");
        scanf("%d", &dia);

        printf("Archivo abierto correctamente\n");
        while (fread(&zona, sizeof(struct Zonas), 1, file))
        {
            if (zona.Dias == dia)
            {
                f = 1;
                printf("Dia %d\n", zona.Dias);
                printf("Total de mediciones: %d\n", zona.TotalMediciones);
                printf("PM2.5: %lf\n", zona.cpPM25);
                printf("NO2: %lf\n", zona.cpNO2);
                printf("SO2: %lf\n", zona.cpSO2);
                printf("CO: %lf\n", zona.cpCO);
                break;
            }
            posicion = ftell(file);
        }
    }
    if (f == 0)
    {
        printf("La zona no se encuentra en el archivo\n");
        posicion = -1;
    }
    fclose(file);
    printf("Archivo cerrado correctamente\n");
    return posicion;
}

/*void updateZone(struct Zonas *zona, int posicion)
{
    FILE *file;
    file = fopen("zonas.dat", "rb+");
    if (file == NULL)
    {
        printf("Error al abrir el archivo\n");
        return;
    }
    else
    {
        fseek(file, posicion, 0);
        fwrite(zona, sizeof(struct Zonas), 1, file);
        printf("Zona actualizada correctamente\n");
    }
    fclose(file);
}
/*
void actualizarZona()
{
    int numMedPM2 = 0, numMedNO2 = 0, numMedSO2 = 0, numMedCO = 0;
    double sumaPM25 = 0, sumaNO2 = 0, sumaSO2 = 0, sumaCO = 0;
    struct Zonas zona;
    char nombre[50];
    int posicion = 0;
    printf("Ingrese el nombre de la zona que desea actualizar: ");
    leercadena(nombre, 50);

    posicion = findByZoneName(nombre);

    if (posicion != -1)
    {
        printf("Ingrese el nuevo nombre de la zona: ");
        leercadena(zona.nomZona, 50);

        printf("\t\tPM2.5\t\t\n");
        printf("\n");
        do
        {
            printf("Cuantas mediciones de PM2.5 deseas ingresar: ");
            while (scanf("%d", &numMedPM2) != 1)
            {
                printf("Por favor ingrese un numero valido\n");
                while (getchar() != '\n')
                    ;
            }

        } while (numMedPM2 <= 0);

        zona.TotalMediciones = 0;
        for (int i = 0; i < numMedPM2; i++)
        {

            printf("Ingrese la la nueva concentracion %d de PM2.5: ", i + 1);
            while (scanf("%lf", &zona.contaminantes[i].PM25) != 1)
            {
                printf("Por favor ingrese un numero valido\n");
                while (getchar() != '\n')
                    ;
            }

            sumaPM25 += zona.contaminantes[i].PM25;
        }

        zona.cpPM25 = CpPM25(numMedPM2, sumaPM25, &zona);
        zona.TotalMediciones += numMedPM2;
        printf("\n");
        printf("\t\tNO2\t\t\n");
        printf("\n");
        printf("!Ten encuenta que las mediciones de NO2 tienen que estar en un rango de 1 hora¡\n");

        do
        {
            printf("Cuantas mediciones de NO2 deseas ingresar: ");
            while (scanf("%d", &numMedNO2) != 1)
            {
                printf("Por favor ingrese un numero valido\n");
                while (getchar() != '\n')
                    ;
            }
        } while (numMedNO2 <= 0);

        for (int i = 0; i < numMedNO2; i++)
        {
            printf("Ingrese la nueva concentracion %d de NO2: ", i + 1);
            while (scanf("%lf", &zona.contaminantes[i].NO2) != 1)
            {
                printf("Por favor ingrese un numero valido\n");
                while (getchar() != '\n')
                    ;
            }

            sumaNO2 += zona.contaminantes[i].NO2;
        }
        zona.cpNO2 = CpNO2(numMedNO2, sumaNO2, &zona);
        zona.TotalMediciones += numMedNO2;
        printf("\n");
        printf("\t\tSO2\t\t\n");
        printf("\n");

        do
        {
            printf("Cuantas mediciones de SO2 deseas ingresar: ");
            while (scanf("%d", &numMedSO2) != 1)
            {
                printf("Por favor ingrese un numero valido\n");
                while (getchar() != '\n')
                    ;
            }
        } while (numMedSO2 <= 0);

        for (int i = 0; i < numMedSO2; i++)
        {
            printf("Ingrese la nueva concentracion %d de SO2: ", i + 1);
            while (scanf("%lf", &zona.contaminantes[i].SO2) != 1)
            {
                printf("Por favor ingrese un numero valido\n");
                while (getchar() != '\n')
                    ;
            }
            sumaSO2 += zona.contaminantes[i].SO2;
        }
        zona.cpSO2 = CpSO2(numMedSO2, sumaSO2, &zona);
        zona.TotalMediciones += numMedSO2;
        printf("\n");
        printf("\t\tCO\t\t\n");
        printf("\n");
        printf("!Ten encuenta que las mediciones de CO tienen que estar en un rango de 8 hora¡\n");
        do
        {
            printf("Cuantas mediciones de CO deseas ingresar: ");
            while (scanf("%d", &numMedCO) != 1)
            {
                printf("Por favor ingrese un numero valido\n");
                while (getchar() != '\n')
                    ;
            }
        } while (numMedCO <= 0);

        for (int i = 0; i < numMedCO; i++)
        {
            printf("Ingrese la nueva concentracion %d de CO: ", i + 1);
            while (scanf("%lf", &zona.contaminantes[i].CO) != 1)
            {
                printf("Por favor ingrese un numero valido\n");
                while (getchar() != '\n')
                    ;
            }
            sumaCO += zona.contaminantes[i].CO;
        }
        zona.cpCO = CpCO(numMedCO, sumaCO, &zona);
        zona.TotalMediciones += numMedCO;
    }
    updateZone(&zona, posicion);
}

void deleateZona()
{
    struct Zonas zona;
    char nombre[50];
    int posicion = 0;
    printf("Ingrese el nombre de la zona que desea eliminar: ");
    leercadena(nombre, 50);
    posicion = findByZoneName(nombre);

    if (posicion != -1)
    {
        zona.nZonas = 0;
        zona.TotalMediciones = 0;
        printf("La zona ha sido eliminada\n");
        updateZone(&zona, posicion);
    }
}
*/
void menu()
{
    int opcion;
    do
    {
        printf("Seleccione una opcion: \n");
        printf("1. Crear archivo\n");
        printf("2. Ingresar datos de la zona\n");
        printf("3. Leer datos de la zona\n");
        printf("4. Encontrar zona por dia\n");
        printf("5. Salir\n");
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            crearArchi();
            break;
        case 2:
            creatDatZona();
            break;
        case 3:
            leerDatZona();
            break;
        case 4:
            findByZoneDia();
            break;
        case 5:
            printf("Saliendo...\n");
            break;
        default:
            printf("Opcion no valida\n");
            break;
        }
    } while (opcion != 6);
}
